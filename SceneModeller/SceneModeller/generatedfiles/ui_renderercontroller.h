/********************************************************************************
** Form generated from reading ui file 'renderercontroller.ui'
**
** Created: Mon May 25 09:46:29 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_RENDERERCONTROLLER_H
#define UI_RENDERERCONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RendererControllerClass
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *Widht;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *RendererControllerClass)
    {
    if (RendererControllerClass->objectName().isEmpty())
        RendererControllerClass->setObjectName(QString::fromUtf8("RendererControllerClass"));
    RendererControllerClass->resize(236, 179);
    verticalLayout = new QVBoxLayout(RendererControllerClass);
    verticalLayout->setSpacing(6);
    verticalLayout->setMargin(11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    groupBox = new QGroupBox(RendererControllerClass);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    checkBox = new QCheckBox(groupBox);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    gridLayout->addWidget(checkBox, 0, 0, 1, 1);

    checkBox_2 = new QCheckBox(groupBox);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    gridLayout->addWidget(checkBox_2, 1, 0, 1, 1);

    Widht = new QLabel(groupBox);
    Widht->setObjectName(QString::fromUtf8("Widht"));

    gridLayout->addWidget(Widht, 2, 0, 1, 1);

    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 3, 0, 1, 1);

    lineEdit = new QLineEdit(groupBox);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setMaximumSize(QSize(100, 16777215));

    gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

    lineEdit_2 = new QLineEdit(groupBox);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setMaximumSize(QSize(100, 16777215));

    gridLayout->addWidget(lineEdit_2, 3, 1, 1, 1);


    verticalLayout->addWidget(groupBox);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    pushButton_2 = new QPushButton(RendererControllerClass);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    horizontalLayout->addWidget(pushButton_2);

    pushButton = new QPushButton(RendererControllerClass);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    horizontalLayout->addWidget(pushButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(RendererControllerClass);

    QMetaObject::connectSlotsByName(RendererControllerClass);
    } // setupUi

    void retranslateUi(QDialog *RendererControllerClass)
    {
    RendererControllerClass->setWindowTitle(QApplication::translate("RendererControllerClass", "Render Options", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("RendererControllerClass", "Render Options", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("RendererControllerClass", "Enable Antialising", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("RendererControllerClass", "Enable Sky Light", 0, QApplication::UnicodeUTF8));
    Widht->setText(QApplication::translate("RendererControllerClass", "Widht", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("RendererControllerClass", "Height", 0, QApplication::UnicodeUTF8));
    lineEdit->setText(QApplication::translate("RendererControllerClass", "600", 0, QApplication::UnicodeUTF8));
    lineEdit_2->setText(QApplication::translate("RendererControllerClass", "600", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("RendererControllerClass", "Render", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("RendererControllerClass", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(RendererControllerClass);
    } // retranslateUi

};

namespace Ui {
    class RendererControllerClass: public Ui_RendererControllerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERERCONTROLLER_H
