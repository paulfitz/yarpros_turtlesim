project(yarpros_turtlesim)
cmake_minimum_required(VERSION 2.8.7)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)


find_package(YARP REQUIRED)

include(YarpRos)

include_directories(${CMAKE_BINARY_DIR}
                    ${YARP_INCLUDE_DIRS})


if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif()



yarpros_add_type(Velocity)
yarpros_add_type(Pose)
yarpros_add_type(TeleportAbsoluteIn)
yarpros_add_type(TeleportAbsoluteOut)
yarpros_add_type(TeleportRelativeIn)
yarpros_add_type(TeleportRelativeOut)
yarpros_add_type(EmptyIn)
yarpros_add_type(EmptyOut)
yarpros_add_type(SpawnIn)
yarpros_add_type(SpawnOut)
yarpros_add_type(KillIn)
yarpros_add_type(KillOut)
yarpros_add_type(SetPenIn)
yarpros_add_type(SetPenOut)


add_executable(yarpros_turtlesim main.cpp ${YARPROS_SOURCES})

target_link_libraries(yarpros_turtlesim YARP_OS YARP_init)
