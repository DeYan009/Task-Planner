# cmake_minimum_required(VERSION 3.21)
# project(TP LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# set(CMAKE_PREFIX_PATH "E:/qt2/6.9.1/msvc2022_64")
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# qt_add_executable(TP
#     main.cpp
#     mainwindow.cpp
#     mainwindow.h
# )

# target_link_libraries(TP PRIVATE
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Widgets
# )

# if(WIN32)
#     set_target_properties(TP PROPERTIES WIN32_EXECUTABLE TRUE)
# endif()

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.21)
project(TP LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Путь к Qt
set(CMAKE_PREFIX_PATH "E:/qt2/6.9.1/msvc2022_64")

# Поиск компонентов Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Создание исполняемого файла
qt_add_executable(TP
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

# Подключение Qt модулей
target_link_libraries(TP PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Настройки для Windows
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Для Debug-сборки
    add_custom_command(TARGET TP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Cored.dll"
            $<TARGET_FILE_DIR:TP>
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Guid.dll"
            $<TARGET_FILE_DIR:TP>
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Widgetsd.dll"
            $<TARGET_FILE_DIR:TP>
        COMMENT "Копирование Debug DLL"
    )
elseif(WIN32)
    # Для Release-сборки
    add_custom_command(TARGET TP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Core.dll"
            $<TARGET_FILE_DIR:TP>
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Gui.dll"
            $<TARGET_FILE_DIR:TP>
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Widgets.dll"
            $<TARGET_FILE_DIR:TP>
        COMMENT "Копирование Release DLL"
    )
endif()