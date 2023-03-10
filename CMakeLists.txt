cmake_minimum_required(VERSION 3.14)

project(RaceGame)

include_directories(
        RaceApp/headers
        RaceApp/src
        RaceLib/src        
        RaceLib/includes
)

file(GLOB Lib_SRCS
        "RaceLib/src/*.cpp"
        "RaceLib/includes/*.h"
        )

file(GLOB App_SRCS
        "RaceApp/src/*.cpp"
        "RaceApp/headers/*.h"
        )
		
configure_file(RaceApp/resources/botnames.txt Debug/botnames.txt COPYONLY)
configure_file(RaceApp/resources/botcallsigns.txt Debug/botcallsigns.txt COPYONLY)

add_library(RaceLib SHARED ${Lib_SRCS})

add_executable(RaceGame ${App_SRCS})

target_link_libraries(RaceGame RaceLib)