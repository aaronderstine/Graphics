/********************************************************************************
** Form generated from reading UI file 'GraphicsProject.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSPROJECT_H
#define UI_GRAPHICSPROJECT_H

#include <CameraSlider.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GraphicsProjectClass
{
public:
    QAction *actionLoad_Config_File;
    QAction *actionHelp;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadConfigFileButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *cameraZoomLabel;
    CameraSlider *zoomSlider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *cameraRotateUDLabel;
    CameraSlider *rotateUDSlider;
    QVBoxLayout *verticalLayout_3;
    QLabel *cameraRotateLRLabel;
    CameraSlider *rotateLRSlider;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GraphicsProjectClass)
    {
        if (GraphicsProjectClass->objectName().isEmpty())
            GraphicsProjectClass->setObjectName(QStringLiteral("GraphicsProjectClass"));
        GraphicsProjectClass->resize(595, 400);
        actionLoad_Config_File = new QAction(GraphicsProjectClass);
        actionLoad_Config_File->setObjectName(QStringLiteral("actionLoad_Config_File"));
        actionHelp = new QAction(GraphicsProjectClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        centralWidget = new QWidget(GraphicsProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        loadConfigFileButton = new QPushButton(centralWidget);
        loadConfigFileButton->setObjectName(QStringLiteral("loadConfigFileButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loadConfigFileButton->sizePolicy().hasHeightForWidth());
        loadConfigFileButton->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(loadConfigFileButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        cameraZoomLabel = new QLabel(centralWidget);
        cameraZoomLabel->setObjectName(QStringLiteral("cameraZoomLabel"));
        cameraZoomLabel->setFrameShape(QFrame::NoFrame);
        cameraZoomLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(cameraZoomLabel);

        zoomSlider = new CameraSlider(centralWidget);
        zoomSlider->setObjectName(QStringLiteral("zoomSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(zoomSlider->sizePolicy().hasHeightForWidth());
        zoomSlider->setSizePolicy(sizePolicy2);
        zoomSlider->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(zoomSlider);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cameraRotateUDLabel = new QLabel(centralWidget);
        cameraRotateUDLabel->setObjectName(QStringLiteral("cameraRotateUDLabel"));
        cameraRotateUDLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(cameraRotateUDLabel);

        rotateUDSlider = new CameraSlider(centralWidget);
        rotateUDSlider->setObjectName(QStringLiteral("rotateUDSlider"));
        sizePolicy2.setHeightForWidth(rotateUDSlider->sizePolicy().hasHeightForWidth());
        rotateUDSlider->setSizePolicy(sizePolicy2);
        rotateUDSlider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(rotateUDSlider);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cameraRotateLRLabel = new QLabel(centralWidget);
        cameraRotateLRLabel->setObjectName(QStringLiteral("cameraRotateLRLabel"));
        cameraRotateLRLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(cameraRotateLRLabel);

        rotateLRSlider = new CameraSlider(centralWidget);
        rotateLRSlider->setObjectName(QStringLiteral("rotateLRSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rotateLRSlider->sizePolicy().hasHeightForWidth());
        rotateLRSlider->setSizePolicy(sizePolicy3);
        rotateLRSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(rotateLRSlider);


        verticalLayout_2->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        GraphicsProjectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GraphicsProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        GraphicsProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GraphicsProjectClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GraphicsProjectClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GraphicsProjectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GraphicsProjectClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionLoad_Config_File);
        menuHelp->addAction(actionHelp);

        retranslateUi(GraphicsProjectClass);
        QObject::connect(zoomSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(cameraZoomChanged(Camera::MoveDirection)));
        QObject::connect(rotateUDSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(cameraRotateUDChanged(Camera::MoveDirection)));
        QObject::connect(rotateLRSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(cameraRotateLRChanged(Camera::MoveDirection)));
        QObject::connect(loadConfigFileButton, SIGNAL(clicked()), GraphicsProjectClass, SLOT(onLoadConfigFileTriggered()));

        QMetaObject::connectSlotsByName(GraphicsProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphicsProjectClass)
    {
        GraphicsProjectClass->setWindowTitle(QApplication::translate("GraphicsProjectClass", "GraphicsProject", 0));
        actionLoad_Config_File->setText(QApplication::translate("GraphicsProjectClass", "Load Config File", 0));
        actionHelp->setText(QApplication::translate("GraphicsProjectClass", "Help", 0));
        loadConfigFileButton->setText(QApplication::translate("GraphicsProjectClass", "Load\n"
"Configuration\n"
"File", 0));
        cameraZoomLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Zoom", 0));
        cameraRotateUDLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Rotate\n"
"Up/Down", 0));
        cameraRotateLRLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Rotate\n"
"Left/Right", 0));
        menuFile->setTitle(QApplication::translate("GraphicsProjectClass", "File", 0));
        menuHelp->setTitle(QApplication::translate("GraphicsProjectClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicsProjectClass: public Ui_GraphicsProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSPROJECT_H
