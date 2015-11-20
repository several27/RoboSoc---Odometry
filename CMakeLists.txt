cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME Odometry)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH Odometry.ino)
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/tty.usbmodem1421)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})