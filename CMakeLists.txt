cmake_minimum_required(VERSION 3.24)
project(csvreader)

set(CMAKE_CXX_STANDARD 17)

add_executable(csvreader main.cpp modules/error.h modules/csvfilereader.h modules/csvfilereader.cpp modules/expression.h modules/expression.cpp modules/simplearithmetics.cpp modules/simplearithmetics.h modules/CSVParser.cpp modules/CSVParser.h modules/print.h modules/csvvalidator.cpp modules/csvvalidator.h)
