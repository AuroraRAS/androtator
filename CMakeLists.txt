cmake_minimum_required(VERSION 3.5)

project(androtator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Hamlib/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Hamlib/libs/${ANDROID_ABI}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Hamlib/libs/${ANDROID_ABI}/libhamlib.so" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/android-build/libs/${ANDROID_ABI}/")

find_package(QT NAMES Qt6 COMPONENTS Widgets Charts Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        polarwidget.cpp
        polarwidget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(androtator
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(androtator SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(androtator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    androtator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Network
    hamlib
    )
