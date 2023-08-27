cmake_minimum_required(VERSION 3.15)

set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(metafunctions VERSION ${PROJECT_VESRION})

set(CMAKE_BUILD_TYPE Debug)

add_executable(metafunctions metafunc.cpp)

set_target_properties(metafunctions PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(metafunctions PRIVATE
        /W4
    )
else ()
    target_compile_options(metafunctions PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS metafunctions RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)