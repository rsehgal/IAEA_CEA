cmake_minimum_required(VERSION 2.8)
project(M)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()


#----------------------------------------------------------------------------
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(.)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h ${PROJECT_SOURCE_DIR}/inc/*.hh) 

ROOT_GENERATE_DICTIONARY(G__ABData inc/Point3D.h LINKDEF inc/DictLinkDef.h)
add_library(ABData SHARED src/Point3D.cpp G__ABData.cxx)
target_link_libraries(ABData ${ROOT_LIBRARIES})

add_executable(Test_Analyse test/Test_Analyse.cpp ${sources} )
target_link_libraries(Test_Analyse ${ROOT_LIBRARIES} ABData) 

add_executable(Test_Track test/Test_Track.cpp ${sources} )
target_link_libraries(Test_Track ${ROOT_LIBRARIES} ABData) 

add_executable(Test_POCA test/Test_POCA.cpp ${sources} )
target_link_libraries(Test_POCA ${ROOT_LIBRARIES} ABData) 

add_executable(ProcessTree test/ProcessTree.cpp ${sources} )
target_link_libraries(ProcessTree ${ROOT_LIBRARIES} ABData) 

add_executable(ProcessTree_Transmission test/ProcessTree_Transmission.cpp ${sources} )
target_link_libraries(ProcessTree_Transmission ${ROOT_LIBRARIES} ABData) 

add_executable(Test_ClusterSize test/Test_ClusterSize.cpp ${sources} )
target_link_libraries(Test_ClusterSize ${ROOT_LIBRARIES} ABData) 

