cmake_minimum_required(VERSION 2.8)
project(daemonmonitor)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  cmake_policy(SET CMP0068 NEW)
  SET(CMAKE_MACOSX_RPATH ON)
  SET(CMAKE_INSTALL_RPATH "@loader_path")
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  SET(PLATFORM_LINKER_FLAGS "-Wl,-dead_strip")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(PLATFORM_LINKER_FLAGS "-Wl,-rpath,./ -s -Wl,--gc-sections -Wl,--as-needed -lpthread")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

endif()

SET(CMAKE_C_FLAGS "-std=c11")
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath \$<))\"'")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

FILE(GLOB PK_SOURCES "src/proktord/*" "src/app/*" "src/common/*")
ADD_LIBRARY(proktor STATIC ${PK_SOURCES})

TARGET_INCLUDE_DIRECTORIES(proktor PUBLIC "src/proktord/inc" "src/app/inc" "src/common/inc" "lib")

FILE(GLOB SOURCES_PROCTOR "src/app/proktor.cpp")
ADD_EXECUTABLE(test_proktor ${SOURCES_PROCTOR})
TARGET_LINK_LIBRARIES(test_proktor proktor ${PLATFORM_LINKER_FLAGS})

FILE(GLOB SOURCES_TEST_PROC "test/cpp/loop.cpp")
ADD_EXECUTABLE(test_loop ${SOURCES_TEST_PROC})
TARGET_LINK_LIBRARIES(test_loop proktor ${PLATFORM_LINKER_FLAGS})

FILE(GLOB SOURCES_TEST_PROC "test/execute_sys_call.cpp")
ADD_EXECUTABLE(test_execute_sys_call ${SOURCES_TEST_PROC})