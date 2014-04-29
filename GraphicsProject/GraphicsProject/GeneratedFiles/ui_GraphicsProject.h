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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
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
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox;
    QLabel *selectLabel;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *prevButton;
    QToolButton *nextButton;
    QVBoxLayout *verticalLayout_6;
    QLabel *transformLabel;
    QLabel *translateLabel;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QLineEdit *transXEdit;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QLineEdit *transYEdit;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_3;
    QLineEdit *transZEdit;
    QLabel *rotateLabel;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_4;
    QLineEdit *rotXEdit;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_5;
    QLineEdit *rotYEdit;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_6;
    QLineEdit *rotZEdit;
    QLabel *scaleLabel;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_7;
    QLineEdit *scaleXEdit;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_8;
    QLineEdit *scaleYEdit;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_9;
    QLineEdit *scaleZEdit;
    QLabel *colorLabel;
    QComboBox *colorPicker;
    QPushButton *transformButton;
    QPushButton *subdivideButton;
    QSpacerItem *verticalSpacer;
    QPushButton *raytraceButton;
    QSpacerItem *verticalSpacer_2;
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
    QFrame *line;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lightYLabel;
    CameraSlider *lightYSlider;
    QVBoxLayout *verticalLayout_4;
    QLabel *lightXLabel;
    CameraSlider *lightXSlider;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lightZLabel;
    CameraSlider *lightZSlider;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GraphicsProjectClass)
    {
        if (GraphicsProjectClass->objectName().isEmpty())
            GraphicsProjectClass->setObjectName(QStringLiteral("GraphicsProjectClass"));
        GraphicsProjectClass->resize(740, 612);
        actionLoad_Config_File = new QAction(GraphicsProjectClass);
        actionLoad_Config_File->setObjectName(QStringLiteral("actionLoad_Config_File"));
        actionHelp = new QAction(GraphicsProjectClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        centralWidget = new QWidget(GraphicsProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_5->setContentsMargins(0, -1, -1, -1);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(checkBox);

        selectLabel = new QLabel(centralWidget);
        selectLabel->setObjectName(QStringLiteral("selectLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(selectLabel->sizePolicy().hasHeightForWidth());
        selectLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(10);
        selectLabel->setFont(font);
        selectLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(selectLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        prevButton = new QToolButton(centralWidget);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        sizePolicy1.setHeightForWidth(prevButton->sizePolicy().hasHeightForWidth());
        prevButton->setSizePolicy(sizePolicy1);
        prevButton->setArrowType(Qt::LeftArrow);

        horizontalLayout_4->addWidget(prevButton);

        nextButton = new QToolButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        sizePolicy1.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy1);
        nextButton->setArrowType(Qt::RightArrow);

        horizontalLayout_4->addWidget(nextButton);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        transformLabel = new QLabel(centralWidget);
        transformLabel->setObjectName(QStringLiteral("transformLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(transformLabel->sizePolicy().hasHeightForWidth());
        transformLabel->setSizePolicy(sizePolicy3);
        transformLabel->setFont(font);
        transformLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(transformLabel);

        translateLabel = new QLabel(centralWidget);
        translateLabel->setObjectName(QStringLiteral("translateLabel"));
        sizePolicy3.setHeightForWidth(translateLabel->sizePolicy().hasHeightForWidth());
        translateLabel->setSizePolicy(sizePolicy3);
        translateLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(translateLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, 0, -1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label);

        transXEdit = new QLineEdit(centralWidget);
        transXEdit->setObjectName(QStringLiteral("transXEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(transXEdit->sizePolicy().hasHeightForWidth());
        transXEdit->setSizePolicy(sizePolicy4);
        transXEdit->setMinimumSize(QSize(0, 0));
        transXEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(transXEdit);


        horizontalLayout_5->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, -1, 0, -1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_2);

        transYEdit = new QLineEdit(centralWidget);
        transYEdit->setObjectName(QStringLiteral("transYEdit"));
        sizePolicy4.setHeightForWidth(transYEdit->sizePolicy().hasHeightForWidth());
        transYEdit->setSizePolicy(sizePolicy4);
        transYEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(transYEdit);


        horizontalLayout_5->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, -1, 0, -1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_3);

        transZEdit = new QLineEdit(centralWidget);
        transZEdit->setObjectName(QStringLiteral("transZEdit"));
        sizePolicy4.setHeightForWidth(transZEdit->sizePolicy().hasHeightForWidth());
        transZEdit->setSizePolicy(sizePolicy4);
        transZEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(transZEdit);


        horizontalLayout_5->addLayout(verticalLayout_9);


        verticalLayout_6->addLayout(horizontalLayout_5);

        rotateLabel = new QLabel(centralWidget);
        rotateLabel->setObjectName(QStringLiteral("rotateLabel"));
        sizePolicy3.setHeightForWidth(rotateLabel->sizePolicy().hasHeightForWidth());
        rotateLabel->setSizePolicy(sizePolicy3);
        rotateLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(rotateLabel);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(-1, -1, 0, -1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_4);

        rotXEdit = new QLineEdit(centralWidget);
        rotXEdit->setObjectName(QStringLiteral("rotXEdit"));
        sizePolicy4.setHeightForWidth(rotXEdit->sizePolicy().hasHeightForWidth());
        rotXEdit->setSizePolicy(sizePolicy4);
        rotXEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(rotXEdit);


        horizontalLayout_7->addLayout(verticalLayout_10);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(-1, -1, 0, -1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_5);

        rotYEdit = new QLineEdit(centralWidget);
        rotYEdit->setObjectName(QStringLiteral("rotYEdit"));
        sizePolicy4.setHeightForWidth(rotYEdit->sizePolicy().hasHeightForWidth());
        rotYEdit->setSizePolicy(sizePolicy4);
        rotYEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(rotYEdit);


        horizontalLayout_7->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_6);

        rotZEdit = new QLineEdit(centralWidget);
        rotZEdit->setObjectName(QStringLiteral("rotZEdit"));
        sizePolicy4.setHeightForWidth(rotZEdit->sizePolicy().hasHeightForWidth());
        rotZEdit->setSizePolicy(sizePolicy4);
        rotZEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(rotZEdit);


        horizontalLayout_7->addLayout(verticalLayout_13);


        verticalLayout_6->addLayout(horizontalLayout_7);

        scaleLabel = new QLabel(centralWidget);
        scaleLabel->setObjectName(QStringLiteral("scaleLabel"));
        sizePolicy3.setHeightForWidth(scaleLabel->sizePolicy().hasHeightForWidth());
        scaleLabel->setSizePolicy(sizePolicy3);
        scaleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(scaleLabel);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(-1, -1, 0, -1);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_7);

        scaleXEdit = new QLineEdit(centralWidget);
        scaleXEdit->setObjectName(QStringLiteral("scaleXEdit"));
        sizePolicy4.setHeightForWidth(scaleXEdit->sizePolicy().hasHeightForWidth());
        scaleXEdit->setSizePolicy(sizePolicy4);
        scaleXEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(scaleXEdit);


        horizontalLayout_8->addLayout(verticalLayout_11);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_8);

        scaleYEdit = new QLineEdit(centralWidget);
        scaleYEdit->setObjectName(QStringLiteral("scaleYEdit"));
        sizePolicy4.setHeightForWidth(scaleYEdit->sizePolicy().hasHeightForWidth());
        scaleYEdit->setSizePolicy(sizePolicy4);
        scaleYEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(scaleYEdit);


        horizontalLayout_8->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(label_9);

        scaleZEdit = new QLineEdit(centralWidget);
        scaleZEdit->setObjectName(QStringLiteral("scaleZEdit"));
        sizePolicy4.setHeightForWidth(scaleZEdit->sizePolicy().hasHeightForWidth());
        scaleZEdit->setSizePolicy(sizePolicy4);
        scaleZEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(scaleZEdit);


        horizontalLayout_8->addLayout(verticalLayout_15);


        verticalLayout_6->addLayout(horizontalLayout_8);

        colorLabel = new QLabel(centralWidget);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));
        colorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(colorLabel);

        colorPicker = new QComboBox(centralWidget);
        colorPicker->setObjectName(QStringLiteral("colorPicker"));
        colorPicker->setMaxVisibleItems(20);

        verticalLayout_6->addWidget(colorPicker);

        transformButton = new QPushButton(centralWidget);
        transformButton->setObjectName(QStringLiteral("transformButton"));

        verticalLayout_6->addWidget(transformButton);


        verticalLayout_5->addLayout(verticalLayout_6);

        subdivideButton = new QPushButton(centralWidget);
        subdivideButton->setObjectName(QStringLiteral("subdivideButton"));

        verticalLayout_5->addWidget(subdivideButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        raytraceButton = new QPushButton(centralWidget);
        raytraceButton->setObjectName(QStringLiteral("raytraceButton"));

        verticalLayout_5->addWidget(raytraceButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy5);
        widget->setMinimumSize(QSize(0, 0));
        widget->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(widget);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        loadConfigFileButton = new QPushButton(centralWidget);
        loadConfigFileButton->setObjectName(QStringLiteral("loadConfigFileButton"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(loadConfigFileButton->sizePolicy().hasHeightForWidth());
        loadConfigFileButton->setSizePolicy(sizePolicy6);

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
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(zoomSlider->sizePolicy().hasHeightForWidth());
        zoomSlider->setSizePolicy(sizePolicy7);
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
        sizePolicy7.setHeightForWidth(rotateUDSlider->sizePolicy().hasHeightForWidth());
        rotateUDSlider->setSizePolicy(sizePolicy7);
        rotateUDSlider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(rotateUDSlider);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cameraRotateLRLabel = new QLabel(centralWidget);
        cameraRotateLRLabel->setObjectName(QStringLiteral("cameraRotateLRLabel"));
        sizePolicy.setHeightForWidth(cameraRotateLRLabel->sizePolicy().hasHeightForWidth());
        cameraRotateLRLabel->setSizePolicy(sizePolicy);
        cameraRotateLRLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(cameraRotateLRLabel);

        rotateLRSlider = new CameraSlider(centralWidget);
        rotateLRSlider->setObjectName(QStringLiteral("rotateLRSlider"));
        sizePolicy1.setHeightForWidth(rotateLRSlider->sizePolicy().hasHeightForWidth());
        rotateLRSlider->setSizePolicy(sizePolicy1);
        rotateLRSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(rotateLRSlider);


        verticalLayout_2->addLayout(verticalLayout_3);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lightYLabel = new QLabel(centralWidget);
        lightYLabel->setObjectName(QStringLiteral("lightYLabel"));
        lightYLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(lightYLabel);

        lightYSlider = new CameraSlider(centralWidget);
        lightYSlider->setObjectName(QStringLiteral("lightYSlider"));
        sizePolicy7.setHeightForWidth(lightYSlider->sizePolicy().hasHeightForWidth());
        lightYSlider->setSizePolicy(sizePolicy7);
        lightYSlider->setOrientation(Qt::Vertical);

        horizontalLayout_6->addWidget(lightYSlider);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lightXLabel = new QLabel(centralWidget);
        lightXLabel->setObjectName(QStringLiteral("lightXLabel"));
        lightXLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lightXLabel);

        lightXSlider = new CameraSlider(centralWidget);
        lightXSlider->setObjectName(QStringLiteral("lightXSlider"));
        sizePolicy1.setHeightForWidth(lightXSlider->sizePolicy().hasHeightForWidth());
        lightXSlider->setSizePolicy(sizePolicy1);
        lightXSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(lightXSlider);


        verticalLayout_2->addLayout(verticalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        lightZLabel = new QLabel(centralWidget);
        lightZLabel->setObjectName(QStringLiteral("lightZLabel"));
        lightZLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(lightZLabel);

        lightZSlider = new CameraSlider(centralWidget);
        lightZSlider->setObjectName(QStringLiteral("lightZSlider"));
        sizePolicy7.setHeightForWidth(lightZSlider->sizePolicy().hasHeightForWidth());
        lightZSlider->setSizePolicy(sizePolicy7);
        lightZSlider->setOrientation(Qt::Vertical);

        horizontalLayout_9->addWidget(lightZSlider);


        verticalLayout_2->addLayout(horizontalLayout_9);


        horizontalLayout->addLayout(verticalLayout_2);

        GraphicsProjectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GraphicsProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 740, 21));
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
        QObject::connect(lightYSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(lightYChanged(Camera::MoveDirection)));
        QObject::connect(lightZSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(lightZChanged(Camera::MoveDirection)));
        QObject::connect(lightXSlider, SIGNAL(cameraMove(Camera::MoveDirection)), widget, SLOT(lightXChanged(Camera::MoveDirection)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), widget, SLOT(showSelected(bool)));
        QObject::connect(nextButton, SIGNAL(clicked()), widget, SLOT(selectNext()));
        QObject::connect(prevButton, SIGNAL(clicked()), widget, SLOT(selectPrev()));
        QObject::connect(transformButton, SIGNAL(clicked()), widget, SLOT(transform()));
        QObject::connect(subdivideButton, SIGNAL(clicked()), widget, SLOT(subdivide()));
        QObject::connect(raytraceButton, SIGNAL(clicked()), widget, SLOT(raytrace()));

        QMetaObject::connectSlotsByName(GraphicsProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphicsProjectClass)
    {
        GraphicsProjectClass->setWindowTitle(QApplication::translate("GraphicsProjectClass", "GraphicsProject", 0));
        actionLoad_Config_File->setText(QApplication::translate("GraphicsProjectClass", "Load Config File", 0));
        actionHelp->setText(QApplication::translate("GraphicsProjectClass", "Help", 0));
        checkBox->setText(QApplication::translate("GraphicsProjectClass", "Show Selected", 0));
        selectLabel->setText(QApplication::translate("GraphicsProjectClass", "Select Object", 0));
        prevButton->setText(QApplication::translate("GraphicsProjectClass", "...", 0));
        nextButton->setText(QApplication::translate("GraphicsProjectClass", "...", 0));
        transformLabel->setText(QApplication::translate("GraphicsProjectClass", "Transform Object", 0));
        translateLabel->setText(QApplication::translate("GraphicsProjectClass", "Translate", 0));
        label->setText(QApplication::translate("GraphicsProjectClass", "X", 0));
        label_2->setText(QApplication::translate("GraphicsProjectClass", "Y", 0));
        label_3->setText(QApplication::translate("GraphicsProjectClass", "Z", 0));
        rotateLabel->setText(QApplication::translate("GraphicsProjectClass", "Rotate", 0));
        label_4->setText(QApplication::translate("GraphicsProjectClass", "X", 0));
        label_5->setText(QApplication::translate("GraphicsProjectClass", "Y", 0));
        label_6->setText(QApplication::translate("GraphicsProjectClass", "Z", 0));
        scaleLabel->setText(QApplication::translate("GraphicsProjectClass", "Scale", 0));
        label_7->setText(QApplication::translate("GraphicsProjectClass", "X", 0));
        label_8->setText(QApplication::translate("GraphicsProjectClass", "Y", 0));
        label_9->setText(QApplication::translate("GraphicsProjectClass", "Z", 0));
        colorLabel->setText(QApplication::translate("GraphicsProjectClass", "Color", 0));
        transformButton->setText(QApplication::translate("GraphicsProjectClass", "Transform", 0));
        subdivideButton->setText(QApplication::translate("GraphicsProjectClass", "Subdivide Object", 0));
        raytraceButton->setText(QApplication::translate("GraphicsProjectClass", "Raytrace", 0));
        loadConfigFileButton->setText(QApplication::translate("GraphicsProjectClass", "Load\n"
"Configuration\n"
"File", 0));
        cameraZoomLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Zoom", 0));
        cameraRotateUDLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Rotate\n"
"Up/Down", 0));
        cameraRotateLRLabel->setText(QApplication::translate("GraphicsProjectClass", "Camera Rotate\n"
"Left/Right", 0));
        lightYLabel->setText(QApplication::translate("GraphicsProjectClass", "Light Y+/-", 0));
        lightXLabel->setText(QApplication::translate("GraphicsProjectClass", "Light X +/-", 0));
        lightZLabel->setText(QApplication::translate("GraphicsProjectClass", "Light Z +/-", 0));
        menuFile->setTitle(QApplication::translate("GraphicsProjectClass", "File", 0));
        menuHelp->setTitle(QApplication::translate("GraphicsProjectClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicsProjectClass: public Ui_GraphicsProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSPROJECT_H
