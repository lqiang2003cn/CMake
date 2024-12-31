cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial VERSION 1.3.10)

# set
set(USE_MYMATH ON)

# configurations
configure_file(TutorialConfig.h.in TutorialConfig.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# subdirectories
add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial1 tutorial.cxx)
target_include_directories(Tutorial1 PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/MathFunctions")
target_link_libraries(Tutorial1 PUBLIC MathFunctions)


