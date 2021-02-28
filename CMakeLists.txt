cmake_minimum_required(VERSION 3.0)

project(paillier)

set(SRCS
    main.c
    paillier.c
    )
    
set(HEADERS
    paillier.h
    )

add_executable(paillier ${SRCS} ${HEADERS})

target_link_libraries(paillier gmp)
install(TARGETS paillier DESTINATION bin)