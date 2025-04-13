cmake_minimum_required(VERSION 3.16)

project(sumVector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sumVector main.cpp
)

include(GNUInstallDirs)
install(TARGETS sumVector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
