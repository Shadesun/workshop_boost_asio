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

add_executable(tcp_server
	tcp_server_complet/tcp_connection.cpp
	tcp_server_complet/tcp_connection.hpp
	tcp_server_complet/tcp_server.cpp
	tcp_server_complet/tcp_server.hpp)

TARGET_LINK_LIBRARIES(tcp_server ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(tcp_server ${CMAKE_THREAD_LIBS_INIT})

add_executable(tcp_client
	tcp_client_complet/tcp_client.cpp
	tcp_client_complet/tcp_client.hpp
	tcp_client_complet/tcp_connection.cpp
	tcp_client_complet/tcp_connection.hpp)

TARGET_LINK_LIBRARIES(tcp_client ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(tcp_client ${CMAKE_THREAD_LIBS_INIT})

add_executable(udp_server
	udp_server_complet/udp_server.cpp
	udp_server_complet/udp_server.hpp)

TARGET_LINK_LIBRARIES(udp_server ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(udp_server ${CMAKE_THREAD_LIBS_INIT})

add_executable(udp_client
	udp_client_complet/udp_client.cpp
	udp_client_complet/udp_client.hpp)

TARGET_LINK_LIBRARIES(udp_client ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(udp_client ${CMAKE_THREAD_LIBS_INIT})