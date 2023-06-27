cmake_minimum_required(VERSION 3.16)
project(ts4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/PEGParser)

set(PROJECT_LINK_LIBS libPEGParser.a)
link_directories(deps/PEGParser/build)

set(PEG_DIRECTORY deps/PEGParser/include)
set(SOURCES ts4.cpp ${PEG_DIRECTORY}/peg_parser/generator.h)
add_executable(ts4 ${SOURCES})

target_include_directories(ts4 PRIVATE ${PEG_DIRECTORY})
target_link_libraries(ts4 ${PROJECT_LINK_LIBS})
