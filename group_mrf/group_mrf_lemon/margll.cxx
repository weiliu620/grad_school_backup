#include <common.h>
#include <utility.h>

using namespace lemon;
int EstimatePar(ImageType4DF::Pointer fmriPtr,
		ImageType3DChar::Pointer maskPtr,
		ImageType3DChar::Pointer labelPtr,
		SubjectType & vmmsub,
		unsigned numClusters);

int ComputeLL(ImageType4DF::Pointer fmriPtr,
	      ImageType3DChar::Pointer maskPtr,
	      ImageType3DChar::Pointer labelPtr,
	      SubjectType vmmsub,
	      unsigned numClusters);

int PrintPar(SubjectType vmmsub, unsigned numClusters);

int main(int argc, char* argv[])
{
     ParStruct par;

     std::string labelFile, fmriFile;
     // program options.
     po::options_description mydesc("Options can only used at commandline");
     mydesc.add_options()
	  ("help,h", "Given the test label map and fmri data, compute the likelihood, i.e. P(data | labelmap). The vMF parameters are estimated.")
	   ("label,i", po::value<std::string>(&labelFile)->default_value("label.nii.gz"), 	    "test subject label map. For now it is a 3d volume.")
	   ("fmri,f", po::value<std::string>(&fmriFile)->default_value("fmri.nii.gz"), 
	    "test subject fmri file. Should be normalized to sphere.")
	  ("verbose,v", po::value<unsigned short>(&par.verbose)->default_value(0), 
	   "verbose level. 0 for minimal output. 3 for most output.");
     po::variables_map vm;        
     po::store(po::parse_command_line(argc, argv, mydesc), vm);
     po::notify(vm);    

     try {
	  if ( (vm.count("help")) | (argc == 1) ) {
	       std::cout << "Usage: gentestlabel [options]\n";
	       std::cout << mydesc << "\n";
	       return 0;
	  }
     }
     catch(std::exception& e) {
	  std::cout << e.what() << "\n";
	  return 1;
     }    


     // read in initial grp label. Also used as mask. 1-based label converted to
     // 0-based label.
     ReaderType3DChar::Pointer labelReader = ReaderType3DChar::New();
     labelReader->SetFileName(labelFile);
     labelReader->Update();

     ImageType3DChar::Pointer maskPtr = labelReader->GetOutput();
     ImageType3DChar::SizeType maskSize = maskPtr->GetLargestPossibleRegion().GetSize();


     typedef itk::AddImageFilter <ImageType3DChar, ImageType3DChar, ImageType3DChar> AddImageFilterType;
     AddImageFilterType::Pointer addImageFilter = AddImageFilterType::New();
     addImageFilter->SetInput( labelReader->GetOutput()  );
     addImageFilter->SetConstant2(-1);
     addImageFilter->Update();
     ImageType3DChar::Pointer labelPtr = addImageFilter->GetOutput();

     // read in fmri data.
     ReaderType4DFloat::Pointer fmriReader = ReaderType4DFloat::New();
     fmriReader->SetFileName(fmriFile);
     fmriReader->Update();
     ImageType4DF::Pointer fmriPtr = fmriReader->GetOutput();
     ReaderType4DFloat::SizeType fmriSize = fmriPtr->GetLargestPossibleRegion().GetSize();     
     unsigned tsLength = fmriSize[3];

     // num of clusters.
     typedef itk::MinimumMaximumImageCalculator <ImageType3DChar>  ImageCalculatorFilterType;
     ImageCalculatorFilterType::Pointer mmFilter = ImageCalculatorFilterType::New ();
     mmFilter->SetImage(maskPtr);
     mmFilter->Compute();
     unsigned numClusters = mmFilter->GetMaximum();     

     // vMF parameters.
     SubjectType vmmsub;
     vmmsub.comp.resize(numClusters);
     vmmsub.name = "testsub";
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  vmmsub.comp[clsIdx].mu.set_size(tsLength);
	  vmmsub.comp[clsIdx].mu = 0;
	  vmmsub.comp[clsIdx].meanNorm = 0;
	  vmmsub.comp[clsIdx].kappa = 0;
	  vmmsub.comp[clsIdx].numPts = 0;
	  vmmsub.comp[clsIdx].prop = 0;
     }

     // estiamte vMF parameters: mu and kappa.
     EstimatePar(fmriPtr, maskPtr, labelPtr, vmmsub, numClusters);
     if (par.verbose >= 1) {
	  PrintPar(vmmsub, numClusters);
     }

     // compute log-likelihood.
     double LL = ComputeLL(fmriPtr, maskPtr, labelPtr, vmmsub, numClusters);
     printf("%E", LL);
     
}

int EstimatePar(ImageType4DF::Pointer fmriPtr,
		ImageType3DChar::Pointer maskPtr,
		ImageType3DChar::Pointer labelPtr,
		SubjectType & vmmsub,
		unsigned numClusters)
{
     IteratorType3DChar maskIt(maskPtr, maskPtr->GetLargestPossibleRegion());
     ConstIteratorType3DChar labelIt(labelPtr, labelPtr->GetLargestPossibleRegion() );
     ImageType3DChar::IndexType labelIdx;
     ReaderType4DFloat::SizeType fmriSize = fmriPtr->GetLargestPossibleRegion().GetSize();     ImageType4DF::IndexType fmriIdx;
     unsigned tsLength = fmriSize[3];

     unsigned clsIdx = 0;
     for (labelIt.GoToBegin(), maskIt.GoToBegin(); !maskIt.IsAtEnd(); ++labelIt, ++ maskIt) {
	  if (maskIt.Get() > 0) {
	       labelIdx = labelIt.GetIndex();
	       fmriIdx[0] = labelIdx[0];
	       fmriIdx[1] = labelIdx[1];
	       fmriIdx[2] = labelIdx[2];
	       clsIdx = labelIt.Get();

	       for (fmriIdx[3] = 0; fmriIdx[3] < tsLength; fmriIdx[3] ++) {
		    vmmsub.comp[clsIdx].mu[fmriIdx[3]] += fmriPtr->GetPixel(fmriIdx);
	       }
	       vmmsub.comp[clsIdx].numPts ++;
	  }
     }
     // compute mean time series and meanNorm.
     for (clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  if (vmmsub.comp[clsIdx].numPts > 0) {
	       vmmsub.comp[clsIdx].meanNorm = vmmsub.comp[clsIdx].mu.two_norm() / vmmsub.comp[clsIdx].numPts;
	       vmmsub.comp[clsIdx].mu.normalize();
	  }
	  else {
	       vmmsub.comp[clsIdx].meanNorm = 0;
	  }
     }

     
     // estimate kappa.
     float kappa = 0, kappa_new = 0;
     double Ap = 0;
     float RBar = 0;
     float Dim = tsLength;

     for (clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  if (vmmsub.comp[clsIdx].numPts > 0){
	       RBar = vmmsub.comp[clsIdx].meanNorm;
	       kappa_new = RBar * (Dim - RBar * RBar) / (1 - RBar * RBar);
	       unsigned iter = 0;
	       do {
		    iter ++;
		    kappa = kappa_new;
		    Ap = exp(logBesselI(Dim/2, kappa) - logBesselI(Dim/2 - 1, kappa));
		    kappa_new = kappa - ( (Ap - RBar) / (1 - Ap * Ap - (Dim - 1) * Ap / kappa)  );
	       }
	       while(vnl_math_abs(kappa_new - kappa) > 0.01 * kappa && iter < 5);
	       vmmsub.comp[clsIdx].kappa = kappa_new;
	  } // numPts > 0
	  else {
	       vmmsub.comp[clsIdx].kappa = 0;
	  }
     } // for(clsIdx
     return 0;
}


int ComputeLL(ImageType4DF::Pointer fmriPtr,
		ImageType3DChar::Pointer maskPtr,
		ImageType3DChar::Pointer labelPtr,
		SubjectType vmmsub,
		unsigned numClusters)

{
     IteratorType3DChar maskIt(maskPtr, maskPtr->GetLargestPossibleRegion());
     ConstIteratorType3DChar labelIt(labelPtr, labelPtr->GetLargestPossibleRegion() );
     ReaderType4DFloat::SizeType fmriSize = fmriPtr->GetLargestPossibleRegion().GetSize();     
     ImageType3DChar::IndexType labelIdx;
     ImageType4DF::IndexType fmriIdx;
     unsigned tsLength = fmriSize[3];
     unsigned clsIdx = 0;

     std::vector<double >vmfLogConst(numClusters, 0);
     double myD = tsLength;
     double const Pi = 4 * atan(1);

     for (clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  if (vmmsub.comp[clsIdx].kappa > 1) {
	       vmfLogConst[clsIdx] = 
		    (myD/2 - 1) * log (vmmsub.comp[clsIdx].kappa)
		    - myD/2 * log(2*Pi) 
		    - logBesselI(myD/2 - 1, vmmsub.comp[clsIdx].kappa);
	  }
	  else {
	       vmfLogConst[clsIdx] = 25.5; // the limit when kappa -> 0
	  }
     }// for

     vnl_vector <float> timeSeries(tsLength, 0);
     double LL = 0;
     for (maskIt.GoToBegin(), labelIt.GoToBegin(); !maskIt.IsAtEnd(); ++ maskIt, ++ labelIt) {
	  if (maskIt.Get() > 0 ) {
	       labelIdx = labelIt.GetIndex();
	       fmriIdx[0] = labelIdx[0];
	       fmriIdx[1] = labelIdx[1];
	       fmriIdx[2] = labelIdx[2];
	       clsIdx = labelIt.Get();

	       // read in data.
	       for (fmriIdx[3] = 0; fmriIdx[3] < tsLength; fmriIdx[3] ++) {
		    timeSeries[fmriIdx[3]] = fmriPtr->GetPixel(fmriIdx);
	       }

	       LL += ( vmfLogConst[clsIdx] + vmmsub.comp[clsIdx].kappa * inner_product(timeSeries, vmmsub.comp[clsIdx].mu) );
	  }
     }

     return LL;
}


int PrintPar(SubjectType vmmsub, unsigned numClusters)
{
     printf("%-11s", "mu");
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  printf("%10s%02d", "mu_", clsIdx+1);
     }
     printf("\n");
	  
     printf("%-10s", vmmsub.name.c_str());
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {

	  printf("[%3.2f %3.2f] ", vmmsub.comp[clsIdx].mu[0], vmmsub.comp[clsIdx].mu[1]);
     }
     printf("\n");

     // print VMF's kappa.
     printf("%-11s", "kappa");
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  printf("%10s%02d", "kappa_", clsIdx+1);
     }
     printf("\n");
	  
     printf("%-10s", vmmsub.name.c_str());
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {

	  printf("%12.4f", vmmsub.comp[clsIdx].kappa);
     }
     printf("\n");

     // print the number of points in each sub's each clusters.
     printf("%-11s", "numPts");
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  printf("%10s%02d", "numPts_", clsIdx+1);
     }
     printf("\n");

     printf("%-10s", vmmsub.name.c_str());
     for (unsigned clsIdx = 0; clsIdx < numClusters; clsIdx ++) {
	  printf("%12ld", vmmsub.comp[clsIdx].numPts);
     }
     printf("\n");

}
