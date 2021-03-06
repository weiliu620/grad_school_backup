/*=========================================================================
 * connected component function to update the predicted probability volume
 *=========================================================================*/

/*

// add common libraries for super pixel
#include <common.h>

// add library for super pixel
#include <MSLIC.h>

#include "itkConnectedComponentImageFilter.h"

#include <algorithm>    // std::sort
#include <vector>       // std::vector

// the struct for attributes of connected components
typedef struct ConnectedCompInfor{
     int labelValue;
     int volumeSize;
     float avgPredictProb;
     float sumPredictProb;
} myConnectedCompInfor;

// the comparator for sorting
bool myCompFunction (int i,int j) { return (i>j); }

// the pair data structure for returning indices in sorting
typedef std::pair<int,int> mypair;
typedef std::pair<float,int> mypairFI;
bool myComparatorforCcp ( const mypair& l, const mypair& r)
   { return l.first > r.first; }
bool myComparatorforCcpFI ( const mypairFI& l, const mypairFI& r)
   { return l.first > r.first; }

// define unsigned char type for morphological processing
typedef unsigned char PixelType3DUC;
typedef itk::Image<PixelType3DUC , 3> ImageType3DUC;
typedef itk::ImageFileWriter< ImageType3DUC >  WriterType3DUC;

// for mathematical morphology operations - erosion
#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"


namespace po = boost::program_options;


void morphologicalProcessingTrueCandidatesVolume(ImageType3DUC::Pointer trueCandidatesVolume,
						 ImageType3DUC::Pointer trueCandidatesVolumeErosion, 
						 ImageType3DUC::Pointer trueCandidatesVolumeDilationMinusErosion)
{
     std::cout << "Do morphological processing for true candidates volume to get masks." << std::endl;

     const ImageType3DI::SizeType sizeOfImage = trueCandidatesVolume->GetLargestPossibleRegion().GetSize();
     
     int width = sizeOfImage[0];
     int height = sizeOfImage[1];
     int slice = sizeOfImage[2];

     ImageType3DI::RegionType outRegion = trueCandidatesVolume->GetLargestPossibleRegion();

     int i,j,k;

     ImageType3DUC::IndexType imageIndexUC;
     ImageType3DUC::PixelType imageValueUCerosion, imageValueUCdelision;


     // do erosion = trueCandidatesVolumeErosion
     const unsigned int Dimension = 3;

     typedef itk::BinaryBallStructuringElement<PixelType3DUC, Dimension> StructuringElementType;
     typedef itk::BinaryErodeImageFilter<ImageType3DUC, ImageType3DUC, StructuringElementType> ErodeFilterType;
	  
     ErodeFilterType::Pointer binaryErode = ErodeFilterType::New();

     StructuringElementType structuringElement;

     structuringElement.SetRadius( 1 ); // 3x3 structuring element
     structuringElement.CreateStructuringElement();
     binaryErode->SetKernel( structuringElement );
     binaryErode->SetInput( trueCandidatesVolume );
     binaryErode->SetErodeValue( 1 );

     ImageType3DUC::Pointer tempTrueCandidatesVolumeErosion;
     tempTrueCandidatesVolumeErosion = binaryErode->GetOutput();

     std::string test_save_4 = "test_true_candidates_erosion.nii.gz";
     WriterType3DUC::Pointer writer4 = WriterType3DUC::New();
     writer4->SetFileName( test_save_4 );
     writer4->SetInput( tempTrueCandidatesVolumeErosion ) ;
     writer4->Update();

     for(k=0; k<slice; k++)
     {
	  for(j=0; j<height; j++)
	  {
	       for(i=0; i<width; i++)
	       {
		    imageValueUCerosion = 0;
		    imageIndexUC[0] = i;
		    imageIndexUC[1] = j;
		    imageIndexUC[2] = k;
		    imageValueUCerosion = tempTrueCandidatesVolumeErosion->GetPixel( imageIndexUC );

		    trueCandidatesVolumeErosion->SetPixel(imageIndexUC, imageValueUCerosion );
	       }
	  }
     }


     // do dilation

     typedef itk::BinaryDilateImageFilter<ImageType3DUC, ImageType3DUC, StructuringElementType> DilateFilterType;

     DilateFilterType::Pointer binaryDilate = DilateFilterType::New();

     binaryDilate->SetKernel( structuringElement );
     binaryDilate->SetInput( trueCandidatesVolume );
     binaryDilate->SetDilateValue( 1 );

     ImageType3DUC::Pointer trueCandidatesVolumeDilation = ImageType3DUC::New();
     trueCandidatesVolumeDilation->SetRegions(outRegion);
     trueCandidatesVolumeDilation->Allocate();
     trueCandidatesVolumeDilation->FillBuffer( 0 );

     trueCandidatesVolumeDilation = binaryDilate->GetOutput();

     std::string test_save_5 = "test_true_candidates_dilation.nii.gz";
     WriterType3DUC::Pointer writer5 = WriterType3DUC::New();
     writer5->SetFileName( test_save_5 );
     writer5->SetInput( trueCandidatesVolumeDilation ) ;
     writer5->Update();

     // dilation - erosion = trueCandidatesVolumeDilationMinusErosion

     for(k=0; k<slice; k++)
     {
	  for(j=0; j<height; j++)
	  {
	       for(i=0; i<width; i++)
	       {
		    imageValueUCerosion = 0;
		    imageValueUCdelision = 0;
		    imageIndexUC[0] = i;
		    imageIndexUC[1] = j;
		    imageIndexUC[2] = k;
		    imageValueUCerosion = trueCandidatesVolumeErosion->GetPixel( imageIndexUC );
		    imageValueUCdelision = trueCandidatesVolumeDilation->GetPixel( imageIndexUC );

		    if(imageValueUCerosion < 1 && imageValueUCdelision > 0)
		    {
			 trueCandidatesVolumeDilationMinusErosion->SetPixel(imageIndexUC, 1 );
		    }
	       }
	  }
     }

     // std::string test_save_6 = "test_true_candidates_dilationMinusErosion.nii.gz";
     // WriterType3DUC::Pointer writer6 = WriterType3DUC::New();
     // writer6->SetFileName( test_save_6 );
     // writer6->SetInput( trueCandidatesVolumeDilationMinusErosion ) ;
     // writer6->Update();

}


void computeShapeScoreforCcpCandidates (ImageType3DI::Pointer ccpPredictProb,
					ImageType3DI::Pointer trimap,
					const int& numTopCcptoEvaluate,
					vector< pair<int, int> >& ccpVectorPairs,
					ConnectedCompInfor allConnectedComponents[],
					const float& thresholdScoreforTopCandidates,
					std::string& output_image_file)
{
     std::cout << "Compute shape information for Top ranked connected componets:" << std::endl;

     const ImageType3DI::SizeType sizeOfImage = ccpPredictProb->GetLargestPossibleRegion().GetSize();
     
     int width = sizeOfImage[0];
     int height = sizeOfImage[1];
     int slice = sizeOfImage[2];

     ImageType3DI::RegionType outRegion = ccpPredictProb->GetLargestPossibleRegion();

     // print the sorted connected components based on volume
     int i,j,k,n;
     int curLabelValue = 0;
     ImageType3DI::IndexType ccpIndex;
     ImageType3DI::PixelType ccpLabelValue;

     const unsigned int Dimension = 3;

     float curScoreCriteria = 0;
     float curShapeScore = 0;
     float shapeScoreScaling = 1.0;
     float curVolumeMultiplyProb = 0;
     
     mypairFI ccpTopPair[numTopCcptoEvaluate];

     //for(n=0; n<numTopCcptoEvaluate; n++)
     for(n=0; n<numTopCcptoEvaluate; n++)
     {
	  //cout << "Volume: " << ccpVectorPairs[n].first << " Label: "<<  ccpVectorPairs[n].second << std::endl;
	  cout << " Label: "<<  ccpVectorPairs[n].second << " |  Volume: " << ccpVectorPairs[n].first ;
	  curLabelValue = ccpVectorPairs[n].second;
	  cout << " | Avg Prob.: "<< allConnectedComponents[curLabelValue].avgPredictProb << std::endl ;

	  // for each connected components
	  // step 1: extract the label
	  

	  ImageType3DUC::Pointer curCCPLabel = ImageType3DUC::New();
	  curCCPLabel->SetRegions(outRegion);
	  curCCPLabel->Allocate();
	  curCCPLabel->FillBuffer( 0 );

	  for(k=0; k<slice; k++)
	  {
	       for(j=0; j<height; j++)
	       {
		    for(i=0; i<width; i++)
		    {

			 ccpLabelValue = 0;
			 ccpIndex[0] = i;
			 ccpIndex[1] = j;
			 ccpIndex[2] = k;
			 ccpLabelValue = ccpPredictProb->GetPixel( ccpIndex );
			 
			 if(ccpLabelValue == curLabelValue)
			 {
			      curCCPLabel->SetPixel(ccpIndex, 1 );
			 }
		    }
	       }
	  }
	  
	  
	  // std::string test_save_1 = "test_CurrentCCPVolume.nii.gz";
	  // WriterType3DUC::Pointer writer = WriterType3DUC::New();
	  // writer->SetFileName( test_save_1 );
	  // writer->SetInput( curCCPLabel ) ;
	  // writer->Update();
	  

	  // Step 2: erosion
	  typedef itk::BinaryBallStructuringElement<PixelType3DUC, Dimension> StructuringElementType;
	  typedef itk::BinaryErodeImageFilter<ImageType3DUC, ImageType3DUC, StructuringElementType> ErodeFilterType;
	  
	  ErodeFilterType::Pointer binaryErode = ErodeFilterType::New();

	  StructuringElementType structuringElement;

	  structuringElement.SetRadius( 1 ); // 3x3 structuring element

	  structuringElement.CreateStructuringElement();

	  binaryErode->SetKernel( structuringElement );

	  binaryErode->SetInput( curCCPLabel );

	  binaryErode->SetErodeValue( 1 );

	  ImageType3DUC::Pointer curCCPLabelErosion = ImageType3DUC::New();
	  curCCPLabelErosion->SetRegions(outRegion);
	  curCCPLabelErosion->Allocate();
	  curCCPLabelErosion->FillBuffer( 0 );
	  curCCPLabelErosion = binaryErode->GetOutput();

	  // Note: the following code to save the rosion volume is to prevent
	  // segmentation fault error
	  std::string test_save_2 = "test_CurrentCCPVolume_erosion.nii.gz";
	  WriterType3DUC::Pointer writer2 = WriterType3DUC::New();
	  writer2->SetFileName( test_save_2 );
	  writer2->SetInput( curCCPLabelErosion ) ;
	  writer2->Update();
	  

	  // step 3: original binary - erosion = the boundary voxels
	  //       : & count the boundary voxels
	  ImageType3DUC::Pointer curCCPLabelBoundary = ImageType3DUC::New();
	  curCCPLabelBoundary->SetRegions(outRegion);
	  curCCPLabelBoundary->Allocate();
	  curCCPLabelBoundary->FillBuffer( 0 );

	  ImageType3DUC::IndexType ccpIndexUC;
	  ImageType3DUC::PixelType ccpLabelValueUC_ori,ccpLabelValueUC_ero;
	  
	  int countNumBoundary = 0;
	  for(k=0; k<slice; k++)
	  {
	       for(j=0; j<height; j++)
	       {
		    for(i=0; i<width; i++)
		    {

			 ccpLabelValueUC_ori = 0;
			 ccpLabelValueUC_ero = 0;
			 ccpIndexUC[0] = i;
			 ccpIndexUC[1] = j;
			 ccpIndexUC[2] = k;
			 ccpLabelValueUC_ori = curCCPLabel->GetPixel( ccpIndexUC );
			 ccpLabelValueUC_ero = curCCPLabelErosion->GetPixel( ccpIndexUC );

			 if(ccpLabelValueUC_ori > 0 && ccpLabelValueUC_ero < 1)
			 {
			      curCCPLabelBoundary->SetPixel(ccpIndexUC, 1 );
			      countNumBoundary++;
			 }
		    }
	       }
	  }

	  
	  // std::string test_save_3 = "test_CurrentCCPVolume_boundary.nii.gz";
	  // WriterType3DUC::Pointer writer3 = WriterType3DUC::New();
	  // writer3->SetFileName( test_save_3 );
	  // writer3->SetInput( curCCPLabelBoundary ) ;
	  // writer3->Update();
	  

	  // compute the score for rank the top K connected components

	  curShapeScore = float(ccpVectorPairs[n].first) / float(countNumBoundary);
	  //curVolumeMultiplyProb = float(ccpVectorPairs[n].first) * allConnectedComponents[curLabelValue].avgPredictProb;
	  //curScoreCriteria = curVolumeMultiplyProb +			\
		 //     float(ccpVectorPairs[n].first) *  curShapeScore * curShapeScore * curShapeScore;
	  curScoreCriteria = curShapeScore;
	 
	  cout << " Num of boundary voxel for current CCP: "<< countNumBoundary << std::endl ;
	  cout << " Shape score for current CCP: "<< curShapeScore << std::endl ;
	  //cout << " Volume multiply Prob.: "<< curVolumeMultiplyProb << std::endl ;
	  cout << " Score for current CCP: "<< curScoreCriteria << std::endl ;
	  cout << " ---------------------- " << std::endl ;

	  // create new pair
	  ccpTopPair[n].first = curScoreCriteria;
	  ccpTopPair[n].second = ccpVectorPairs[n].second;
	  
     }

     // sort the ccpTopPair
     
     std::vector< pair<float, int> > ccpTopVectorPairs (ccpTopPair, ccpTopPair+numTopCcptoEvaluate);
     std::sort (ccpTopVectorPairs.begin(), ccpTopVectorPairs.end(), myComparatorforCcpFI);
     
     // create a volume for true candidates
     ImageType3DUC::Pointer trueCandidatesVolume = ImageType3DUC::New();
     trueCandidatesVolume->SetRegions(outRegion);
     trueCandidatesVolume->Allocate();
     trueCandidatesVolume->FillBuffer( 0 );


     // print newly sorted ccpTopPair
     ImageType3DUC::IndexType imageIndexUC;

     cout << "=================== " << std::endl;
     for(n=0; n<numTopCcptoEvaluate; n++)
     {
	  cout << " Label: "<<  ccpTopVectorPairs[n].second << " |  Score: " << ccpTopVectorPairs[n].first << std::endl;
	  
	  curLabelValue = ccpTopVectorPairs[n].second;

	  if(ccpTopVectorPairs[n].first > thresholdScoreforTopCandidates)
	  {
	       cout << "This connected component's score is larger than the user-input threshold." << std::endl;
	       cout << std::endl;
	       // add the label of this connected component to true candidates label volume
	       for(k=0; k<slice; k++)
	       {
		    for(j=0; j<height; j++)
		    {
			 for(i=0; i<width; i++)
			 {
			      ccpLabelValue = 0;
			      ccpIndex[0] = i;
			      ccpIndex[1] = j;
			      ccpIndex[2] = k;
			      ccpLabelValue = ccpPredictProb->GetPixel( ccpIndex );
			      
			      imageIndexUC[0] = i;
			      imageIndexUC[1] = j;
			      imageIndexUC[2] = k;

			      if(curLabelValue == ccpLabelValue)
			      {
				   trueCandidatesVolume->SetPixel(imageIndexUC, 1 );
			      }
			 }
		    }
	       }
	  }

     }
     cout << "=================== " << std::endl;

     ImageType3DUC::Pointer trueCandidatesVolumeErosion = ImageType3DUC::New();
     trueCandidatesVolumeErosion->SetRegions(outRegion);
     trueCandidatesVolumeErosion->Allocate();
     trueCandidatesVolumeErosion->FillBuffer( 0 );

     ImageType3DUC::Pointer trueCandidatesVolumeDilationMinusErosion = ImageType3DUC::New();
     trueCandidatesVolumeDilationMinusErosion->SetRegions(outRegion);
     trueCandidatesVolumeDilationMinusErosion->Allocate();
     trueCandidatesVolumeDilationMinusErosion->FillBuffer( 0 );

     morphologicalProcessingTrueCandidatesVolume(trueCandidatesVolume, trueCandidatesVolumeErosion, trueCandidatesVolumeDilationMinusErosion);

     // use the trueCandidatesVolumeErosion & trueCandidatesVolumeDilationMinusErosion
     // to modify the trimap; trueCandidatesVolumeErosion == 1, trimap = 1; foreground
     // trueCandidatesVolumeDilationMinusErosion == 1, trimap = 0; uncertain
     
     ImageType3DUC::IndexType curImageIndexUC;
     ImageType3DUC::PixelType curImageValueUCerosion, curImageValueUCdelisionMinusErosion;

     for(k=0; k<slice; k++)
     {
      	  for(j=0; j<height; j++)
      	  {
      	       for(i=0; i<width; i++)
      	       {
      		    curImageValueUCerosion = 0;
      		    curImageValueUCdelisionMinusErosion = 0;
      		    curImageIndexUC[0] = i;
      		    curImageIndexUC[1] = j;
      		    curImageIndexUC[2] = k;
      		    curImageValueUCerosion = trueCandidatesVolumeErosion->GetPixel( curImageIndexUC );
      		    curImageValueUCdelisionMinusErosion = trueCandidatesVolumeDilationMinusErosion->GetPixel( curImageIndexUC );

      		    ccpIndex[0] = i;
      		    ccpIndex[1] = j;
      		    ccpIndex[2] = k;

      		    if(curImageValueUCerosion > 0)
      		    {
			 //std::cout << "set as foreground " << std::endl;
      			 trimap->SetPixel(ccpIndex, 1 );
      		    }

      		    if(curImageValueUCdelisionMinusErosion > 0)
      		    {
      			 trimap->SetPixel(ccpIndex, 0 );
      		    }
      	       }
      	  }
     }


     // save the output which is the modified trimap
     std::cout << "Output image name: " << output_image_file << std::endl;
     WriterType3DI::Pointer writer = WriterType3DI::New();
     //WriterType3DUC::Pointer writer = WriterType3DUC::New();
     writer->SetFileName( output_image_file );
     writer->SetInput( trimap ) ;
     writer->Update();
}

int activeLearnCCP(ImageType3DF::Pointer predictProb,
		   ImageType3DI::Pointer alphaLabel,
		   ImageType3DI::Pointer trimap,
		   const float& thresholdPredictProb,
		   const float& thresholdScoreforTopCandidates,
		   std::string& output_image_file)
{
     ImageType3DI::Pointer binaryPredictProb = ImageType3DI::New();
     ImageType3DI::Pointer ccpPredictProb = ImageType3DI::New();

     // ImageType3DI::Pointer OutputImage = ImageType3DI::New();

     // Read information
     const ImageType3DI::SizeType sizeOfImage = alphaLabel->GetLargestPossibleRegion().GetSize();
     
     int width = sizeOfImage[0];
     int height = sizeOfImage[1];
     int slice = sizeOfImage[2];

     // print the image size
     std::cout << "Volume Size" << std::endl;
     std::cout << "width: " <<  width << ", height: " << height << ", slice: " << slice << std::endl;

     // threshold the probability query volume
     ImageType3DI::RegionType outRegion = alphaLabel->GetLargestPossibleRegion();
     binaryPredictProb->SetRegions(outRegion);
     binaryPredictProb->Allocate();
     binaryPredictProb->FillBuffer( 0 );

     int i,j,k;

     ImageType3DF::IndexType pixelIndex;
     ImageType3DF::PixelType pixelValue;
     ImageType3DI::IndexType maskIndex;
     ImageType3DI::PixelType maskValue, binaryValue;
     binaryValue = 1;

     for(k=0; k<slice; k++)
     {
	  for(j=0; j<height; j++)
	  {
	       for(i=0; i<width; i++)
	       {
		    pixelValue = 0;
		    maskValue = 0;

		    pixelIndex[0] = i;
		    pixelIndex[1] = j;
		    pixelIndex[2] = k;

		    maskIndex[0] = i;
		    maskIndex[1] = j;
		    maskIndex[2] = k;

		    pixelValue = predictProb->GetPixel( pixelIndex );
		    maskValue = alphaLabel->GetPixel( maskIndex );
		    // alpha value is 1 or 0, 1: foreground; 0: background
		    if(maskValue < 1)
		    {
			 // it's not inside mask (alpha foreground)
			 if(pixelValue >= thresholdPredictProb)
			 {
			      // the prediction probability is larger than the threshold
			      binaryPredictProb->SetPixel( maskIndex, binaryValue );
			 }
		    }
	       }
	  }
     }
     
     // connected component
     typedef itk::ConnectedComponentImageFilter <ImageType3DI, ImageType3DI >
	  ConnectedComponentImageFilterType;

     ConnectedComponentImageFilterType::Pointer connected =
	  ConnectedComponentImageFilterType::New ();
     connected->SetInput(binaryPredictProb);
     connected->Update();

     int numConnectedComponents = connected->GetObjectCount();

     std::cout << "Number of connected components: " << numConnectedComponents << std::endl;

     ccpPredictProb->SetRegions(outRegion);
     ccpPredictProb->Allocate();
     ccpPredictProb->FillBuffer( 0 );
     ccpPredictProb = connected->GetOutput();


     // initialize the struct for attributes of connected components
     ConnectedCompInfor allConnectedComponents[numConnectedComponents];
     int n;
     for(n=0; n<numConnectedComponents; n++)
     {
	  allConnectedComponents[n].labelValue = n+1;
	  allConnectedComponents[n].volumeSize = 0;
	  allConnectedComponents[n].avgPredictProb = 0;
	  allConnectedComponents[n].sumPredictProb = 0;
     }

     int countNumVoxel = 0;
     int curCcpLabelValue = 0;
     float sumPredictProb = 0;
     float avgPredictProbCcp = 0;
     ImageType3DI::IndexType ccpIndex;
     ImageType3DI::PixelType ccpLabelValue;
     for(n=0; n<numConnectedComponents; n++)
     {
	  countNumVoxel = 0;
	  curCcpLabelValue = allConnectedComponents[n].labelValue;

	  sumPredictProb = 0;

	  for(k=0; k<slice; k++)
	  {
	       for(j=0; j<height; j++)
	       {
		    for(i=0; i<width; i++)
		    {
			 ccpLabelValue = 0;
			 ccpIndex[0] = i;
			 ccpIndex[1] = j;
			 ccpIndex[2] = k;
			 ccpLabelValue = ccpPredictProb->GetPixel( ccpIndex );

			 pixelValue = 0;
			 pixelIndex[0] = i;
			 pixelIndex[1] = j;
			 pixelIndex[2] = k;
			 pixelValue = predictProb->GetPixel( pixelIndex );

			 if(ccpLabelValue == curCcpLabelValue)
			 {
			      countNumVoxel++;
			      sumPredictProb = sumPredictProb + pixelValue;
			 }
		    }
	       }
	  }

	  avgPredictProbCcp = sumPredictProb/countNumVoxel;

	  allConnectedComponents[n].volumeSize = countNumVoxel;
	  allConnectedComponents[n].avgPredictProb = avgPredictProbCcp;
	  allConnectedComponents[n].sumPredictProb = sumPredictProb;
     }
     
     // print the struct of attributes of connected components: 
     
     // for(n=0; n<numConnectedComponents; n++)
     // {
     // 	  std::cout << "Label value of ccp: " << allConnectedComponents[n].labelValue << std::endl;
     // 	  std::cout << "Volume of ccp: " << allConnectedComponents[n].volumeSize << std::endl;
     // 	  std::cout << "Avg predict prob. of ccp: " << allConnectedComponents[n].avgPredictProb << std::endl;
     // 	  std::cout << "Sum predict prob. of ccp: " << allConnectedComponents[n].sumPredictProb << std::endl;
     // 	  std::cout << "---------------" << std::endl;
     // }
     

     mypair ccpPair[numConnectedComponents];
     for(n=0; n<numConnectedComponents; n++)
     {
	  ccpPair[n].first = allConnectedComponents[n].volumeSize;
	  ccpPair[n].second = allConnectedComponents[n].labelValue;
     }

     std::vector< pair<int, int> > ccpVectorPairs (ccpPair, ccpPair+numConnectedComponents);

     std::sort (ccpVectorPairs.begin(), ccpVectorPairs.end(), myComparatorforCcp);

     

     int numTopCCPtoEvaluate = 15;
     computeShapeScoreforCcpCandidates(ccpPredictProb, trimap, numTopCCPtoEvaluate, ccpVectorPairs, allConnectedComponents, thresholdScoreforTopCandidates, output_image_file);

     
     // int largestCcpVolumeLabel = ccpVectorPairs[2].second;
     // OutputImage->SetRegions(outRegion);
     // OutputImage->Allocate();
     // OutputImage->FillBuffer( 0 );
     // for(k=0; k<slice; k++)
     // {
     // 	  for(j=0; j<height; j++)
     // 	  {
     // 	       for(i=0; i<width; i++)
     // 	       {

     // 		    ccpLabelValue = 0;
     // 		    ccpIndex[0] = i;
     // 		    ccpIndex[1] = j;
     // 		    ccpIndex[2] = k;
     // 		    ccpLabelValue = ccpPredictProb->GetPixel( ccpIndex );
     // 		    // alpha value is 1 or 0, 1: foreground; 0: background
     // 		    if(ccpLabelValue == largestCcpVolumeLabel)
     // 		    {
     // 			 OutputImage->SetPixel(ccpIndex, 1 );
     // 		    }
     // 	       }
     // 	  }
     // }
     
     // print the output image file name:

}

*/

// add common libraries for super pixel
#include <common.h>

#include <query.h>

namespace po = boost::program_options;

int main(int argc, char * argv[])
{
     std::string input_predict_prob_volume, input_alpha_label_volume, hard_constraint_map_volume, output_image_file;

     float thresholdPredictProb = 0;
     float thresholdScoreforTopCandidates = 0;

     // program options.
     po::options_description svdesc("Options (to use this Connected Component Function) can only used at commandline");
     svdesc.add_options()
	  
	  ("help,h", "Connected Component Function for 3D predicted probability volume data")

	  ("data,d", po::value<std::string>(&input_predict_prob_volume),
	   "Input 3D volume file of predicted prob. A 3D gipl or nii or nii.gz file.")

	  ("alpha,a", po::value<std::string>(&input_alpha_label_volume),
	   "Input 3D volume of alpha label. A 3D gipl or nii or nii.gz file.")

	  ("contraint,c", po::value<std::string>(&hard_constraint_map_volume),
	   "Input 3D volume of hard contraint map. A 3D gipl or nii or nii.gz file.")
	  
	  ("output,o", po::value<std::string>(&output_image_file),
	   "Output label image file. A 3D nii file.")
	  
	  ("threshold,t", po::value<float>(&thresholdPredictProb)->default_value(0.75),
	   "Threshold value for predicted volume.")

	  ("scorethreshold,s", po::value<float>(&thresholdScoreforTopCandidates)->default_value(1.3),
	   "Threshold value for predicted volume.")

	  ;

     po::variables_map vm;        
     po::store(po::parse_command_line(argc, argv, svdesc), vm);
     po::notify(vm);    

     try {
	  if ( (vm.count("help")) | (argc == 1) ) {
	       std::cout << "Usage: queryccp [options]\n";
	       std::cout << svdesc << "\n";
	       return 0;
	  }
     }
     catch(std::exception& e) {
	  std::cout << e.what() << "\n";
	  return 1;
     }


     ReaderType3DF::Pointer readerPredictProb = ReaderType3DF::New();
     ReaderType3DI::Pointer readerAlphaLabel = ReaderType3DI::New();
     ReaderType3DC::Pointer readerTrimap = ReaderType3DC::New();
     
     ImageType3DF::Pointer predictProb = ImageType3DF::New();
     ImageType3DI::Pointer alphaLabel = ImageType3DI::New();
     ImageType3DC::Pointer trimap = ImageType3DC::New();

     // load prediction probability map
     readerPredictProb->SetFileName( input_predict_prob_volume );
     readerPredictProb->Update();
     predictProb = readerPredictProb->GetOutput();

     // load the alpha label volume (foreground/background label volume)
     readerAlphaLabel->SetFileName( input_alpha_label_volume );
     readerAlphaLabel->Update();
     alphaLabel = readerAlphaLabel->GetOutput();

     // load the hard constraint map (trimap): foreground, background, uncertain.
     readerTrimap->SetFileName( hard_constraint_map_volume );
     readerTrimap->Update();
     trimap = readerTrimap->GetOutput();

     // test cin
     bool flag_do_self_training = false;
     std::string userStr;
     std::string doSelfTraining ("y");
     std::string notdoSelfTraining ("n");
     std::cout << "If do self training? Yes or No (y/n) \n";
     std::cin >> userStr;
     if(userStr.compare(doSelfTraining) == 0)
     {
	  // user input is yes
	  flag_do_self_training = true;
     } 

     if(flag_do_self_training)
     {
	  std::cout << "User agree to do self training! \n";
	  activeLearnCCP(predictProb, alphaLabel, trimap, thresholdPredictProb, thresholdScoreforTopCandidates, 300);
     }
     else
     {
	  std::cout << "User refuse to allow to do self training! \n";
     }

     return EXIT_SUCCESS;

}


