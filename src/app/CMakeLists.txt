qt_add_executable(boardgame
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

target_link_libraries(boardgame PRIVATE Qt6::Widgets)

set_target_properties(boardgame PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)