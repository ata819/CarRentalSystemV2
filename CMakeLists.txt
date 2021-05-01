cmake_minimum_required(VERSION 3.19)
project(CarRentalSystemV2)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.75.0 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(CarRentalSystemV2 main.cpp main.h displayFunc.cpp SQLiteDB.h)
target_link_libraries(CarRentalSystemV2 LINK_PUBLIC ${Boost_LIBRARIES} LINK_PUBLIC sqlite3)
