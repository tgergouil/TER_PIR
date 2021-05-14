cmake_minimum_required(VERSION 3.0)

project(paillier)

set(SRCS
    main.c
    paillier.c
    1-hypercube.c
    2-hypercube.c
    3-hypercube.c
    )
    
set(HEADERS
    paillier.h
    1-hypercube.h
    2-hypercube.h
    3-hypercube.h   
    )

add_executable(paillier   ${SRCS} ${HEADERS})
add_executable(1-hypercube  ${SRCS} ${HEADERS})
add_executable(2-hypercube  ${SRCS} ${HEADERS})
add_executable(3-hypercube  ${SRCS} ${HEADERS})
target_link_libraries(paillier  gmp)
target_link_libraries( 1-hypercube  gmp)
target_link_libraries( 2-hypercube  gmp)
target_link_libraries( 3-hypercube gmp)
install(TARGETS paillier  DESTINATION bin)
install(TARGETS 1-hypercube  DESTINATION bin)
install(TARGETS 2-hypercube  DESTINATION bin)
install(TARGETS 3-hypercube  DESTINATION bin)
