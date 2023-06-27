cmake_minimum_required(VERSION 3.16)
project(ts4)

set(CMAKE_CXX_STANDARD 17)

# PEG Library
add_subdirectory(deps/PEGParser)
set(PROJECT_LINK_LIBS libPEGParser.a)
link_directories(deps/PEGParser/build)

# Include directory
set(PEG_DIRECTORY deps/PEGParser/include)
set(INC_DIRECTORY include)

set(TS_SRC src/tick.cpp)
set(SOURCES ts4.cpp ${TS_SRC} ${PEG_DIRECTORY}/peg_parser/generator.h ${INC_DIRECTORY}/tick.h)
add_executable(ts4 ${SOURCES})

target_include_directories(ts4 PRIVATE ${PEG_DIRECTORY} ${INC_DIRECTORY})
target_link_libraries(ts4 ${PROJECT_LINK_LIBS})
