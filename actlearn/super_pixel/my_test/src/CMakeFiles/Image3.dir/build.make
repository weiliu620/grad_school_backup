# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/cmake

# The command to remove a file.
RM = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src

# Include any dependencies generated for this target.
include CMakeFiles/Image3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Image3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Image3.dir/flags.make

CMakeFiles/Image3.dir/Image3.cxx.o: CMakeFiles/Image3.dir/flags.make
CMakeFiles/Image3.dir/Image3.cxx.o: Image3.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Image3.dir/Image3.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Image3.dir/Image3.cxx.o -c /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/Image3.cxx

CMakeFiles/Image3.dir/Image3.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Image3.dir/Image3.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/Image3.cxx > CMakeFiles/Image3.dir/Image3.cxx.i

CMakeFiles/Image3.dir/Image3.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Image3.dir/Image3.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/Image3.cxx -o CMakeFiles/Image3.dir/Image3.cxx.s

CMakeFiles/Image3.dir/Image3.cxx.o.requires:
.PHONY : CMakeFiles/Image3.dir/Image3.cxx.o.requires

CMakeFiles/Image3.dir/Image3.cxx.o.provides: CMakeFiles/Image3.dir/Image3.cxx.o.requires
	$(MAKE) -f CMakeFiles/Image3.dir/build.make CMakeFiles/Image3.dir/Image3.cxx.o.provides.build
.PHONY : CMakeFiles/Image3.dir/Image3.cxx.o.provides

CMakeFiles/Image3.dir/Image3.cxx.o.provides.build: CMakeFiles/Image3.dir/Image3.cxx.o

CMakeFiles/Image3.dir/MSLIC.cxx.o: CMakeFiles/Image3.dir/flags.make
CMakeFiles/Image3.dir/MSLIC.cxx.o: MSLIC.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Image3.dir/MSLIC.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Image3.dir/MSLIC.cxx.o -c /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/MSLIC.cxx

CMakeFiles/Image3.dir/MSLIC.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Image3.dir/MSLIC.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/MSLIC.cxx > CMakeFiles/Image3.dir/MSLIC.cxx.i

CMakeFiles/Image3.dir/MSLIC.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Image3.dir/MSLIC.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/MSLIC.cxx -o CMakeFiles/Image3.dir/MSLIC.cxx.s

CMakeFiles/Image3.dir/MSLIC.cxx.o.requires:
.PHONY : CMakeFiles/Image3.dir/MSLIC.cxx.o.requires

CMakeFiles/Image3.dir/MSLIC.cxx.o.provides: CMakeFiles/Image3.dir/MSLIC.cxx.o.requires
	$(MAKE) -f CMakeFiles/Image3.dir/build.make CMakeFiles/Image3.dir/MSLIC.cxx.o.provides.build
.PHONY : CMakeFiles/Image3.dir/MSLIC.cxx.o.provides

CMakeFiles/Image3.dir/MSLIC.cxx.o.provides.build: CMakeFiles/Image3.dir/MSLIC.cxx.o

# Object files for target Image3
Image3_OBJECTS = \
"CMakeFiles/Image3.dir/Image3.cxx.o" \
"CMakeFiles/Image3.dir/MSLIC.cxx.o"

# External object files for target Image3
Image3_EXTERNAL_OBJECTS =

Image3: CMakeFiles/Image3.dir/Image3.cxx.o
Image3: CMakeFiles/Image3.dir/MSLIC.cxx.o
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitksys-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkvnl_algo-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkvnl-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkv3p_netlib-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKCommon-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkNetlibSlatec-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKStatistics-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOImageBase-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKMesh-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkzlib-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKMetaIO-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKSpatialObjects-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKPath-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKLabelMap-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKQuadEdgeMesh-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKOptimizers-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKPolynomials-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKBiasCorrection-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKBioCell-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKDICOMParser-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKEXPAT-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOXML-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOSpatialObjects-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKFEM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOBMP-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOBioRad-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkopenjpeg-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmDICT-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmMSFF-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGDCM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOIPL-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGE-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGIPL-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkjpeg-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOJPEG-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOMeta-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKznz-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKniftiio-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIONIFTI-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKNrrdIO-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIONRRD-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkpng-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOPNG-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOSiemens-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOStimulate-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitktiff-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTIFF-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformBase-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkhdf5_cpp-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkhdf5-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformHDF5-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformInsightLegacy-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformMatlab-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOVTK-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKKLMRegionGrowing-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOLSM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVTK-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKWatersheds-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKDeprecated-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKgiftiio-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOCSV-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOHDF5-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOMesh-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKOptimizersv4-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKReview-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVideoCore-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVideoIO-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKDICOMParser-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOLSM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKgiftiio-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKLabelMap-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKQuadEdgeMesh-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKBiasCorrection-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKPolynomials-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKBioCell-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOSpatialObjects-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOXML-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKFEM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKOptimizers-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOBMP-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOBioRad-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGDCM-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmMSFF-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkopenjpeg-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmDICT-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmIOD-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKEXPAT-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmDSED-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmCommon-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmjpeg8-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmjpeg12-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmjpeg16-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkgdcmuuid-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGIPL-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOJPEG-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOMeta-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKMetaIO-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIONIFTI-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKniftiio-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKznz-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIONRRD-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKNrrdIO-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOPNG-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkpng-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOSiemens-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOGE-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOIPL-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOStimulate-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTIFF-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitktiff-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkjpeg-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformHDF5-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkhdf5_cpp-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkhdf5-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkzlib-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformInsightLegacy-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformMatlab-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOTransformBase-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOVTK-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKKLMRegionGrowing-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVTK-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKWatersheds-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKSpatialObjects-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKMesh-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKPath-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKStatistics-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkNetlibSlatec-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKIOImageBase-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVideoCore-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKCommon-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitksys-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libITKVNLInstantiation-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkvnl_algo-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkv3p_lsqr-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkvnl-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkvcl-4.3.a
Image3: /home/sci/weiliu/packages/itk_4.3.1_bin/wukong/lib/libitkv3p_netlib-4.3.a
Image3: CMakeFiles/Image3.dir/build.make
Image3: CMakeFiles/Image3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Image3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Image3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Image3.dir/build: Image3
.PHONY : CMakeFiles/Image3.dir/build

CMakeFiles/Image3.dir/requires: CMakeFiles/Image3.dir/Image3.cxx.o.requires
CMakeFiles/Image3.dir/requires: CMakeFiles/Image3.dir/MSLIC.cxx.o.requires
.PHONY : CMakeFiles/Image3.dir/requires

CMakeFiles/Image3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Image3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Image3.dir/clean

CMakeFiles/Image3.dir/depend:
	cd /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src /home/sci/weiliu/projects/actlearn/super_pixel/my_test/src/CMakeFiles/Image3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Image3.dir/depend

