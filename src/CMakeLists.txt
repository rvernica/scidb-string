find_package(Boost REQUIRED)
find_package(Scidb REQUIRED)

find_file(LOG4CXX_INCLUDE_DIR
  log4cxx/logger.h
  )

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LOG4CXX_INCLUDE_DIR})
include_directories(${SCIDB_INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SCIDB_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -rdynamic")

add_library(string SHARED string.cpp)
