cmake_minimum_required(VERSION 3.0)
project(LIBTENSOR CXX)

set(CMAKE_CXX_STANDARD 11)

if(NOT LIBUTIL_SOURCE_DIR)
set(LIBUTIL_SOURCE_DIR ${LIBTENSOR_SOURCE_DIR})
endif(NOT LIBUTIL_SOURCE_DIR)

if(NOT LIBTENSOR_DIR)
set(LIBTENSOR_DIR ${LIBTENSOR_SOURCE_DIR})
endif(NOT LIBTENSOR_DIR)

if(NOT LIBUTIL_DIR)
set(LIBUTIL_DIR ${LIBTENSOR_SOURCE_DIR})
endif(NOT LIBUTIL_DIR)

include(cmake/CheckFortranSourceCompiles.cmake)
include(cmake/CheckFortranSourceRuns.cmake)

if(LIBVMM_SOURCE_DIR)
    set(HAVE_LIBVMM TRUE)
else(LIBVMM_SOURCE_DIR)
    set(HAVE_LIBVMM FALSE)
    message(STATUS "Warning: libvmm was not found")
endif(LIBVMM_SOURCE_DIR)

if(LIBTENSOR_STANDALONE)
    include(${LIBUTIL_SOURCE_DIR}/cmake/SetupLibUtil.txt)
    if(HAVE_LIBVMM)
        include(${LIBVMM_SOURCE_DIR}/cmake/SetupLibVmm.txt)
    endif(HAVE_LIBVMM)
endif(LIBTENSOR_STANDALONE)
include(cmake/DepsLibTensor.txt)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    enable_testing()
endif()
if(LIBTENSOR_STANDALONE)
    add_subdirectory(libutil)
endif(LIBTENSOR_STANDALONE)

add_subdirectory(libtensor)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(tests)
endif()
#add_subdirectory(performance_tests)

if (LIBTENSOR_STANDALONE)
    install(
            TARGETS tensor util tensor_bto1 tensor_bto2 tensor_bto3 tensor_core tensor_dto tensor_so
            EXPORT libtensorTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            INCLUDES DESTINATION include/libtensor
            PUBLIC_HEADER DESTINATION include/libtensor
    )
    install(
            DIRECTORY libtensor/
            DESTINATION include/libtensor
            FILES_MATCHING PATTERN "*.h"
    )
    install(
            DIRECTORY libutil/
            DESTINATION include/libtensor/libutil
            FILES_MATCHING PATTERN "*.h"
    )
    install(
            EXPORT libtensorTargets
            FILE libtensorTargets.cmake
            NAMESPACE libtensor::
            DESTINATION lib/cmake/libtensor
    )
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            "libtensorConfigVersion.cmake"
            VERSION 0.0.0
            COMPATIBILITY SameMajorVersion
    )
    configure_package_config_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/libtensorConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/libtensorConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libtensor
    )
    install(
            FILES "${CMAKE_CURRENT_BINARY_DIR}/libtensorConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/libtensorConfigVersion.cmake"
            DESTINATION lib/cmake/libtensor
    )

endif ()