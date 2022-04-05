cmake_minimum_required(VERSION 3.21)
project(extension_example)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SystemC "2.3.3" REQUIRED)

add_executable(extension_example main.cpp Initiator.cpp Target.cpp common_extension.cpp)
target_compile_features(extension_example PUBLIC cxx_std_11)
target_link_libraries(extension_example PRIVATE ${SYSTEMC_LIBRARIES})
target_include_directories(extension_example PRIVATE ${SYSTEMC_INCLUDE_DIRS})