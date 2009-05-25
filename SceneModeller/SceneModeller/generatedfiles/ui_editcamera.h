/********************************************************************************
** Form generated from reading ui file 'editcamera.ui'
**
** Created: Sun May 24 22:51:47 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EDITCAMERA_H
#define UI_EDITCAMERA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_EditCameraClass
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *Camera;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *Camera_2;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *Add;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *Close;

    void setupUi(QDialog *EditCameraClass)
    {
    if (EditCameraClass->objectName().isEmpty())
        EditCameraClass->setObjectName(QString::fromUtf8("EditCameraClass"));
    EditCameraClass->resize(500, 245);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(EditCameraClass->sizePolicy().hasHeightForWidth());
    EditCameraClass->setSizePolicy(sizePolicy);
    gridLayout_2 = new QGridLayout(EditCameraClass);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setMargin(11);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    Camera = new QGroupBox(EditCameraClass);
    Camera->setObjectName(QString::fromUtf8("Camera"));
    gridLayout = new QGridLayout(Camera);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    listWidget = new QListWidget(Camera);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setMaximumSize(QSize(200, 16777215));

    gridLayout->addWidget(listWidget, 0, 0, 1, 1);


    gridLayout_2->addWidget(Camera, 0, 0, 1, 1);

    groupBox_2 = new QGroupBox(EditCameraClass);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    gridLayout_3 = new QGridLayout(groupBox_2);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setMargin(11);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    lineEdit = new QLineEdit(groupBox_2);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout_3->addWidget(lineEdit, 0, 1, 1, 1);

    lineEdit_2 = new QLineEdit(groupBox_2);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

    gridLayout_3->addWidget(lineEdit_2, 1, 1, 1, 1);

    lineEdit_4 = new QLineEdit(groupBox_2);
    lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

    gridLayout_3->addWidget(lineEdit_4, 3, 1, 1, 1);

    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout_3->addWidget(label, 0, 0, 1, 1);

    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

    label_4 = new QLabel(groupBox_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

    Camera_2 = new QLabel(groupBox_2);
    Camera_2->setObjectName(QString::fromUtf8("Camera_2"));

    gridLayout_3->addWidget(Camera_2, 2, 0, 1, 1);

    lineEdit_3 = new QLineEdit(groupBox_2);
    lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

    gridLayout_3->addWidget(lineEdit_3, 2, 1, 1, 1);


    gridLayout_2->addWidget(groupBox_2, 0, 1, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setMargin(2);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    Add = new QPushButton(EditCameraClass);
    Add->setObjectName(QString::fromUtf8("Add"));
    Add->setFocusPolicy(Qt::ClickFocus);

    horizontalLayout->addWidget(Add);

    pushButton_2 = new QPushButton(EditCameraClass);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setFocusPolicy(Qt::ClickFocus);

    horizontalLayout->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(EditCameraClass);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setFocusPolicy(Qt::ClickFocus);

    horizontalLayout->addWidget(pushButton_3);

    Close = new QPushButton(EditCameraClass);
    Close->setObjectName(QString::fromUtf8("Close"));
    Close->setFocusPolicy(Qt::ClickFocus);

    horizontalLayout->addWidget(Close);


    gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 2);


    retranslateUi(EditCameraClass);

    QMetaObject::connectSlotsByName(EditCameraClass);
    } // setupUi

    void retranslateUi(QDialog *EditCameraClass)
    {
    EditCameraClass->setWindowTitle(QApplication::translate("EditCameraClass", "EditCamera", 0, QApplication::UnicodeUTF8));
    Camera->setTitle(QApplication::translate("EditCameraClass", "Camera List", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("EditCameraClass", "Current Camera Information", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("EditCameraClass", "Name", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("EditCameraClass", "Position", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("EditCameraClass", "Up Vector", 0, QApplication::UnicodeUTF8));
    Camera_2->setText(QApplication::translate("EditCameraClass", "Target ", 0, QApplication::UnicodeUTF8));
    Add->setText(QApplication::translate("EditCameraClass", "Add", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("EditCameraClass", "Delete", 0, QApplication::UnicodeUTF8));
    pushButton_3->setText(QApplication::translate("EditCameraClass", "Ok", 0, QApplication::UnicodeUTF8));
    Close->setText(QApplication::translate("EditCameraClass", "Close", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EditCameraClass);
    } // retranslateUi

};

namespace Ui {
    class EditCameraClass: public Ui_EditCameraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCAMERA_H
