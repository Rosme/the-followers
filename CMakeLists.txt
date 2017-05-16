# Copyright (C) - Jean-Sébastien Fauteux 2017
# This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to 
# Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

cmake_minimum_required(VERSION 2.8)

project(TheFollowers)

add_subdirectory(extlib/SFML)
include_directories(extlib/SFML/include)


if(UNIX)
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
	check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		MESSAGE(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use one that supports C++11.")
	endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("include")
include_directories(${SFML_INCLUDE_DIR})
include_directories("include/pugixml")

set(FollowCPP
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

set(FollowHPP
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

add_executable(TheFollowers
	${FollowHPP}
	${FollowCPP}
)

target_link_libraries(TheFollowers sfml-graphics sfml-window sfml-system sfml-main)

if(WIN32)
	set_target_properties(TheFollowers PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()
