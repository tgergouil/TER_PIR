cmake_minimum_required(VERSION 3.0)

project(testPIR)

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

add_executable(paillier   ${SRCS} ${HEADERS})
add_executable(Dimension-1  ${SRCS} ${HEADERS})
add_executable(Dimension-2  ${SRCS} ${HEADERS})
add_executable(Dimension-3  ${SRCS} ${HEADERS})
target_link_libraries(paillier  gmp)
target_link_libraries(Dimension-1  gmp)
target_link_libraries(Dimension-2  gmp)
target_link_libraries(Dimension-3 gmp)
install(TARGETS paillier  DESTINATION bin)
install(TARGETS Dimension-1  DESTINATION bin)
install(TARGETS Dimension-2  DESTINATION bin)
install(TARGETS Dimension-3  DESTINATION bin)
