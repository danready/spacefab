/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <clickablelabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QPushButton *ServerOnOffButton;
    QLabel *ServerLabel;
    ClickableLabel *StatusQuestion;
    QPushButton *ConnectToGeobrickButton_1;
    QLabel *GeobrickConnectedLabel;
    QPushButton *ConnectToGeobrickButton_2;
    QPushButton *DisconnectToGeobrick;
    QTabWidget *tabWidgetMain;
    QWidget *tabUserInterface;
    QWidget *tabSpaceFabExpert;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *variable_label_8;
    QLabel *variable_label_9;
    QLabel *variable_label_3;
    QLabel *variable_label_11;
    QLabel *variable_label_2;
    QLabel *variable_label_7;
    QPushButton *SendCommandButton;
    QTextEdit *textEditExpertMode;
    QLabel *variable_label_4;
    QLabel *variable_label_6;
    QLabel *variable_label_12;
    QLabel *variable_label_5;
    QLabel *variable_label_1;
    QLineEdit *lineEditExpertMode;
    QLabel *variable_label_10;
    QPushButton *RetrieveCommonVariables;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(556, 623);
        QIcon icon;
        icon.addFile(QStringLiteral(":/product-SMALL-geo-pmac.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, -1, -1, 10);
        ServerOnOffButton = new QPushButton(centralWidget);
        ServerOnOffButton->setObjectName(QStringLiteral("ServerOnOffButton"));
        ServerOnOffButton->setMinimumSize(QSize(171, 41));
        ServerOnOffButton->setMaximumSize(QSize(171, 41));
        ServerOnOffButton->setAutoDefault(false);
        ServerOnOffButton->setFlat(false);

        gridLayout_2->addWidget(ServerOnOffButton, 0, 0, 1, 1);

        ServerLabel = new QLabel(centralWidget);
        ServerLabel->setObjectName(QStringLiteral("ServerLabel"));

        gridLayout_2->addWidget(ServerLabel, 0, 1, 1, 1);

        StatusQuestion = new ClickableLabel(centralWidget);
        StatusQuestion->setObjectName(QStringLiteral("StatusQuestion"));
        StatusQuestion->setMaximumSize(QSize(150, 150));
        StatusQuestion->setCursor(QCursor(Qt::PointingHandCursor));
        StatusQuestion->setPixmap(QPixmap(QString::fromUtf8(":/Information.svg")));
        StatusQuestion->setScaledContents(true);

        gridLayout_2->addWidget(StatusQuestion, 0, 2, 3, 1);

        ConnectToGeobrickButton_1 = new QPushButton(centralWidget);
        ConnectToGeobrickButton_1->setObjectName(QStringLiteral("ConnectToGeobrickButton_1"));
        ConnectToGeobrickButton_1->setMinimumSize(QSize(171, 31));
        ConnectToGeobrickButton_1->setMaximumSize(QSize(171, 31));

        gridLayout_2->addWidget(ConnectToGeobrickButton_1, 1, 0, 1, 1);

        GeobrickConnectedLabel = new QLabel(centralWidget);
        GeobrickConnectedLabel->setObjectName(QStringLiteral("GeobrickConnectedLabel"));

        gridLayout_2->addWidget(GeobrickConnectedLabel, 1, 1, 2, 1);

        ConnectToGeobrickButton_2 = new QPushButton(centralWidget);
        ConnectToGeobrickButton_2->setObjectName(QStringLiteral("ConnectToGeobrickButton_2"));
        ConnectToGeobrickButton_2->setMinimumSize(QSize(171, 31));
        ConnectToGeobrickButton_2->setMaximumSize(QSize(171, 31));

        gridLayout_2->addWidget(ConnectToGeobrickButton_2, 2, 0, 1, 1);

        DisconnectToGeobrick = new QPushButton(centralWidget);
        DisconnectToGeobrick->setObjectName(QStringLiteral("DisconnectToGeobrick"));

        gridLayout_2->addWidget(DisconnectToGeobrick, 3, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        tabWidgetMain = new QTabWidget(centralWidget);
        tabWidgetMain->setObjectName(QStringLiteral("tabWidgetMain"));
        tabUserInterface = new QWidget();
        tabUserInterface->setObjectName(QStringLiteral("tabUserInterface"));
        tabWidgetMain->addTab(tabUserInterface, QString());
        tabSpaceFabExpert = new QWidget();
        tabSpaceFabExpert->setObjectName(QStringLiteral("tabSpaceFabExpert"));
        gridLayout_4 = new QGridLayout(tabSpaceFabExpert);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        variable_label_8 = new QLabel(tabSpaceFabExpert);
        variable_label_8->setObjectName(QStringLiteral("variable_label_8"));
        variable_label_8->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_8, 7, 2, 1, 1);

        variable_label_9 = new QLabel(tabSpaceFabExpert);
        variable_label_9->setObjectName(QStringLiteral("variable_label_9"));
        variable_label_9->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_9, 8, 2, 1, 1);

        variable_label_3 = new QLabel(tabSpaceFabExpert);
        variable_label_3->setObjectName(QStringLiteral("variable_label_3"));
        variable_label_3->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_3, 2, 2, 1, 1);

        variable_label_11 = new QLabel(tabSpaceFabExpert);
        variable_label_11->setObjectName(QStringLiteral("variable_label_11"));
        variable_label_11->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_11, 10, 2, 1, 1);

        variable_label_2 = new QLabel(tabSpaceFabExpert);
        variable_label_2->setObjectName(QStringLiteral("variable_label_2"));
        variable_label_2->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_2, 1, 2, 1, 1);

        variable_label_7 = new QLabel(tabSpaceFabExpert);
        variable_label_7->setObjectName(QStringLiteral("variable_label_7"));
        variable_label_7->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_7, 6, 2, 1, 1);

        SendCommandButton = new QPushButton(tabSpaceFabExpert);
        SendCommandButton->setObjectName(QStringLiteral("SendCommandButton"));

        gridLayout_3->addWidget(SendCommandButton, 12, 1, 1, 1);

        textEditExpertMode = new QTextEdit(tabSpaceFabExpert);
        textEditExpertMode->setObjectName(QStringLiteral("textEditExpertMode"));

        gridLayout_3->addWidget(textEditExpertMode, 0, 0, 12, 2);

        variable_label_4 = new QLabel(tabSpaceFabExpert);
        variable_label_4->setObjectName(QStringLiteral("variable_label_4"));
        variable_label_4->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_4, 3, 2, 1, 1);

        variable_label_6 = new QLabel(tabSpaceFabExpert);
        variable_label_6->setObjectName(QStringLiteral("variable_label_6"));
        variable_label_6->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_6, 5, 2, 1, 1);

        variable_label_12 = new QLabel(tabSpaceFabExpert);
        variable_label_12->setObjectName(QStringLiteral("variable_label_12"));
        variable_label_12->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_12, 11, 2, 1, 1);

        variable_label_5 = new QLabel(tabSpaceFabExpert);
        variable_label_5->setObjectName(QStringLiteral("variable_label_5"));
        variable_label_5->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_5, 4, 2, 1, 1);

        variable_label_1 = new QLabel(tabSpaceFabExpert);
        variable_label_1->setObjectName(QStringLiteral("variable_label_1"));
        variable_label_1->setMinimumSize(QSize(150, 0));
        variable_label_1->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_1, 0, 2, 1, 1);

        lineEditExpertMode = new QLineEdit(tabSpaceFabExpert);
        lineEditExpertMode->setObjectName(QStringLiteral("lineEditExpertMode"));

        gridLayout_3->addWidget(lineEditExpertMode, 12, 0, 1, 1);

        variable_label_10 = new QLabel(tabSpaceFabExpert);
        variable_label_10->setObjectName(QStringLiteral("variable_label_10"));
        variable_label_10->setMaximumSize(QSize(159, 16));

        gridLayout_3->addWidget(variable_label_10, 9, 2, 1, 1);

        RetrieveCommonVariables = new QPushButton(tabSpaceFabExpert);
        RetrieveCommonVariables->setObjectName(QStringLiteral("RetrieveCommonVariables"));

        gridLayout_3->addWidget(RetrieveCommonVariables, 12, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabWidgetMain->addTab(tabSpaceFabExpert, QString());

        gridLayout->addWidget(tabWidgetMain, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidgetMain->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SpaceFab - Software Controller", 0));
        ServerOnOffButton->setText(QApplication::translate("MainWindow", "Switch on server", 0));
        ServerLabel->setText(QApplication::translate("MainWindow", "    Server Off", 0));
        StatusQuestion->setText(QString());
        ConnectToGeobrickButton_1->setText(QApplication::translate("MainWindow", "Connect to GeoBrick 1", 0));
        GeobrickConnectedLabel->setText(QApplication::translate("MainWindow", "    Disconnected", 0));
        ConnectToGeobrickButton_2->setText(QApplication::translate("MainWindow", "Connect to GeoBrick 2", 0));
        DisconnectToGeobrick->setText(QApplication::translate("MainWindow", "Disconnect Geobrick", 0));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabUserInterface), QApplication::translate("MainWindow", "User interface - SpaceFab", 0));
        variable_label_8->setText(QApplication::translate("MainWindow", "    q94 = undef", 0));
        variable_label_9->setText(QApplication::translate("MainWindow", "    q95 = undef", 0));
        variable_label_3->setText(QApplication::translate("MainWindow", "    q78 = undef", 0));
        variable_label_11->setText(QApplication::translate("MainWindow", "    p91 = undef", 0));
        variable_label_2->setText(QApplication::translate("MainWindow", "    q77 = undef", 0));
        variable_label_7->setText(QApplication::translate("MainWindow", "    q89 = undef", 0));
        SendCommandButton->setText(QApplication::translate("MainWindow", "Send", 0));
        variable_label_4->setText(QApplication::translate("MainWindow", "    q79 = undef", 0));
        variable_label_6->setText(QApplication::translate("MainWindow", "    q88 = undef", 0));
        variable_label_12->setText(QApplication::translate("MainWindow", "    p80 = undef", 0));
        variable_label_5->setText(QApplication::translate("MainWindow", "    q87 = undef", 0));
        variable_label_1->setText(QApplication::translate("MainWindow", "    q70 = undef", 0));
        variable_label_10->setText(QApplication::translate("MainWindow", "    q96 = undef", 0));
        RetrieveCommonVariables->setText(QApplication::translate("MainWindow", "Update", 0));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabSpaceFabExpert), QApplication::translate("MainWindow", "Expert mode - SpaceFab", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
