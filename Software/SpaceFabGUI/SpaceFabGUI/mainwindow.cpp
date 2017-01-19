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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

//Starting condition:
//server_status OFF: SpaceFabServer is supposed to be switched off.
//active_geobrick -1: No active geobrick
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setting up GUI
    ui->setupUi(this);

    //This variable records the status of the SpaceFabServer (ON/OFF)

    //initial condition: server_status OFF
    server_status = OFF;

    //This variable records the number of the active GeoBrick (1 or 2)
    //If active_geobrick != 1 or active_geobrick != 2, no GeoBrick is operative
    //The user can modify this variable with the methods on_ConnectToGeobrickButton_1_clicked
    //and on_ConnectToGeobrickButton_2_clicked, triggered by the buttons "Connect to GeoBrick 1"
    //and "Connect to GeoBrick 2".
    //This variable influences the string being sent to the server:
    //for example, if the GeoBrick 2 is active, commands sent to the server will refer to GeoBrick 2.
    //(ex. 2:&2q71 where "2:" are the characters added by the GUI to the string insered by the user in the expert mode).

    //no active geobrick
    active_geobrick = -1;

    _pSocket = new QTcpSocket( this );

    _pSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    //Binding CollSoft socket with readTcpData() and with Error SLOT
    connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );
    connect( _pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Errore(QAbstractSocket::SocketError)));

}

//Support function to separate the commands contained in a message.
std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}


MainWindow::~MainWindow()
{
    delete ui;
}

//Method called by the GUI when the user press' the blue button "i".
//StatusQuestion is a ClickableLabel defined by the files clickablelabel.h and
//clickablelabel.cpp . It emits the clicked signal when the user clicked on it.
void MainWindow::on_StatusQuestion_clicked()
{
    Dialog* dialog = new Dialog();
    dialog->exec();
}

//This slot is used to catch the errors from the TCP/IP communication between the ExpertGUI and the SpaceFabServer.
void MainWindow::Errore(QAbstractSocket::SocketError sock_error)
{
    QString data_string;
    data_string += "Error communicating with SpaceFabServer: " + _pSocket->errorString() + "\n";

    AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);
}

//This methods analyze the input sent to this GUI from the server
void MainWindow::readTcpData()
{
    //Reading the message
    QByteArray data = _pSocket->readAll();

    QString data_string(data);

    //Prints the list of the physical devices connected with the CollSoft server
    QRegularExpression re1("^Connection okay to GeoBrick 1");
    //QRegularExpressionMatch match = re1.match(data_string);

    if (re1.match(data_string).hasMatch()) {

        ui->GeobrickConnectedLabel->setText("    Connected to Geobrick 1");
        //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

    }

    re1.setPattern("^Connection okay to GeoBrick 2");

    if (re1.match(data_string).hasMatch()) {
         ui->GeobrickConnectedLabel->setText("    Connected to Geobrick 2");

        //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

    }

    re1.setPattern("^Connection failed to GeoBrick");

    if (re1.match(data_string).hasMatch()) {
         ui->GeobrickConnectedLabel->setText("    Disconnected");

        //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

    }

    re1.setPattern("^Disconnection to Geobrick 1 okay!");

    if (re1.match(data_string).hasMatch()) {
         ui->GeobrickConnectedLabel->setText("    Disconnected");

        //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

    }

    re1.setPattern("^Disconnection to Geobrick 2 okay!");

    if (re1.match(data_string).hasMatch()) {
         ui->GeobrickConnectedLabel->setText("    Disconnected");

        //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

    }

    //Extracting the commands from the message
    string tmp(data_string.toUtf8().constData());
    auto command_list = explode(tmp, '\n');

    //Passing through the command list
    for ( int tmpi = 0; tmpi < command_list.size() ; tmpi ++)
    {
        QString data_string(command_list[tmpi].c_str());

        re1.setPattern("^q70 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_1->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q77 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_2->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q78 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_3->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q79 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_4->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q87 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_5->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q88 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_6->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q89 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_7->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q94 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_8->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q95 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_9->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^q96 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_10->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^p91 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_11->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

        re1.setPattern("^p80 = ");

        if (re1.match(data_string).hasMatch()) {
             ui->variable_label_12->setText("    " + data_string);

            //AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

        }

    }

    AppendMessageToQtextEdit(ui->textEditExpertMode, data_string);

}

//This method allows the user to switch the SpaceFab server on and off.
//It is used the global variable ServerOnOff to record the information about the availability
//of the server
//ServerOnOff = ON means the server is online
//ServerOnOff = OFF means the server is offline
void MainWindow::on_ServerOnOffButton_clicked()
{
    //Variable to store the result of the query.
    //OKAY = Query executed correctly
    //FAILED = Query execution failed
    bool query_result = FAILED;

    //Socket to communicate with CollSoft program
    QTcpSocket* _pSocket_1 = new QTcpSocket( this );

    //Disabling Nagle algorithm in order to have real time response from Server
    _pSocket_1->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    _pSocket_1->connectToHost(SPACEFAB_EXISTENCE_IP, (quint16)SPACEFAB_EXISTENCE_PORT);

    _pSocket_1->waitForConnected(1000);

    //Disabling Nagle algorithm in order to have real time response from Server
    _pSocket_1->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    if(_pSocket_1->waitForReadyRead(1000))
    {
        _pSocket_1->readAll();

        //Variable to store the message to send to the CheckExistenxe server.
        QString tmp;

        if (server_status == OFF)
        {
            //Procedura per aggiornare i dati
            tmp = "On";
        }
        else
        {
            tmp = "Off";
            _pSocket->disconnectFromHost();
        }

        QByteArray data(tmp.toUtf8());
        _pSocket_1->write( data );

        if(_pSocket_1->waitForReadyRead(1000))
        {
            QByteArray data_1 = _pSocket_1->readAll();
            QString data_string(data_1);

            //If the server has sent a response to connect programmerpath command:
            QRegularExpression re1;
            QRegularExpressionMatch match;

            //If the server has sent a response to a get_pos_status
            if (server_status == OFF)
            {
                re1.setPattern("(SpaceFabServer is already running)|(New SpaceFabServer process created successfully)");
            }
            else
            {
                re1.setPattern("(...SpaceFabServer processed killed)|(SpaceFabServer process is not running)");
            }

            match = re1.match(data_string);

            if (re1.match(data_string).hasMatch())
            {

                //GeneralDialog* dialog_1 = new GeneralDialog("<html><b style=\" font-size:14pt; color:#007700;\">Connection with the programmer okay!</b</html>");
                //dialog_1->ui->label->setPixmap(QPixmap(":Enable.png"));
                //dialog_1->show();

                query_result = OKAY;

                _pSocket_1->disconnectFromHost();

            }
            else
            {

                //GeneralDialog* dialog_1 = new GeneralDialog(data_string);
                //dialog_1->ui->label->setPixmap(QPixmap(":Disable.png"));
                //dialog_1->show();

                _pSocket_1->disconnectFromHost();

            }
        }
    }

    if (query_result == OKAY && server_status == OFF)
    {
        ui->ServerLabel->setText("    Server On");
        ui->ServerOnOffButton->setText("Switch off server");

        server_status = ON;

        _pSocket->connectToHost(SPACEFAB_SERVER_IP, (quint16)SPACEFAB_SERVER_PORT);
        if( _pSocket->waitForConnected(1000) ) {
            ;
        }
    }
    else if (query_result == OKAY && server_status == ON)
    {
        ui->ServerLabel->setText("    Server Off");
        ui->ServerOnOffButton->setText("Switch on server");

        server_status = OFF;
    }
    else if (query_result == FAILED)
    {
        ui->ServerLabel->setText("    Server Off");
        ui->ServerOnOffButton->setText("Switch on server");

        server_status = OFF;
    }
}

//Method called by the GUI when the user press' the "Connect to GeoBrick 1" button.
void MainWindow::on_ConnectToGeobrickButton_1_clicked()
{
    QString tmp = "connect_1\n";

    QByteArray data(tmp.toUtf8());
    _pSocket->write( data );

    active_geobrick = 1;
}

//Method called by the GUI when the user press' the "Connect to GeoBrick 2" button.
void MainWindow::on_ConnectToGeobrickButton_2_clicked()
{
    QString tmp = "connect_2\n";

    QByteArray data(tmp.toUtf8());
    _pSocket->write( data );

    active_geobrick = 2;
}

//Method called by the GUI when the user press' the "Send" button in the "Expert mode - SpaceFab" tab.
void MainWindow::on_SendCommandButton_clicked()
{
    QString tmp = QString::number(active_geobrick) + ":" + ui->lineEditExpertMode->text();

    QByteArray data(tmp.toUtf8());
    _pSocket->write( data );
}

//This function print the message contained in Message QString at the bottom of the QTextEdit pointed by MexArea
void MainWindow::AppendMessageToQtextEdit(QTextEdit* MexArea, QString Message)
{
    //Message += "\n---------------------";

    //QString PromptMessage("> ");

    MexArea->append("> " + Message);
    QTextCursor c2 =  MexArea->textCursor();
    c2.movePosition(QTextCursor::End);
    MexArea->setTextCursor(c2);
    MexArea->ensureCursorVisible();
}

//Method called when the user press' the button "Update" in order to refresh the values of the variables
//shown in the "Expert mode - SpaceFab" tab.
void MainWindow::on_RetrieveCommonVariables_clicked()
{
    QString tmp = "retrieve_" + QString::number(active_geobrick) + '\n';

    QByteArray data(tmp.toUtf8());
    _pSocket->write( data );
}

//Method called when the user press' the button "Diconnect Geobrick"v
void MainWindow::on_DisconnectToGeobrick_clicked()
{
    if (active_geobrick == 1)
    {
        QString tmp = "disconnect_1";

        QByteArray data(tmp.toUtf8());
        _pSocket->write( data );

        active_geobrick = -1;
    }
    else if (active_geobrick == 2)
    {
        QString tmp = "disconnect_2";

        QByteArray data(tmp.toUtf8());
        _pSocket->write( data );

        active_geobrick = -1;
    }
}
