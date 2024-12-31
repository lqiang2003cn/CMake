add_library(MathFunctions MathFunctions.cxx)

option(USE_MYMATH "Use tutorial provided math implementation")

# define a compile definition for MathFunctions
if(USE_MYMATH)
    add_library(SqrtLibrary STATIC mysqrt.cxx)
    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
    target_compile_definitions(MathFunctions PRIVATE "LQTECH_USE_MYMATH")
endif()