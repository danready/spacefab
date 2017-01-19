// GNU General Public License Agreement
// Copyright (C) 2015-2016 Daniele Berto daniele.fratello@gmail.com
//
// spacefab is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation.
// You must retain a copy of this licence in all copies.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextEdit>

#include "DefineGeneral.h"
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //Method called by the GUI when the user press' the blue button "i".
    //StatusQuestion is a ClickableLabel defined by the files clickablelabel.h and
    //clickablelabel.cpp . It emits the clicked signal when the user clicked on it.
    void on_StatusQuestion_clicked();

    //Method called by the GUI when the user press' the Switch On/Off Button
    void on_ServerOnOffButton_clicked();

    //Method called by the GUI when the user press' the "Connect to GeoBrick 1" button.
    void on_ConnectToGeobrickButton_1_clicked();

    //Method called by the GUI when the user press' the "Connect to GeoBrick 2" button.
    void on_ConnectToGeobrickButton_2_clicked();

    //Method called by the GUI when the user press' the "Send" button in the "Expert mode - SpaceFab" tab.
    void on_SendCommandButton_clicked();

    //Method called when the GUI receives a TCP/IP input.
    void readTcpData();

    //Method called when the GUI receives an error from the TCP/IP input intereface.
    void Errore(QAbstractSocket::SocketError sock_error);

    //Method called when the user press' the button "Update" in order to refresh the values of the variables
    //shown in the "Expert mode - SpaceFab" tab.
    void on_RetrieveCommonVariables_clicked();

    //Method called when the user press' the button "Diconnect Geobrick"
    void on_DisconnectToGeobrick_clicked();

private:
    Ui::MainWindow *ui;

    //This variable records the status of the SpaceFabServer (ON/OFF)
    bool server_status;

    //This variable records the number of the active GeoBrick (1 or 2)
    //If active_geobrick != 1 or active_geobrick != 2, no GeoBrick is operative
    //The user can modify this variable with the methods on_ConnectToGeobrickButton_1_clicked
    //and on_ConnectToGeobrickButton_2_clicked, triggered by the buttons "Connect to GeoBrick 1"
    //and "Connect to GeoBrick 2".
    //This variable influences the string being sent to the server:
    //for example, if the GeoBrick 2 is active, commands sent to the server will refer to GeoBrick 2.
    //(ex. 2:&2q71 where "2:" are the characters added by the GUI to the string insered by the user in the expert mode).
    int active_geobrick;

    QTcpSocket* _pSocket;

    //This function print the message contained in Message QString at the bottom of the QTextEdit pointed by MexArea
    void AppendMessageToQtextEdit(QTextEdit* MexArea, QString Message);
};

#endif // MAINWINDOW_H
