cmake_minimum_required(VERSION 3.15)
project(workshop_boost_asio)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.67.0 REQUIRED COMPONENTS filesystem regex)
find_package(Threads REQUIRED)
include_directories(${BOOST_ROOT})
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_ROOT}/stage/lib)

add_executable(Server
	tcp_server_complet/tcp_connection.cpp
	tcp_server_complet/tcp_connection.hpp
	tcp_server_complet/tcp_server.cpp
	tcp_server_complet/tcp_server.hpp)

TARGET_LINK_LIBRARIES(Server ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(Server ${CMAKE_THREAD_LIBS_INIT})