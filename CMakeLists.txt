cmake_minimum_required(VERSION 3.22.1)
project(CurrencyDataBase)
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
        Charts
        Network
        REQUIRED)


add_executable(CurrencyDataBase
        ./src/main.cpp
        ./src/mainwindow.cpp
        ./src/mainwindow.ui
        ./src/insertbank.cpp
        ./src/insertbank.hpp
        ./src/insertbank.ui
        ./src/insertaccount.cpp
        ./src/insertaccount.hpp
        ./src/insertaccount.ui
        ./src/insertcurrency.cpp
        ./src/insertcurrency.hpp
        ./src/insertcurrency.ui
        ./src/stockmarket.cpp
        ./src/stockmarket.hpp
        ./src/stockmarket.ui
        ./src/transaction.cpp
        ./src/transaction.hpp
        ./src/transaction.ui
        ./src/ConnectionTool.cpp
        ./src/ConnectionTool.hpp
        ./src/auntification.cpp
        ./src/auntification.hpp
        ./src/auntification.ui
        src/registration.cpp
        src/registration.hpp
        src/registration.ui
        src/registration.cpp
        src/registration.hpp
        src/registration.ui
        src/managetables.cpp
        src/managetables.hpp
        src/managetables.ui)

target_link_libraries(CurrencyDataBase
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::Network
        ${PQXX_LIB} ${PQ_LIB}
)
