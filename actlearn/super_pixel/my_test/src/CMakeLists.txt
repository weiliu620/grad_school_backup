cmake_minimum_required(VERSION 2.8)
project(supervoxel)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# find boost library
set(Boost_DEBUG 0)
set(Boost_USE_STATIC_LIBS on)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.49.0 REQUIRED COMPONENTS program_options filesystem system) 

include_directories(${PROJECT_SOURCE_DIR})


if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(Supervoxel supervoxelseg.cxx MSLIC.cxx)
  #target_link_libraries(Supervoxel ${ITK_LIBRARIES})
  target_link_libraries(Supervoxel ${ITK_LIBRARIES} ${Boost_LIBRARIES})

  if(BUILD_TESTING)
    add_subdirectory(test)
  endif()
endif()             

