#-------------------------------------------------
#
# Project created by QtCreator 2015-07-22T08:12:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qChess
TEMPLATE = app


SOURCES += main.cpp\
    GUI/gamewindow.cpp \
    Model/options.cpp \
    Model/board.cpp \
    Model/bitboard.cpp \
    Model/boardposition.cpp \
    Model/boardmove.cpp \
    Model/chessgame.cpp \
    Model/chessgamestate.cpp \
    Model/chessplayer.cpp \
    Model/chessplayers.cpp \
    Model/piece.cpp \
    Model/pieceset.cpp \
    Model/statsnapshot.cpp \
    Model/freefunctions.cpp

HEADERS  += GUI/gamewindow.h \
    Model/options.h \
    Model/board.h \
    Model/bitboard.h \
    Model/boardposition.h \
    Model/boardmove.h \
    Model/chessgame.h \
    Model/chessgamestate.h \
    Model/chessplayer.h \
    Model/chessplayers.h \
    Model/piece.h \
    Model/pieceset.h \
    Model/statsnapshot.h \
    Model/freefunctions.h

FORMS    += GUI/gamewindow.ui
CONFIG   += c++11
