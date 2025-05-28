set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)  # <- to jest kluczowe
set(CMAKE_AUTOUIC ON)

qt_add_resources(RESOURCES imgs.qrc)


qt_add_executable(boardgame
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    GameController.cpp
    ${RESOURCES}
)

target_link_libraries(boardgame PRIVATE Qt6::Widgets richpp)

set_target_properties(boardgame PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)
