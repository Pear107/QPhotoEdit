cmake_minimum_required(VERSION 3.14)

project(QPhotoEdit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Charts)
find_package(OpenCV 4 REQUIRED)

file(GLOB APP_FILES "src/app/*")
file(GLOB PAINT_FILES "src/paint/*")
file(GLOB ALGORITHM_FILES "src/algorithm/*")
file(GLOB UTILS_FILES "src/utils/*")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
    QPhotoEdit
    src/main.cpp
    src/qml.qrc
    src/qtquickcontrols2.conf
    ${APP_FILES}
    ${PAINT_FILES}
    ${ALGORITHM_FILES}
    ${UTILS_FILES}
)

target_link_libraries(
    QPhotoEdit
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Charts
)
target_link_libraries(QPhotoEdit PRIVATE ${OpenCV_LIBS})
target_link_libraries(QPhotoEdit PRIVATE ${NCNN_LIBS})

link_directories(${OpenCV_LIBRARY_DIRS})
