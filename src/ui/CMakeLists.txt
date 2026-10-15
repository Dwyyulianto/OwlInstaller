qt_add_qml_module(ui_module
    URI AppUI
    VERSION 1.0
    QML_FILES main.qml
)
target_link_libraries(ui_module PUBLIC core_backend Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)