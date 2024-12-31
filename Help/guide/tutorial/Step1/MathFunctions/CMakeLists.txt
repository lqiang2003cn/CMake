include(MakeTable.cmake)

add_library(MathFunctions MathFunctions.cxx)
target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")

#include(CheckCXXSourceCompiles)
#check_cxx_source_compiles("
#    #include <cmath>
#    int main() {
#      std::log(1.01);
#      return 0;
#    }
#  " HAVE_LOG)
#check_cxx_source_compiles("
#    #include <cmath>
#    int main() {
#      std::exp(1.01);
#      return 0;
#    }
#  " HAVE_EXP)



option(USE_MYMATH "Use tutorial provided math implementation" ON)

# define a compile definition for MathFunctions
if(USE_MYMATH)
    add_library(SqrtLibrary STATIC mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)
    set_target_properties(SqrtLibrary PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})
    target_include_directories(SqrtLibrary PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
    target_compile_definitions(MathFunctions PRIVATE "LQTECH_USE_MYMATH")
endif()

# whoever link this library, include the ${CMAKE_CURRENT_SOURCE_DIR}
target_include_directories(MathFunctions INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

# link the tutorial_compiler_flags, means compile the library using c++ 11
target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

set(installable_libs MathFunctions tutorial_compiler_flags)
if(TARGET SqrtLibrary)
    list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs} EXPORT MathFunctionsTargets DESTINATION lib) # /usr/local/lin
install(FILES MathFunctions.h DESTINATION include) # /usr/local/include




#  sudo cmake --install cmake-build-debug --prefix "install3"