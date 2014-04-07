# Copyright (C) - Jean-Sébastien Fauteux 2014
# This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
# Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(APP_NAME "The Followers")

project(${APP_NAME})

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

FIND_PACKAGE(SFML 2 COMPONENTS graphics window system main)

IF(SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
ELSE()
	SET(SFML_ROOT "" CACHE PATH "SFML Top-Level Directory")
	MESSAGE("\n -> SFML Directory not found.")
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES("include")
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

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
)

source_group("Header Files" FILES ${FollowHPP})
source_group("Source Files" FILES ${FollowCPP})

ADD_EXECUTABLE(${APP_NAME}
	${FollowHPP}
	${FollowCPP}
)

TARGET_LINK_LIBRARIES(${APP_NAME} ${SFML_LIBRARIES} pugixml.lib)

SET_TARGET_PROPERTIES(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS") 
