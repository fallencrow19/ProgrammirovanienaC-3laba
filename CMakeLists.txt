cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(containers VERSION ${PROJECT_VESRION})

add_executable(containers main.cpp containers.cpp)

set_target_properties(containers PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(containers PRIVATE
        /W4
    )
else ()
    target_compile_options(containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (UNIX)
    set(CPACK_GENERATOR DEB)
else()
    set(CPACK_GENERATOR ZIP)
endif()

install(TARGETS containers RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)