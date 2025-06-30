cmake_minimum_required(VERSION 3.26.3)

 project(committee C)

 add_executable(committee ../test/main.c)

 SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_test(
  NAME TestClientZmq
 COMMAND "LD_PRELOAD=../lib/libzmq/build/lib/libzmq.so Test")
