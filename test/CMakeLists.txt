#-------------------------------------------------------------------------------------------
# Jorge López González
# DCPP Signals Test
#-------------------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(DCPPTaskManagerTest)

#-------------------------------------------------------------------------------------------
# Folder definitions
#-------------------------------------------------------------------------------------------
# Set the output folders where the program will be created
SET(DCPPTASKMANAGER_TEST_EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(DCPPTASKMANAGER_PATH ${PROJECT_SOURCE_DIR}/../project)

#-------------------------------------------------------------------------------------------
# Compiler Flags
#-------------------------------------------------------------------------------------------
# C++ Dialect
SET(CMAKE_CXX_STANDARD 11) # C++11...
SET(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
SET(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

#-------------------------------------------------------------------------------------------
# Library definition
#-------------------------------------------------------------------------------------------

SET(SOURCE
	src/main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE})

#-------------------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------------------

ADD_SUBDIRECTORY(${DCPPTASKMANAGER_PATH} ${PROJECT_BINARY_DIR}/dcpp_taskmanager)
INCLUDE_DIRECTORIES(${DCPPTASKMANAGER_PATH}/include)

ADD_DEPENDENCIES(${PROJECT_NAME} DCPPTaskManager)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	DCPPTaskManager
)

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------
# Set the location for executable installation
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${DCPPTASKMANAGER_TEST_EXECUTABLE_OUTPUT_PATH})









