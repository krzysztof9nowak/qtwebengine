TEMPLATE = app

# FIXME: Re-enable once we want to run tests on the CI
# CONFIG += testcase

CONFIG += c++11

VPATH += $$_PRO_FILE_PWD_
TARGET = tst_$$TARGET

SOURCES += $${TARGET}.cpp
INCLUDEPATH += $$PWD

QT += testlib network webenginewidgets widgets
osx: CONFIG -= app_bundle

# This define is used by some tests to look up resources in the source tree
DEFINES += TESTS_SOURCE_DIR=\\\"$$PWD/\\\"
