cmake_minimum_required(VERSION 3.0)

project(testPIR C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

set(SRCS
    main.c
    paillier.c
    Dimension-1.c
    Dimension-2.c
    Dimension-3.c
    )
    
set(HEADERS
    paillier.h
    Dimension-1.h
    Dimension-2.h
    Dimension-3.h   
    )

add_executable(testPIR   ${SRCS} ${HEADERS})
target_link_libraries(testPIR  gmp)
