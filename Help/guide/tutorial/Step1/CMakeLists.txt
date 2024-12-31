cmake_minimum_required(VERSION 3.15)

# set the project name
project(Tutorial VERSION 1.3.10)

# options
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# set
set(USE_MYMATH ON)
# COMPILE_LANG_AND_ID: if Lang match CXX, and compiler id matches any ARMClang,AppleClang,Clang,GNU,LCC, then 1
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# COMPILE_LANG_AND_ID: if Lang match CXX, and compiler id matches MSVC, then 1
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
# the two variable gcc_like_cxx and msvc_cxx are exclusive


# configurations
configure_file(TutorialConfig.h.in TutorialConfig.h)

# specify the C++ standard
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)
target_compile_options(tutorial_compiler_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)


# subdirectories
add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial1 tutorial.cxx)
target_include_directories(Tutorial1 PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(Tutorial1 PUBLIC MathFunctions tutorial_compiler_flags)

# default installation directory is: /usr/local
install(TARGETS Tutorial1 DESTINATION bin) # /usr/local/bin
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include) # /usr/local/include
install(
    EXPORT MathFunctionsTargets
    FILE MathFunctionsTargets.cmake
    DESTINATION lib/cmake/MathFunctions
)
include(CMakePackageConfigHelpers)

enable_testing()
add_test(NAME Runs1 COMMAND Tutorial1 25)
add_test(NAME Usage COMMAND Tutorial1)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
add_test(NAME StandardUse COMMAND Tutorial1 4)
set_tests_properties(StandardUse PROPERTIES PASS_REGULAR_EXPRESSION "4 is 2")

function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

# do a bunch of result based tests
do_test(Tutorial1 4 "4 is 2")
do_test(Tutorial1 9 "9 is 3")
do_test(Tutorial1 5 "5 is 2.236")
do_test(Tutorial1 7 "7 is 2.645")
do_test(Tutorial1 25 "25 is 5")
do_test(Tutorial1 -25 "-25 is (-nan|nan|0)")
do_test(Tutorial1 0.0001 "0.0001 is 0.01")


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)