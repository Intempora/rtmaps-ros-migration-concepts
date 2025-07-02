cmake_minimum_required(VERSION 3.5)

set(PCK ros_to_rtmaps)
project(${PCK})

if (NOT DEFINED RTMAPS_SDKDIR)  # If -D"RTMAPS_SDKDIR=<RTMaps Install Dir>" has NOT been passed to the "cmake" command
    if (DEFINED ENV{RTMAPS_SDKDIR})  # Try to use the default RTMaps installation
        set(RTMAPS_SDKDIR "$ENV{RTMAPS_SDKDIR}" CACHE PATH "Path the RTMaps installation directory")
    else()
        message(FATAL_ERROR "RTMAPS_SDKDIR not defined. Either pass -D\"RTMAPS_SDKDIR=...\" to CMake or define an RTMAPS_SDKDIR environment variable")
    endif()
endif()

include("${RTMAPS_SDKDIR}/templates.u/rtmaps.cmake")

set(SOURCE
   ${CMAKE_CURRENT_SOURCE_DIR}/minimal_publisher_cpp/rtmaps_minimal_publisher.h
   ${CMAKE_CURRENT_SOURCE_DIR}/minimal_publisher_cpp/rtmaps_minimal_publisher.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/minimal_subscriber_cpp/rtmaps_minimal_subscriber.h
   ${CMAKE_CURRENT_SOURCE_DIR}/minimal_subscriber_cpp/rtmaps_minimal_subscriber.cpp
)
    
add_rtmaps_package(${PCK} PCKINFO "${PCK}.pckinfo"
    ${SOURCE}
)

target_link_libraries(${PCK} rtmaps_input_reader)

