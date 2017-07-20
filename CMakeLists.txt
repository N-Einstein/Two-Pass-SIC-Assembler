cmake_minimum_required(VERSION 3.7)
project(AssemblerSIC)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Validator.cpp Validator.h Pass1.cpp Pass1.h Pass2.cpp Pass2.h Loader.cpp Loader.h Command.cpp Command.h CommandCreator.cpp CommandCreator.h Directive.cpp Directive.h FileReader.cpp FileReader.h Instruction.cpp Instruction.h WrongComm.cpp WrongComm.h FileWriter.cpp FileWriter.h)
add_executable(AssemblerSIC ${SOURCE_FILES})