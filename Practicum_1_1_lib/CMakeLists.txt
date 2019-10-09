project(Practicum_1_1)

set(HEADER_FILES pi_cluster.h)
set(SOURCE_FILES pi_cluster.cpp)

add_library(Practicum_1_1_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
