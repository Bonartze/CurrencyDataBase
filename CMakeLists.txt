cmake_minimum_required(VERSION 3.26)
project(untitled87)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


add_executable(untitled87
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        insertbank.cpp
        insertbank.hpp
        insertbank.ui
        insertaccount.cpp
        insertaccount.hpp
        insertaccount.ui
        insertcurrency.cpp
        insertcurrency.hpp
        insertcurrency.ui
        stockmarket.cpp
        stockmarket.hpp
        stockmarket.ui
        transaction.cpp
        transaction.hpp
        transaction.ui)

target_link_libraries(untitled87
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${PQXX_LIB} ${PQ_LIB}
)
