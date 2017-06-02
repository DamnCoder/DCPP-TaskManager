#-------------------------------------------------------------------------------------------
# Jorge López González
# DCPP Signals
#-------------------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(DCPPTaskManager)

#-------------------------------------------------------------------------------------------
# Folder definitions
#-------------------------------------------------------------------------------------------
# Set the output folders where the program will be created
SET(DCPPTASKMANAGER_LIB_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#-------------------------------------------------------------------------------------------
# Library definition
#-------------------------------------------------------------------------------------------
INCLUDE_DIRECTORIES(include)

SET(HEADERS
	include/task.h
	include/taskmanager.h
	include/thread.h
)

SET(SOURCES
	src/taskmanager.cpp
	src/thread.cpp
)


ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

#-------------------------------------------------------------------------------------------
# Compiler Flags
#-------------------------------------------------------------------------------------------
# C++ Dialect
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------
# Set the location for library installation
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${DCPPTASKMANAGER_LIB_OUTPUT_PATH})

# Copy the include directory where the lib is installed
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${DCPPTASKMANAGER_LIB_OUTPUT_PATH})

