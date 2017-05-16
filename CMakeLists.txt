# Copyright (C) - Jean-S�bastien Fauteux 2014
# This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
# Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(TheFollowers)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

FIND_PACKAGE(SFML 2 COMPONENTS graphics window system main)

IF(SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
ELSE()
	SET(SFML_ROOT "" CACHE PATH "SFML Top-Level Directory")
	MESSAGE("\n -> SFML Directory not found.")
ENDIF()

IF(UNIX)
	INCLUDE(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	ELSEIF(COMPILER_SUPPORTS_CXX0X)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	ELSE()
		MESSAGE(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use one that supports C++11.")
	ENDIF()
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES("include")
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
INCLUDE_DIRECTORIES("include/pugixml")

LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

SET(FollowCPP
	./src/blue.cpp
	./src/brown.cpp
	./src/ennemi.cpp
	./src/error.cpp
	./src/eventmanager.cpp
	./src/level.cpp
	./src/main.cpp
	./src/menu.cpp
	./src/mine.cpp
	./src/ressources.cpp
	./src/runner.cpp
	./src/score.cpp
	./src/timer.cpp
	./src/tombstone.cpp
	./src/unit.cpp
	./src/window.cpp
	./src/pugixml/pugixml.cpp
)

SET(FollowHPP
	./include/blue.h
	./include/brown.h
	./include/ennemi.h
	./include/error.h
	./include/eventmanager.h
	./include/level.h
	./include/menu.h
	./include/mine.h
	./include/ressource.h
	./include/runner.h
	./include/score.h
	./include/timer.h
	./include/tombstone.h
	./include/unit.h
	./include/window.h
    ./include/pugixml/pugiconfig.hpp
    ./include/pugixml/pugixml.hpp
)

source_group("Header Files" FILES ${FollowHPP})
source_group("Source Files" FILES ${FollowCPP})

ADD_EXECUTABLE(TheFollowers
	${FollowHPP}
	${FollowCPP}
)

TARGET_LINK_LIBRARIES(TheFollowers ${SFML_LIBRARIES})

if(WIN32)
	SET_TARGET_PROPERTIES(TheFollowers PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()
