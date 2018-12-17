cmake_minimum_required(VERSION 3.8)
project(proj1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        riscvcode/code/multiply.input
        riscvcode/code/random.input
        riscvcode/code/simple.input
        riscvcode/ref/multiply.solution
        riscvcode/ref/multiply.trace
        riscvcode/ref/random.solution
        riscvcode/ref/random.trace
        riscvcode/ref/simple.solution
        riscvcode/ref/simple.trace
        Makefile
        part1.c
        part2.c
        riscv.c
        riscv.h
        types.h
        utils.c
        utils.h)

add_executable(proj1 ${SOURCE_FILES})