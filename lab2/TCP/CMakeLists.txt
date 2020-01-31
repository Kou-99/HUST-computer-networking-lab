cmake_minimum_required(VERSION 3.10)
project(TCP)



SET(CMAKE_C_COMPTLER GCC)
set(CMAKE_CXX FLAGS -fexec-charset=GBK)
add_definitions(-std=c++11)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test)
ADD_EXECUTABLE(tcp ${SRC_LIST} include/TCPReceiver.h include/TCPSender.h src/TCPSender.cpp src/TCPReceiver.cpp include/TCPSetting.h)
FIND_LIBRARY(NETSIM_LIB libnetsim.a ${PROJECT_SOURCE_DIR}/lib)
TARGET_LINK_LIBRARIES(tcp  ${NETSIM_LIB})