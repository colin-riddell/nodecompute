include_directories(${CMAKE_SRC_DIR}../node/)

include_directories(${CMAKE_SRC_DIR}../node/deps/v8/src)

add_executable(app src/nodecompute.cc src/ocl.cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I../../node/src")