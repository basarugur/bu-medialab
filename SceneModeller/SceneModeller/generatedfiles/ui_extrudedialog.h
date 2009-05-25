/********************************************************************************
** Form generated from reading ui file 'extrudedialog.ui'
**
** Created: Sun May 24 22:51:47 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EXTRUDEDIALOG_H
#define UI_EXTRUDEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ExtrudeDialogClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *ExtrudeDialogClass)
    {
    if (ExtrudeDialogClass->objectName().isEmpty())
        ExtrudeDialogClass->setObjectName(QString::fromUtf8("ExtrudeDialogClass"));
    ExtrudeDialogClass->resize(400, 92);
    gridLayout = new QGridLayout(ExtrudeDialogClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox = new QGroupBox(ExtrudeDialogClass);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout_2 = new QGridLayout(groupBox);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setMargin(11);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    horizontalSlider = new QSlider(groupBox);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setMinimum(-100);
    horizontalSlider->setMaximum(100);
    horizontalSlider->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(horizontalSlider, 0, 0, 1, 1);


    gridLayout->addWidget(groupBox, 0, 0, 1, 3);

    pushButton = new QPushButton(ExtrudeDialogClass);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout->addWidget(pushButton, 1, 2, 1, 1);

    pushButton_2 = new QPushButton(ExtrudeDialogClass);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


    retranslateUi(ExtrudeDialogClass);

    QMetaObject::connectSlotsByName(ExtrudeDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ExtrudeDialogClass)
    {
    ExtrudeDialogClass->setWindowTitle(QApplication::translate("ExtrudeDialogClass", "Extrude Face", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("ExtrudeDialogClass", "Close", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("ExtrudeDialogClass", "Ok", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExtrudeDialogClass);
    } // retranslateUi

};

namespace Ui {
    class ExtrudeDialogClass: public Ui_ExtrudeDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRUDEDIALOG_H
