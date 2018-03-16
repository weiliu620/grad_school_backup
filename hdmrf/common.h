#ifndef __COMMON_H__ 
#define __COMMON_H__

#include <cstdio>
#include <new>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <cstdlib>     /* div, div_t */
#include <cstddef>

#include <boost/filesystem.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/version.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <itkNiftiImageIO.h>
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkNeighborhoodIterator.h"
#include "itkConstantBoundaryCondition.h"
#include "itkCannyEdgeDetectionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include <itkExtractImageFilter.h>
#include "itkStatisticsImageFilter.h"
#include <vnl/vnl_rank.h>
#include <vnl/vnl_inverse.h>
#include <vnl/algo/vnl_matrix_inverse.h>
#include <vnl/vnl_sparse_matrix.h>
#include <vcl_iostream.h>
#include <vnl/vnl_matlab_print.h>

typedef itk::Image<float, 2> ImageType2DF;
typedef itk::Image<unsigned, 3> ImageType3DU;
typedef itk::Image<short int, 3> ImageType3DS;
typedef itk::Image<int, 3> ImageType3DI;
typedef itk::Image<char, 3> ImageType3DC;
typedef itk::Image<float, 3> ImageType3DF;
typedef itk::Image<float, 4> ImageType4DF;

typedef itk::ImageFileReader< ImageType2DF >  ReaderType2D;
typedef itk::ImageFileReader< ImageType3DF >  ReaderType3D;
typedef itk::ImageFileReader< ImageType3DS >  ReaderType3DS;
typedef itk::ImageFileReader< ImageType3DF >  ReaderType3DF;
typedef itk::ImageFileReader< ImageType3DI >  ReaderType3DI;
typedef itk::ImageFileReader< ImageType3DC >  ReaderType3DC;
typedef itk::ImageFileReader< ImageType3DU >  ReaderType3DU;
typedef itk::ImageFileReader< ImageType4DF >  ReaderType4DF;

typedef itk::ImageFileWriter< ImageType2DF >  WriterType2DF;
typedef itk::ImageFileWriter< ImageType3DS >  WriterType3DS;
typedef itk::ImageFileWriter< ImageType3DI >  WriterType3DI;
typedef itk::ImageFileWriter< ImageType3DF >  WriterType3DF;
typedef itk::ImageFileWriter< ImageType3DC >  WriterType3DC;
typedef itk::ImageFileWriter< ImageType3DU >  WriterType3DU;
typedef itk::ImageFileWriter< ImageType4DF >  WriterType4DF;

typedef itk::ImageRegionConstIterator< ImageType2DF > ConstIteratorType2DF;
typedef itk::ImageRegionConstIterator< ImageType3DF > ConstIteratorType3DF;
typedef itk::ImageRegionConstIterator< ImageType3DC > ConstIteratorType3DC;

typedef itk::ImageRegionIterator< ImageType2DF>       IteratorType2DF;
typedef itk::ImageRegionIterator< ImageType3DF>       IteratorType3DF;
typedef itk::ImageRegionIterator< ImageType3DC>       IteratorType3DC;
typedef itk::ImageRegionIterator< ImageType3DI>       IteratorType3DI;
typedef itk::ImageRegionIterator< ImageType3DU>       IteratorType3DU;
typedef itk::ImageRegionIterator< ImageType3DS>       IteratorType3DS;
typedef itk::ImageRegionIterator< ImageType4DF>       IteratorType4DF;

struct  CompType
{
     double mu;
     double var;
     int label; // which label assigned to this comp.
     double numPts; // how many data points in this comp.
     double pi;
};


struct GMMType
{
     unsigned n_comp; // num of comp 
     std::vector<CompType> comp; // each Gaussian component.
     std::string name; // either FG or BG
};

struct ParType
{
     GMMType gmm;
     unsigned n_pts;
     double beta;
     unsigned verbose;
};




#define EPS 1e-6
#define PI 3.14159265
#define NCOMP 3

#endif 
  
