#include "commonalt.h"
#include "/home/sci/weiliu/packages/InsightToolkit-3.20.0/Utilities/vxl/core/vnl/algo/vnl_qr.h"
#include "/home/sci/weiliu/packages/InsightToolkit-3.20.0/Utilities/vxl/core/vnl/algo/vnl_matrix_inverse.h"
#include "/home/sci/weiliu/packages/InsightToolkit-3.20.0/Utilities/vxl/core/vnl/vnl_inverse.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
     unsigned short verbose = 0;

     std::string observedimage, maskimage, fmrionsphere;
     // Declare a group of options that will be allowed only on
     // command line
     po::options_description generic("Options can only used at commandline");
     generic.add_options()
	  ("help,h", "produce help message")
	  ("verbose,v", po::value<unsigned short>(&verbose)->default_value(0), 
	   "verbose level. 0 for minimal output. 3 for most output.")

	  ("in", po::value<std::string>(&observedimage)->default_value("observedimage.nii"),
	   "original input nii file.")
	  ("out", po::value<std::string>(&fmrionsphere)->default_value("fmrionsphere.nii"),
	   "output file. Time series vector are subtracted mean and normalized to unit length.");

     po::options_description cmdline_options;
     cmdline_options.add(generic);

     po::positional_options_description p;
     p.add("in", -1);

     po::variables_map vm;        
     po::store(po::command_line_parser(argc, argv).
	       options(cmdline_options).positional(p).run(), vm);
     po::notify(vm);    

     try {

	  if (vm.count("help")) {
	       std::cout << "Usage: generateimage [options]\n";
	       std::cout << cmdline_options << "\n";
	       return 0;
	  }
	  
     }

     catch(std::exception& e)
     {
	  std::cout << e.what() << "\n";
	  return 1;
     }    


     

     // read in image data.
     ReaderType4DFloat::Pointer imageReader = ReaderType4DFloat::New();
     imageReader->SetFileName(observedimage);
     imageReader->Update();
     ImageType4DFloat::Pointer imagePtr = imageReader->GetOutput();
     ImageType4DFloat::SizeType imageSize = imagePtr->GetLargestPossibleRegion().GetSize();
     ImageType4DFloat::IndexType imageIdx;    

     // Allocate memory for saving mean image, and std image.
     ImageType3DFloat::Pointer meanPtr = ImageType3DFloat::New();
     ImageType3DFloat::IndexType meanStart;
     ImageType3DFloat::IndexType meanIdx;
     meanStart.Fill(0);

     ImageType3DFloat::SizeType meanSize;
     meanSize[0] = imageSize[0];
     meanSize[1] = imageSize[1];
     meanSize[2] = imageSize[2];

     ImageType3DFloat::RegionType meanRegion;
     meanRegion.SetSize(meanSize);
     meanRegion.SetIndex(meanStart);
     meanPtr->SetRegions(meanRegion);
     meanPtr->Allocate();
     meanPtr->FillBuffer(0);
     IteratorType3DFloat meanIt(meanPtr, meanRegion);

     // Allocate memory for saving std image.
     ImageType3DFloat::Pointer stdPtr = ImageType3DFloat::New();
     ImageType3DFloat::IndexType stdStart;
     stdStart.Fill(0);

     ImageType3DFloat::SizeType stdSize;
     stdSize[0] = imageSize[0];
     stdSize[1] = imageSize[1];
     stdSize[2] = imageSize[2];

     ImageType3DFloat::RegionType stdRegion;
     stdRegion.SetSize(stdSize);
     stdRegion.SetIndex(stdStart);
     stdPtr->SetRegions(stdRegion);
     stdPtr->Allocate();
     stdPtr->FillBuffer(0);
     IteratorType3DFloat stdIt(stdPtr, stdRegion);

     // Allocate memory for saving sphere image.
     ImageType4DFloat::Pointer spherePtr = ImageType4DFloat::New();
     ImageType4DFloat::IndexType sphereStart;
     ImageType4DFloat::IndexType sphereIdx;
     sphereStart.Fill(0);

     ImageType4DFloat::SizeType sphereSize;
     sphereSize[0] = imageSize[0];
     sphereSize[1] = imageSize[1];
     sphereSize[2] = imageSize[2];
     // But, new vectors should be p-1 dimension because of the
     // hyperplane transformation.
     sphereSize[3] = imageSize[3] - 1;
     ImageType4DFloat::RegionType sphereRegion;
     sphereRegion.SetSize(sphereSize);
     sphereRegion.SetIndex(sphereStart);
     spherePtr->SetRegions(sphereRegion);
     spherePtr->Allocate();
     spherePtr->FillBuffer(0);
     spherePtr->SetOrigin(imagePtr->GetOrigin());
     spherePtr->SetSpacing(imagePtr->GetSpacing());
     spherePtr->SetDirection(imagePtr->GetDirection());

     IteratorType4DFloat sphereIt(spherePtr, sphereRegion);

     const unsigned timeSeriesLength = imageSize[3];
     vnl_vector <float> timeSeries(timeSeriesLength, 0);

     // Compute the transformation matrix to rotate vector such that
     // it's aligned with one axis.

     vnl_matrix<float> hyperBases(timeSeriesLength, timeSeriesLength);
     vnl_matrix<float> naturalBases(timeSeriesLength, timeSeriesLength);
     vnl_matrix<float> transMat(timeSeriesLength, timeSeriesLength);

     // Construct original bases, which is for the space where the
     // hyperplane resides.

     hyperBases.fill(0);
     hyperBases.set_row(timeSeriesLength - 1, -1);
     hyperBases.fill_diagonal(1);
     hyperBases.set_column(timeSeriesLength - 1, 1);

//     printVnlMatrix(hyperBases, 10);
     
     // Construct newBasis, which is the natural bases of destination
     // space.
     naturalBases.fill(0);
     naturalBases.fill_diagonal(1);

     vnl_qr<float> qrComp(hyperBases);
     vnl_matrix<float> orthHyperBases = qrComp.Q();

     // becuse naturalBases = orthHyperBases * transMat, we want to
     // get the matrix transMat. And coordinates_under_hyperBases =
     // transMat * coordinates_under_naturalBases.
     transMat = vnl_matrix_inverse<float>(orthHyperBases) * naturalBases;
     

     for (meanIt.GoToBegin(), stdIt.GoToBegin(); !meanIt.IsAtEnd(); ++ meanIt, ++ stdIt)
     {
	  meanIdx = meanIt.GetIndex();
	  imageIdx[0] = meanIdx[0];
	  imageIdx[1] = meanIdx[1];
	  imageIdx[2] = meanIdx[2];
	  // First save time series at this position into a vector.
	  for (imageIdx[3] = 0; imageIdx[3] < imageSize[3]; imageIdx[3] ++) {
	       timeSeries[imageIdx[3]] = imagePtr->GetPixel(imageIdx);
	  }

//	  printVnlVector(timeSeries, 3);

	  meanIt.Set(timeSeries.mean());
	  timeSeries = timeSeries - timeSeries.mean();

//	  printVnlVector(timeSeries, 3);

	  // root mean square of the time series, is actually the sample
	  // std deviation when sample is zero mean.
	  stdIt.Set(timeSeries.rms());
     
	  // Normalize by deviding by the magnitude, which is not equal to
	  // the rms (sample std deviation). So this normalization is not
	  // the one in the statistics sense. But because after this
	  // normalization, the time series will be on sphere, we use it.
	  timeSeries.normalize();

//	  printVnlVector(timeSeries, 3);

	  // all the data points are at a hyperplane x_1 + x_2 + ... = 1
	  // because we normalize it by subtract the mean. we need to
	  // project such that its last elements (or the first, depending
	  // on the implenmentation) is zero, and we discard it, so the
	  // remaning vector is in a p-1 space, and p-2 sphere.

	  // v2 = Matrix * v1, where v1 is the coordinates under natural
	  // bases, and v2 is coordinates under hyper bases.
	  timeSeries.pre_multiply(transMat);

//	  printVnlVector(timeSeries, 3);

	  // Now the coordinates should have one element always zero. 

	  // Save time series to spherePtr.
	  sphereIdx[0] = meanIdx[0];
	  sphereIdx[1] = meanIdx[1];
	  sphereIdx[2] = meanIdx[2];
	  // it seesm after transformation, last coordinate will be
	  // zero, so we just discard last one and keep first p - 1
	  // one.
	  for (sphereIdx[3] = 0; sphereIdx[3] < sphereSize[3]; sphereIdx[3] ++) {
	       spherePtr->SetPixel(sphereIdx, timeSeries[sphereIdx[3]]);
	  }
     }


     // write back.
     WriterType4DFloat::Pointer writer = WriterType4DFloat::New();
     
     writer->SetInput(spherePtr);
     writer->SetFileName(fmrionsphere);
     try 
     { 
	  writer->Update(); 
     } 
     catch( itk::ExceptionObject & err ) 
     { 
	  std::cerr << "ExceptionObject caught !" << std::endl; 
	  std::cerr << err << std::endl; 
	  return EXIT_FAILURE;
     } 

     std::cout << "projectfmri(): File " << fmrionsphere << " saved.\n";
     return 0;
}




