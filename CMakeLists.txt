cmake_minimum_required(VERSION 3.12)
project(hellocrashpad)

find_package(crashpad REQUIRED)

add_executable(hellocrashpad hello.cpp)
target_compile_features(hellocrashpad PUBLIC cxx_std_17)
target_link_libraries(hellocrashpad crashpad::crashpad)

install(TARGETS hellocrashpad RUNTIME DESTINATION bin)
install(PROGRAMS "${crashpad_LIB_DIRS}/../bin/crashpad_handler" DESTINATION bin)