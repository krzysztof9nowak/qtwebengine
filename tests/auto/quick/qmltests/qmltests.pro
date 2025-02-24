include($$QTWEBENGINE_OUT_ROOT/src/webenginequick/qtwebenginequick-config.pri) # workaround for QTBUG-68093
QT_FOR_CONFIG += webenginequick-private

include(../tests.pri)

QT += qmltest
DEFINES += QUICK_TEST_SOURCE_DIR=\\\"$$re_escape($$OUT_PWD$${QMAKE_DIR_SEP}webengine.qmltests)\\\"
IMPORTPATH += $$PWD/data

QML_TESTS = \
    $$PWD/data/tst_action.qml \
    $$PWD/data/tst_activeFocusOnPress.qml \
    $$PWD/data/tst_audioMuted.qml \
    $$PWD/data/tst_desktopBehaviorLoadHtml.qml \
    $$PWD/data/tst_download.qml \
    $$PWD/data/tst_findText.qml \
    $$PWD/data/tst_focusOnNavigation.qml \
    $$PWD/data/tst_fullScreenRequest.qml \
    $$PWD/data/tst_geopermission.qml \
    $$PWD/data/tst_getUserMedia.qml \
    $$PWD/data/tst_keyboardEvents.qml \
    $$PWD/data/tst_keyboardModifierMapping.qml \
    $$PWD/data/tst_loadHtml.qml \
    $$PWD/data/tst_loadProgress.qml \
    $$PWD/data/tst_loadRecursionCrash.qml \
    $$PWD/data/tst_loadUrl.qml \
    $$PWD/data/tst_mouseMove.qml \
    $$PWD/data/tst_navigationHistory.qml \
    $$PWD/data/tst_navigationRequested.qml \
    $$PWD/data/tst_newViewRequest.qml \
    $$PWD/data/tst_notification.qml \
    $$PWD/data/tst_profile.qml \
    $$PWD/data/tst_properties.qml \
    $$PWD/data/tst_runJavaScript.qml \
    $$PWD/data/tst_scrollPosition.qml \
    $$PWD/data/tst_settings.qml \
    $$PWD/data/tst_titleChanged.qml \
    $$PWD/data/tst_unhandledKeyEventPropagation.qml \
    $$PWD/data/tst_userScripts.qml \
    $$PWD/data/tst_viewSource.qml

qtConfig(webengine-webchannel) {
    QML_TESTS += $$PWD/data/tst_webchannel.qml
}

qtConfig(ssl) {
    include(../../shared/https.pri)
    QML_TESTS += $$PWD/data/tst_certificateError.qml
} else {
    include(../../shared/http.pri)
}

qtConfig(webenginequick-testsupport) {
    QML_TESTS += \
        $$PWD/data/tst_favicon.qml \
        $$PWD/data/tst_faviconDownload.qml \
        $$PWD/data/tst_inputMethod.qml \
        $$PWD/data/tst_javaScriptDialogs.qml \
        $$PWD/data/tst_linkHovered.qml \
        $$PWD/data/tst_loadFail.qml \
        $$PWD/data/tst_mouseClick.qml \
        $$PWD/data/tst_viewSoure.qml
} else {
    PLUGIN_EXTENSION = .so
    PLUGIN_PREFIX = lib
    macos: PLUGIN_PREFIX = .dylib
    win32 {
        PLUGIN_EXTENSION = .dll
        PLUGIN_PREFIX =
    }

    TESTSUPPORT_MODULE = $$shell_path($$[QT_INSTALL_QML]/QtWebEngine/testsupport/$${PLUGIN_PREFIX}qtwebenginetestsupportplugin$${PLUGIN_EXTENSION})
    BUILD_DIR = $$shell_path($$clean_path($$OUT_PWD/../../../..))
    SRC_DIR = $$shell_path($$clean_path($$PWD/../../../..))

    warning("QML Test Support API is disabled. This means some QML tests that use Test Support API will fail.")
    warning("Use the following command to build Test Support module and rebuild WebEngineView API:")
    warning("cd $$BUILD_DIR && qmake -r $$shell_path($$SRC_DIR/qtwebengine.pro -- --feature-testsupport=yes) && make -C $$shell_path($$BUILD_DIR/src/webengine) clean && make")
    warning("After performing the command above make sure QML module \"QtWebEngine.testsupport\" is deployed at $$TESTSUPPORT_MODULE")
}

qtHaveModule(quickcontrols) {
    QML_TESTS += \
        $$PWD/data/tst_contextMenu.qml \
        $$PWD/data/tst_filePicker.qml
}

OTHER_FILES += \
    $$PWD/data/TestWebEngineView.qml \
    $$PWD/data/accepttypes.html \
    $$PWD/data/alert.html \
    $$PWD/data/confirm.html \
    $$PWD/data/confirmclose.html \
    $$PWD/data/append-document-title.js \
    $$PWD/data/big-user-script.js \
    $$PWD/data/change-document-title.js \
    $$PWD/data/download.zip \
    $$PWD/data/directoryupload.html \
    $$PWD/data/favicon.html \
    $$PWD/data/favicon2.html \
    $$PWD/data/favicon-candidates-gray.html \
    $$PWD/data/favicon-misc.html \
    $$PWD/data/favicon-multi.html \
    $$PWD/data/favicon-multi-gray.html \
    $$PWD/data/favicon-single.html \
    $$PWD/data/favicon-shortcut.html \
    $$PWD/data/favicon-touch.html \
    $$PWD/data/favicon-unavailable.html \
    $$PWD/data/forms.html \
    $$PWD/data/geolocation.html \
    $$PWD/data/javascript.html \
    $$PWD/data/link.html \
    $$PWD/data/localStorage.html \
    $$PWD/data/multifileupload.html \
    $$PWD/data/redirect.html \
    $$PWD/data/script-with-metadata.js \
    $$PWD/data/singlefileupload.html \
    $$PWD/data/test1.html \
    $$PWD/data/test2.html \
    $$PWD/data/test3.html \
    $$PWD/data/test4.html \
    $$PWD/data/test-iframe.html \
    $$PWD/data/keyboardModifierMapping.html \
    $$PWD/data/keyboardEvents.html \
    $$PWD/data/titleupdate.js \
    $$PWD/data/icons/favicon.png \
    $$PWD/data/icons/gray128.png \
    $$PWD/data/icons/gray16.png \
    $$PWD/data/icons/gray255.png \
    $$PWD/data/icons/gray32.png \
    $$PWD/data/icons/gray64.png \
    $$PWD/data/icons/grayicons.ico \
    $$PWD/data/icons/qt144.png \
    $$PWD/data/icons/qt32.ico \
    $$PWD/data/icons/qtmulti.ico \
    $$PWD/data/icons/small-favicon.png \
    $$PWD/mock-delegates/QtWebEngine/Controls1Delegates/Menu.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls1Delegates/MenuItem.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls1Delegates/qmldir \
    $$PWD/mock-delegates/TestParams/FilePickerParams.qml \
    $$PWD/mock-delegates/TestParams/JSDialogParams.qml \
    $$PWD/mock-delegates/TestParams/qmldir \
    $$PWD/mock-delegates/QtWebEngine/Controls2Delegates/AlertDialog.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls2Delegates/ConfirmDialog.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls2Delegates/FilePicker.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls2Delegates/PromptDialog.qml \
    $$PWD/mock-delegates/QtWebEngine/Controls2Delegates/qmldir

OTHER_FILES += $$QML_TESTS

!build_pass:!isEmpty(QML_TESTS) {
    for (file, QML_TESTS): QML_TESTS_CONTENT += "$${file}"
    TEST_FILE = $$OUT_PWD/webengine.qmltests
    write_file($$TEST_FILE, QML_TESTS_CONTENT)
}

load(qt_build_paths)

