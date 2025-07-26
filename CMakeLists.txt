cmake_minimum_required(VERSION 3.16)
project(queseriaSupport)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_WIN32_EXECUTABLE ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Подключаем cpr через FetchContent
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.2
)
FetchContent_MakeAvailable(cpr)

# Основные файлы
add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    settingwindow.cpp
    settingwindow.h
    settingwindow.ui
    fonts/github.png fonts/information.png fonts/Montserrat-SemiBold.ttf fonts/resources.qrc fonts/telegram.png fonts/Unbounded-Black.ttf
    processwindow.ui
    processwindow.cpp processwindow.h
)

# Добавляем исходники из src/
target_sources(${PROJECT_NAME} PRIVATE
    src/checkCookie.cpp
    src/isItCorrect.cpp
    src/workWithCout.cpp
    src/parseFunpay.cpp
    src/classOrderInfo.cpp
    src/deleteExcessId.cpp
    src/supportAppeal.cpp
    include/checkCookie.h include/isItCorrect.h include/workWithCout.h include/parseFunpay.h include/classOrderInfo.h include/deleteExcessId.h
    include/supportAppeal.h  include/mytextedit.h
)

# Подключаем include/
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Линкуем Qt и cpr
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    cpr::cpr
)
