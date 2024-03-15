cmake_minimum_required(VERSION 3.19)

project(app)

add_executable(${PROJECT_NAME}  
src/car.cpp
src/car.hpp
src/main.cpp
src/dbhandler.hpp
src/dbhandler.cpp
src/util.hpp
src/util.cpp
)

find_package (SQLite3 REQUIRED)
if (SQLite3_FOUND)
  include_directories(${SQLite3_INCLUDE_DIRS})
  target_link_libraries (app ${SQLite3_LIBRARIES})
endif (SQLite3_FOUND)
