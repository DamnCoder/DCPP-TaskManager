#-------------------------------------------------------------------------------------------
# Jorge López González
# DCPP Multithread Task Manager
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(dcpp_mttaskmanager)

#-------------------------------------------------------------------------------------------
# Library definition
#-------------------------------------------------------------------------------------------
include_directories(include)

set(HEADERS
    include/task.h
    include/taskmanager.h
    include/thread.h
)

set(SOURCES
    src/task.cpp
    src/taskmanager.cpp
    src/thread.cpp
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# setup include directories 
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# setup export preprocessor definitions
if(BUILD_SHARED_LIBS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE DCPPMTTM_EXPORTS) 
  target_compile_definitions(${PROJECT_NAME} INTERFACE DCPPMTTM_IMPORTS) 
endif()

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME} 
    EXPORT fareweller_export
    RUNTIME DESTINATION bin 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
)
