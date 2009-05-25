/********************************************************************************
** Form generated from reading ui file 'scenemodeller.ui'
**
** Created: Mon May 25 00:20:47 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SCENEMODELLER_H
#define UI_SCENEMODELLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneModellerClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionMerge;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionObject_Tree_Dock;
    QAction *actionObject_Properties_Dock;
    QAction *actionCamera_Property_Window;
    QAction *actionCamera;
    QAction *actionBox;
    QAction *actionSphere;
    QAction *actionCone;
    QAction *actionCylinder;
    QAction *actionCamera_Editing;
    QAction *actionLight_2;
    QAction *actionFace;
    QAction *actionPoint;
    QAction *actionPoint_Light;
    QAction *actionArea_Light;
    QAction *actionSingle_Object;
    QAction *actionObject_Tree;
    QAction *actionTow_Sided_Cylinder;
    QAction *actionTorus;
    QAction *actionTriangle;
    QAction *actionRectangle;
    QAction *actionCircle;
    QAction *actionDisk;
    QAction *actionPartial_Disk;
    QAction *actionRotate;
    QAction *actionScale;
    QAction *actionDuplicate;
    QAction *actionDelete_2;
    QAction *actionTranslate;
    QAction *actionAdd_Child;
    QAction *actionRemove_Child;
    QAction *actionNew_Camera;
    QAction *actionRender;
    QAction *actionConvert_to_Mesh;
    QAction *actionSplit_Face;
    QAction *actionExtrude_Face;
    QAction *actionMove_Target;
    QAction *actionMove_Camera;
    QAction *actionFile_Tool_Bar;
    QAction *actionMode_Tool_Bar;
    QAction *action3D_Objects_Toolbar;
    QAction *action2D_Objects_Toolbar;
    QAction *actionPrimitive_Toolbar;
    QAction *actionMesh_Toolbar;
    QAction *actionRender_Toolbar;
    QAction *actionCamera_Toolbar;
    QAction *actionEdit_Toolbar;
    QToolBar *fileToolBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QMenu *menuPrimitive;
    QMenu *menuObjects;
    QMenu *menu2D_Objects;
    QMenu *menuEdit;
    QMenu *menuRender;
    QMenu *menuMode;
    QMenu *menuMesh;
    QMenu *menuCamera;
    QMenu *menuView;
    QDockWidget *ObjectTreeDock;
    QWidget *dockWidgetContents;
    QDockWidget *ObjectPropertyDock;
    QWidget *dockWidgetContents_2;
    QDockWidget *cameraPropertyDock;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_5;
    QLabel *Position;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QToolBar *toolBar;
    QToolBar *toolBar_2;
    QToolBar *toolBar_3;
    QToolBar *toolBar_4;
    QToolBar *toolBar_5;
    QToolBar *toolBar_6;
    QToolBar *toolBar_7;
    QToolBar *toolBar_8;

    void setupUi(QMainWindow *SceneModellerClass)
    {
    if (SceneModellerClass->objectName().isEmpty())
        SceneModellerClass->setObjectName(QString::fromUtf8("SceneModellerClass"));
    SceneModellerClass->resize(1235, 600);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SceneModellerClass->sizePolicy().hasHeightForWidth());
    SceneModellerClass->setSizePolicy(sizePolicy);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/icon.png")), QIcon::Normal, QIcon::Off);
    SceneModellerClass->setWindowIcon(icon);
    SceneModellerClass->setStyleSheet(QString::fromUtf8("QMainWindow\n"
"{\n"
"color:rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
"QCheckBox\n"
"{\n"
"color:rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
"QLineEdit {\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(80,80,80);\n"
"}\n"
"QListWidget {\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(80,80,80);\n"
"}\n"
"QComboBox {\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(80,80,80);\n"
"}\n"
"QDialog {\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
"QPushButton{\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
"QLabel{\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
" QDockWidget {    \n"
"color : rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
" }\n"
"QGroupBox {\n"
"color : rgb(255,255,255);\n"
"background-color:rgb(0,0,0);\n"
"}\n"
" QDockWidget::close-button, QDockWidget::float-button {    \n"
" border: 1px solid transparent;   \n"
"  background: darkgray;     \n"
"padding: 0px; \n"
""
        "}\n"
"\n"
"QTreeWidget\n"
"{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(100, 100, 100, 255));\n"
"color: rgb(255, 255, 255);\n"
"}\n"
" QTreeView::branch:has-siblings:!adjoins-item {   \n"
"  border-image: url(icons/vline.png) 0; } \n"
"QTreeView::branch:has-siblings:adjoins-item {  \n"
"   border-image: url(icons/branch-more.png) 0; }\n"
" QTreeView::branch:!has-children:!has-siblings:adjoins-item {  \n"
"   border-image: url(icons/branch-end.png) 0; } \n"
"QTreeView::branch:has-children:!has-siblings:closed, QTreeView::branch:closed:has-children:has-siblings {       \n"
"  border-image: none;    \n"
"    image: url(icons/branch-closed.png); } \n"
"QTreeView::branch:open:has-children:!has-siblings, QTreeView::branch:open:has-children:has-siblings  {      \n"
"   border-image: none;         \n"
"image: url(icons/branch-open.png); }\n"
" QTreeView {     alternate-background-color: yellow; }\n"
"QTreeView {     show-decoration-selected: 1; } Q"
        "TreeView::item {      border: 1px solid #d9d9d9;     border-top-color: transparent;     border-bottom-color: transparent; } QTreeView::item:hover {     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);     border: 1px solid #bfcde4; } QTreeView::item:selected {     border: 1px solid #567dbc; } QTreeView::item:selected:active{     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc); } QTreeView::item:selected:!active {     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf); }\n"
" \n"
"\n"
"QMenu {\n"
"	background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 140, 0, 149), stop:0.164773 rgba(255, 255, 																		255, 255));\n"
"	border: 1px solid black; \n"
"} \n"
"QMenu::item {\n"
"   background-color : rgb(150,150,150);\n"
" 	color : rgb(255,255,255);\n"
" }\n"
"QMenu::item:selected {\n"
"	background-color: qlineargradient(spread:reflect, x1:0, y1:0.505"
        "682, x2:0, 		y2:1, stop:0 rgba(150, 150, 150, 149), stop:0.551136 rgba(50, 50, 50, 255));\n"
"    color : rgb(255,255,255);\n"
"}\n"
"\n"
"QMenuBar {\n"
"  background-color : rgb(150,150,150);\n"
" color : rgb(255,255,255);\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"	background-color: qlineargradient(spread:reflect, x1:0, y1:0.505682, x2:0, 		y2:1, stop:0 rgba(150, 150, 150, 149), stop:0.551136 rgba(50, 50, 50, 255));\n"
"    color : rgb(255,255,255);\n"
"}\n"
"\n"
""));
    SceneModellerClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
    actionNew = new QAction(SceneModellerClass);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/new.png")), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon1);
    actionOpen = new QAction(SceneModellerClass);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/open.png")), QIcon::Normal, QIcon::Off);
    actionOpen->setIcon(icon2);
    actionSave = new QAction(SceneModellerClass);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/save.png")), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon3);
    actionSave_As = new QAction(SceneModellerClass);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/saveas.png")), QIcon::Normal, QIcon::Off);
    actionSave_As->setIcon(icon4);
    actionExit = new QAction(SceneModellerClass);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    QIcon icon5;
    icon5.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/exit.png")), QIcon::Normal, QIcon::Off);
    actionExit->setIcon(icon5);
    actionMerge = new QAction(SceneModellerClass);
    actionMerge->setObjectName(QString::fromUtf8("actionMerge"));
    QIcon icon6;
    icon6.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/twoface.png")), QIcon::Normal, QIcon::Off);
    actionMerge->setIcon(icon6);
    actionImport = new QAction(SceneModellerClass);
    actionImport->setObjectName(QString::fromUtf8("actionImport"));
    QIcon icon7;
    icon7.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/import.png")), QIcon::Normal, QIcon::Off);
    actionImport->setIcon(icon7);
    actionExport = new QAction(SceneModellerClass);
    actionExport->setObjectName(QString::fromUtf8("actionExport"));
    QIcon icon8;
    icon8.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/export.png")), QIcon::Normal, QIcon::Off);
    actionExport->setIcon(icon8);
    actionObject_Tree_Dock = new QAction(SceneModellerClass);
    actionObject_Tree_Dock->setObjectName(QString::fromUtf8("actionObject_Tree_Dock"));
    actionObject_Tree_Dock->setCheckable(true);
    actionObject_Tree_Dock->setChecked(true);
    actionObject_Properties_Dock = new QAction(SceneModellerClass);
    actionObject_Properties_Dock->setObjectName(QString::fromUtf8("actionObject_Properties_Dock"));
    actionObject_Properties_Dock->setCheckable(true);
    actionObject_Properties_Dock->setChecked(true);
    actionCamera_Property_Window = new QAction(SceneModellerClass);
    actionCamera_Property_Window->setObjectName(QString::fromUtf8("actionCamera_Property_Window"));
    actionCamera_Property_Window->setCheckable(true);
    actionCamera_Property_Window->setChecked(true);
    actionCamera = new QAction(SceneModellerClass);
    actionCamera->setObjectName(QString::fromUtf8("actionCamera"));
    QIcon icon9;
    icon9.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/VideoSZ.png")), QIcon::Normal, QIcon::Off);
    actionCamera->setIcon(icon9);
    actionBox = new QAction(SceneModellerClass);
    actionBox->setObjectName(QString::fromUtf8("actionBox"));
    QIcon icon10;
    icon10.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/cube.png")), QIcon::Normal, QIcon::Off);
    actionBox->setIcon(icon10);
    actionSphere = new QAction(SceneModellerClass);
    actionSphere->setObjectName(QString::fromUtf8("actionSphere"));
    QIcon icon11;
    icon11.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/sphere.png")), QIcon::Normal, QIcon::Off);
    actionSphere->setIcon(icon11);
    actionCone = new QAction(SceneModellerClass);
    actionCone->setObjectName(QString::fromUtf8("actionCone"));
    QIcon icon12;
    icon12.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/cone.png")), QIcon::Normal, QIcon::Off);
    actionCone->setIcon(icon12);
    actionCylinder = new QAction(SceneModellerClass);
    actionCylinder->setObjectName(QString::fromUtf8("actionCylinder"));
    QIcon icon13;
    icon13.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/cylinder.png")), QIcon::Normal, QIcon::Off);
    actionCylinder->setIcon(icon13);
    actionCamera_Editing = new QAction(SceneModellerClass);
    actionCamera_Editing->setObjectName(QString::fromUtf8("actionCamera_Editing"));
    actionCamera_Editing->setCheckable(true);
    QIcon icon14;
    icon14.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/camera-icon.png")), QIcon::Normal, QIcon::Off);
    actionCamera_Editing->setIcon(icon14);
    actionLight_2 = new QAction(SceneModellerClass);
    actionLight_2->setObjectName(QString::fromUtf8("actionLight_2"));
    actionLight_2->setCheckable(true);
    QIcon icon15;
    icon15.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/ktip.png")), QIcon::Normal, QIcon::Off);
    actionLight_2->setIcon(icon15);
    actionFace = new QAction(SceneModellerClass);
    actionFace->setObjectName(QString::fromUtf8("actionFace"));
    actionFace->setCheckable(true);
    QIcon icon16;
    icon16.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/QnextSZ.png")), QIcon::Normal, QIcon::Off);
    actionFace->setIcon(icon16);
    actionPoint = new QAction(SceneModellerClass);
    actionPoint->setObjectName(QString::fromUtf8("actionPoint"));
    actionPoint->setCheckable(true);
    QIcon icon17;
    icon17.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/ASTERISK.png")), QIcon::Normal, QIcon::Off);
    actionPoint->setIcon(icon17);
    actionPoint_Light = new QAction(SceneModellerClass);
    actionPoint_Light->setObjectName(QString::fromUtf8("actionPoint_Light"));
    QIcon icon18;
    icon18.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/qgradient-radial.png")), QIcon::Normal, QIcon::Off);
    actionPoint_Light->setIcon(icon18);
    actionArea_Light = new QAction(SceneModellerClass);
    actionArea_Light->setObjectName(QString::fromUtf8("actionArea_Light"));
    QIcon icon19;
    icon19.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/add_area_light.png")), QIcon::Normal, QIcon::Off);
    actionArea_Light->setIcon(icon19);
    actionSingle_Object = new QAction(SceneModellerClass);
    actionSingle_Object->setObjectName(QString::fromUtf8("actionSingle_Object"));
    actionSingle_Object->setCheckable(true);
    actionSingle_Object->setChecked(true);
    QIcon icon20;
    icon20.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/blockdevice.png")), QIcon::Normal, QIcon::Off);
    actionSingle_Object->setIcon(icon20);
    actionObject_Tree = new QAction(SceneModellerClass);
    actionObject_Tree->setObjectName(QString::fromUtf8("actionObject_Tree"));
    actionObject_Tree->setCheckable(true);
    QIcon icon21;
    icon21.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/visio8.png")), QIcon::Normal, QIcon::Off);
    actionObject_Tree->setIcon(icon21);
    actionTow_Sided_Cylinder = new QAction(SceneModellerClass);
    actionTow_Sided_Cylinder->setObjectName(QString::fromUtf8("actionTow_Sided_Cylinder"));
    QIcon icon22;
    icon22.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/tw_cylinder.png")), QIcon::Normal, QIcon::Off);
    actionTow_Sided_Cylinder->setIcon(icon22);
    actionTorus = new QAction(SceneModellerClass);
    actionTorus->setObjectName(QString::fromUtf8("actionTorus"));
    QIcon icon23;
    icon23.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/torus.png")), QIcon::Normal, QIcon::Off);
    actionTorus->setIcon(icon23);
    actionTriangle = new QAction(SceneModellerClass);
    actionTriangle->setObjectName(QString::fromUtf8("actionTriangle"));
    QIcon icon24;
    icon24.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/triangle.png")), QIcon::Normal, QIcon::Off);
    actionTriangle->setIcon(icon24);
    actionRectangle = new QAction(SceneModellerClass);
    actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
    QIcon icon25;
    icon25.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/rectangle.png")), QIcon::Normal, QIcon::Off);
    actionRectangle->setIcon(icon25);
    actionCircle = new QAction(SceneModellerClass);
    actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
    QIcon icon26;
    icon26.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/circle.png")), QIcon::Normal, QIcon::Off);
    actionCircle->setIcon(icon26);
    actionDisk = new QAction(SceneModellerClass);
    actionDisk->setObjectName(QString::fromUtf8("actionDisk"));
    QIcon icon27;
    icon27.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/disk.png")), QIcon::Normal, QIcon::Off);
    actionDisk->setIcon(icon27);
    actionPartial_Disk = new QAction(SceneModellerClass);
    actionPartial_Disk->setObjectName(QString::fromUtf8("actionPartial_Disk"));
    QIcon icon28;
    icon28.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/partial_disk.png")), QIcon::Normal, QIcon::Off);
    actionPartial_Disk->setIcon(icon28);
    actionRotate = new QAction(SceneModellerClass);
    actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
    QIcon icon29;
    icon29.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/rotateObject.png")), QIcon::Normal, QIcon::Off);
    actionRotate->setIcon(icon29);
    actionScale = new QAction(SceneModellerClass);
    actionScale->setObjectName(QString::fromUtf8("actionScale"));
    QIcon icon30;
    icon30.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/4directionsSZ.png")), QIcon::Normal, QIcon::Off);
    actionScale->setIcon(icon30);
    actionDuplicate = new QAction(SceneModellerClass);
    actionDuplicate->setObjectName(QString::fromUtf8("actionDuplicate"));
    QIcon icon31;
    icon31.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/TRILLIAN AQUA1.png")), QIcon::Normal, QIcon::Off);
    actionDuplicate->setIcon(icon31);
    actionDelete_2 = new QAction(SceneModellerClass);
    actionDelete_2->setObjectName(QString::fromUtf8("actionDelete_2"));
    QIcon icon32;
    icon32.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/104.png")), QIcon::Normal, QIcon::Off);
    actionDelete_2->setIcon(icon32);
    actionTranslate = new QAction(SceneModellerClass);
    actionTranslate->setObjectName(QString::fromUtf8("actionTranslate"));
    QIcon icon33;
    icon33.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/3d.png")), QIcon::Normal, QIcon::Off);
    actionTranslate->setIcon(icon33);
    actionAdd_Child = new QAction(SceneModellerClass);
    actionAdd_Child->setObjectName(QString::fromUtf8("actionAdd_Child"));
    actionAdd_Child->setEnabled(false);
    QIcon icon34;
    icon34.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/add_child.PNG")), QIcon::Normal, QIcon::Off);
    actionAdd_Child->setIcon(icon34);
    actionRemove_Child = new QAction(SceneModellerClass);
    actionRemove_Child->setObjectName(QString::fromUtf8("actionRemove_Child"));
    actionRemove_Child->setEnabled(false);
    QIcon icon35;
    icon35.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/remove_child.PNG")), QIcon::Normal, QIcon::Off);
    actionRemove_Child->setIcon(icon35);
    actionNew_Camera = new QAction(SceneModellerClass);
    actionNew_Camera->setObjectName(QString::fromUtf8("actionNew_Camera"));
    QIcon icon36;
    icon36.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/add_camera.png")), QIcon::Normal, QIcon::Off);
    actionNew_Camera->setIcon(icon36);
    actionRender = new QAction(SceneModellerClass);
    actionRender->setObjectName(QString::fromUtf8("actionRender"));
    QIcon icon37;
    icon37.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/IRIDESCENT.png")), QIcon::Normal, QIcon::Off);
    actionRender->setIcon(icon37);
    actionConvert_to_Mesh = new QAction(SceneModellerClass);
    actionConvert_to_Mesh->setObjectName(QString::fromUtf8("actionConvert_to_Mesh"));
    QIcon icon38;
    icon38.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/ksokoban.png")), QIcon::Normal, QIcon::Off);
    actionConvert_to_Mesh->setIcon(icon38);
    actionSplit_Face = new QAction(SceneModellerClass);
    actionSplit_Face->setObjectName(QString::fromUtf8("actionSplit_Face"));
    QIcon icon39;
    icon39.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/split_face.png")), QIcon::Normal, QIcon::Off);
    actionSplit_Face->setIcon(icon39);
    actionExtrude_Face = new QAction(SceneModellerClass);
    actionExtrude_Face->setObjectName(QString::fromUtf8("actionExtrude_Face"));
    QIcon icon40;
    icon40.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/extendure.png")), QIcon::Normal, QIcon::Off);
    actionExtrude_Face->setIcon(icon40);
    actionMove_Target = new QAction(SceneModellerClass);
    actionMove_Target->setObjectName(QString::fromUtf8("actionMove_Target"));
    QIcon icon41;
    icon41.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/moveTarget.png")), QIcon::Normal, QIcon::Off);
    actionMove_Target->setIcon(icon41);
    actionMove_Camera = new QAction(SceneModellerClass);
    actionMove_Camera->setObjectName(QString::fromUtf8("actionMove_Camera"));
    QIcon icon42;
    icon42.addPixmap(QPixmap(QString::fromUtf8(":/SceneModeller/icons/move_camera.png")), QIcon::Normal, QIcon::Off);
    actionMove_Camera->setIcon(icon42);
    actionFile_Tool_Bar = new QAction(SceneModellerClass);
    actionFile_Tool_Bar->setObjectName(QString::fromUtf8("actionFile_Tool_Bar"));
    actionFile_Tool_Bar->setCheckable(true);
    actionFile_Tool_Bar->setChecked(true);
    actionMode_Tool_Bar = new QAction(SceneModellerClass);
    actionMode_Tool_Bar->setObjectName(QString::fromUtf8("actionMode_Tool_Bar"));
    actionMode_Tool_Bar->setCheckable(true);
    actionMode_Tool_Bar->setChecked(true);
    action3D_Objects_Toolbar = new QAction(SceneModellerClass);
    action3D_Objects_Toolbar->setObjectName(QString::fromUtf8("action3D_Objects_Toolbar"));
    action3D_Objects_Toolbar->setCheckable(true);
    action3D_Objects_Toolbar->setChecked(true);
    action2D_Objects_Toolbar = new QAction(SceneModellerClass);
    action2D_Objects_Toolbar->setObjectName(QString::fromUtf8("action2D_Objects_Toolbar"));
    action2D_Objects_Toolbar->setCheckable(true);
    action2D_Objects_Toolbar->setChecked(true);
    actionPrimitive_Toolbar = new QAction(SceneModellerClass);
    actionPrimitive_Toolbar->setObjectName(QString::fromUtf8("actionPrimitive_Toolbar"));
    actionPrimitive_Toolbar->setCheckable(true);
    actionPrimitive_Toolbar->setChecked(true);
    actionMesh_Toolbar = new QAction(SceneModellerClass);
    actionMesh_Toolbar->setObjectName(QString::fromUtf8("actionMesh_Toolbar"));
    actionMesh_Toolbar->setCheckable(true);
    actionMesh_Toolbar->setChecked(true);
    actionRender_Toolbar = new QAction(SceneModellerClass);
    actionRender_Toolbar->setObjectName(QString::fromUtf8("actionRender_Toolbar"));
    actionRender_Toolbar->setCheckable(true);
    actionRender_Toolbar->setChecked(true);
    actionCamera_Toolbar = new QAction(SceneModellerClass);
    actionCamera_Toolbar->setObjectName(QString::fromUtf8("actionCamera_Toolbar"));
    actionCamera_Toolbar->setCheckable(true);
    actionCamera_Toolbar->setChecked(true);
    actionEdit_Toolbar = new QAction(SceneModellerClass);
    actionEdit_Toolbar->setObjectName(QString::fromUtf8("actionEdit_Toolbar"));
    actionEdit_Toolbar->setCheckable(true);
    actionEdit_Toolbar->setChecked(true);
    fileToolBar = new QToolBar(SceneModellerClass);
    fileToolBar->setObjectName(QString::fromUtf8("fileToolBar"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, fileToolBar);
    menubar = new QMenuBar(SceneModellerClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1235, 21));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuWindow = new QMenu(menubar);
    menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
    menuPrimitive = new QMenu(menubar);
    menuPrimitive->setObjectName(QString::fromUtf8("menuPrimitive"));
    menuObjects = new QMenu(menuPrimitive);
    menuObjects->setObjectName(QString::fromUtf8("menuObjects"));
    menu2D_Objects = new QMenu(menuPrimitive);
    menu2D_Objects->setObjectName(QString::fromUtf8("menu2D_Objects"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    menuRender = new QMenu(menubar);
    menuRender->setObjectName(QString::fromUtf8("menuRender"));
    menuMode = new QMenu(menubar);
    menuMode->setObjectName(QString::fromUtf8("menuMode"));
    menuMesh = new QMenu(menubar);
    menuMesh->setObjectName(QString::fromUtf8("menuMesh"));
    menuCamera = new QMenu(menubar);
    menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
    menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    SceneModellerClass->setMenuBar(menubar);
    ObjectTreeDock = new QDockWidget(SceneModellerClass);
    ObjectTreeDock->setObjectName(QString::fromUtf8("ObjectTreeDock"));
    dockWidgetContents = new QWidget();
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
    ObjectTreeDock->setWidget(dockWidgetContents);
    SceneModellerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), ObjectTreeDock);
    ObjectPropertyDock = new QDockWidget(SceneModellerClass);
    ObjectPropertyDock->setObjectName(QString::fromUtf8("ObjectPropertyDock"));
    dockWidgetContents_2 = new QWidget();
    dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
    ObjectPropertyDock->setWidget(dockWidgetContents_2);
    SceneModellerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), ObjectPropertyDock);
    cameraPropertyDock = new QDockWidget(SceneModellerClass);
    cameraPropertyDock->setObjectName(QString::fromUtf8("cameraPropertyDock"));
    dockWidgetContents_5 = new QWidget();
    dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
    gridLayout_5 = new QGridLayout(dockWidgetContents_5);
    gridLayout_5->setSpacing(2);
    gridLayout_5->setMargin(2);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    Position = new QLabel(dockWidgetContents_5);
    Position->setObjectName(QString::fromUtf8("Position"));

    gridLayout_5->addWidget(Position, 1, 0, 1, 1);

    lineEdit = new QLineEdit(dockWidgetContents_5);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout_5->addWidget(lineEdit, 1, 1, 1, 1);

    label_2 = new QLabel(dockWidgetContents_5);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout_5->addWidget(label_2, 2, 0, 1, 1);

    label_3 = new QLabel(dockWidgetContents_5);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout_5->addWidget(label_3, 3, 0, 1, 1);

    lineEdit_2 = new QLineEdit(dockWidgetContents_5);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

    gridLayout_5->addWidget(lineEdit_2, 2, 1, 1, 1);

    label = new QLabel(dockWidgetContents_5);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout_5->addWidget(label, 0, 0, 1, 1);

    lineEdit_4 = new QLineEdit(dockWidgetContents_5);
    lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
    lineEdit_4->setSizePolicy(sizePolicy1);

    gridLayout_5->addWidget(lineEdit_4, 0, 1, 1, 1);

    lineEdit_3 = new QLineEdit(dockWidgetContents_5);
    lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

    gridLayout_5->addWidget(lineEdit_3, 3, 1, 1, 1);

    cameraPropertyDock->setWidget(dockWidgetContents_5);
    SceneModellerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), cameraPropertyDock);
    toolBar = new QToolBar(SceneModellerClass);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar);
    toolBar_2 = new QToolBar(SceneModellerClass);
    toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_2);
    toolBar_3 = new QToolBar(SceneModellerClass);
    toolBar_3->setObjectName(QString::fromUtf8("toolBar_3"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_3);
    toolBar_4 = new QToolBar(SceneModellerClass);
    toolBar_4->setObjectName(QString::fromUtf8("toolBar_4"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_4);
    toolBar_5 = new QToolBar(SceneModellerClass);
    toolBar_5->setObjectName(QString::fromUtf8("toolBar_5"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_5);
    toolBar_6 = new QToolBar(SceneModellerClass);
    toolBar_6->setObjectName(QString::fromUtf8("toolBar_6"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_6);
    SceneModellerClass->insertToolBarBreak(toolBar_6);
    toolBar_7 = new QToolBar(SceneModellerClass);
    toolBar_7->setObjectName(QString::fromUtf8("toolBar_7"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_7);
    toolBar_8 = new QToolBar(SceneModellerClass);
    toolBar_8->setObjectName(QString::fromUtf8("toolBar_8"));
    SceneModellerClass->addToolBar(Qt::TopToolBarArea, toolBar_8);

    fileToolBar->addAction(actionNew);
    fileToolBar->addAction(actionOpen);
    fileToolBar->addAction(actionSave);
    fileToolBar->addAction(actionSave_As);
    fileToolBar->addAction(actionMerge);
    fileToolBar->addAction(actionImport);
    fileToolBar->addAction(actionExport);
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menubar->addAction(menuView->menuAction());
    menubar->addAction(menuMode->menuAction());
    menubar->addAction(menuPrimitive->menuAction());
    menubar->addAction(menuCamera->menuAction());
    menubar->addAction(menuMesh->menuAction());
    menubar->addAction(menuWindow->menuAction());
    menubar->addAction(menuRender->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_As);
    menuFile->addAction(actionMerge);
    menuFile->addSeparator();
    menuFile->addAction(actionImport);
    menuFile->addAction(actionExport);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuWindow->addAction(actionObject_Tree_Dock);
    menuWindow->addAction(actionObject_Properties_Dock);
    menuWindow->addAction(actionCamera_Property_Window);
    menuPrimitive->addAction(actionNew_Camera);
    menuPrimitive->addSeparator();
    menuPrimitive->addAction(actionPoint_Light);
    menuPrimitive->addAction(actionArea_Light);
    menuPrimitive->addSeparator();
    menuPrimitive->addAction(menuObjects->menuAction());
    menuPrimitive->addAction(menu2D_Objects->menuAction());
    menuObjects->addAction(actionBox);
    menuObjects->addAction(actionSphere);
    menuObjects->addAction(actionCone);
    menuObjects->addAction(actionCylinder);
    menuObjects->addAction(actionTow_Sided_Cylinder);
    menuObjects->addAction(actionTorus);
    menu2D_Objects->addAction(actionTriangle);
    menu2D_Objects->addAction(actionRectangle);
    menu2D_Objects->addAction(actionCircle);
    menu2D_Objects->addAction(actionDisk);
    menu2D_Objects->addAction(actionPartial_Disk);
    menuEdit->addAction(actionRotate);
    menuEdit->addAction(actionScale);
    menuEdit->addAction(actionTranslate);
    menuEdit->addAction(actionDuplicate);
    menuEdit->addAction(actionDelete_2);
    menuEdit->addSeparator();
    menuEdit->addAction(actionAdd_Child);
    menuEdit->addAction(actionRemove_Child);
    menuRender->addAction(actionRender);
    menuMode->addAction(actionSingle_Object);
    menuMode->addAction(actionObject_Tree);
    menuMode->addSeparator();
    menuMode->addAction(actionCamera_Editing);
    menuMode->addAction(actionLight_2);
    menuMode->addSeparator();
    menuMode->addAction(actionFace);
    menuMode->addAction(actionPoint);
    menuMesh->addAction(actionConvert_to_Mesh);
    menuMesh->addSeparator();
    menuMesh->addAction(actionSplit_Face);
    menuMesh->addAction(actionExtrude_Face);
    menuCamera->addAction(actionCamera);
    menuCamera->addSeparator();
    menuCamera->addAction(actionMove_Target);
    menuCamera->addAction(actionMove_Camera);
    menuView->addAction(actionFile_Tool_Bar);
    menuView->addAction(actionEdit_Toolbar);
    menuView->addAction(actionMode_Tool_Bar);
    menuView->addAction(action3D_Objects_Toolbar);
    menuView->addAction(action2D_Objects_Toolbar);
    menuView->addAction(actionPrimitive_Toolbar);
    menuView->addAction(actionMesh_Toolbar);
    menuView->addAction(actionCamera_Toolbar);
    menuView->addAction(actionRender_Toolbar);
    toolBar->addAction(actionRotate);
    toolBar->addAction(actionScale);
    toolBar->addAction(actionTranslate);
    toolBar->addAction(actionDuplicate);
    toolBar->addAction(actionDelete_2);
    toolBar->addAction(actionAdd_Child);
    toolBar->addAction(actionRemove_Child);
    toolBar_2->addAction(actionSingle_Object);
    toolBar_2->addAction(actionObject_Tree);
    toolBar_2->addAction(actionCamera_Editing);
    toolBar_2->addAction(actionLight_2);
    toolBar_2->addAction(actionFace);
    toolBar_2->addAction(actionPoint);
    toolBar_3->addAction(actionSphere);
    toolBar_3->addAction(actionBox);
    toolBar_3->addAction(actionCylinder);
    toolBar_3->addAction(actionCone);
    toolBar_3->addAction(actionTow_Sided_Cylinder);
    toolBar_3->addAction(actionTorus);
    toolBar_4->addAction(actionTriangle);
    toolBar_4->addAction(actionRectangle);
    toolBar_4->addAction(actionCircle);
    toolBar_4->addAction(actionDisk);
    toolBar_4->addAction(actionPartial_Disk);
    toolBar_5->addAction(actionNew_Camera);
    toolBar_5->addAction(actionPoint_Light);
    toolBar_5->addAction(actionArea_Light);
    toolBar_6->addAction(actionConvert_to_Mesh);
    toolBar_6->addAction(actionSplit_Face);
    toolBar_6->addAction(actionExtrude_Face);
    toolBar_7->addAction(actionCamera);
    toolBar_7->addAction(actionMove_Target);
    toolBar_7->addAction(actionMove_Camera);
    toolBar_8->addAction(actionRender);

    retranslateUi(SceneModellerClass);

    QMetaObject::connectSlotsByName(SceneModellerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SceneModellerClass)
    {
    SceneModellerClass->setWindowTitle(QApplication::translate("SceneModellerClass", "Scene Modeler for Resposive Workbench by SERHAT ANGIN", 0, QApplication::UnicodeUTF8));
    actionNew->setText(QApplication::translate("SceneModellerClass", "New", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("SceneModellerClass", "Open...", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("SceneModellerClass", "Save...", 0, QApplication::UnicodeUTF8));
    actionSave_As->setText(QApplication::translate("SceneModellerClass", "Save As...", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("SceneModellerClass", "Exit", 0, QApplication::UnicodeUTF8));
    actionMerge->setText(QApplication::translate("SceneModellerClass", "Merge...", 0, QApplication::UnicodeUTF8));
    actionImport->setText(QApplication::translate("SceneModellerClass", "Import...", 0, QApplication::UnicodeUTF8));
    actionExport->setText(QApplication::translate("SceneModellerClass", "Export...", 0, QApplication::UnicodeUTF8));
    actionObject_Tree_Dock->setText(QApplication::translate("SceneModellerClass", "Object Tree", 0, QApplication::UnicodeUTF8));
    actionObject_Properties_Dock->setText(QApplication::translate("SceneModellerClass", "Object Property", 0, QApplication::UnicodeUTF8));
    actionObject_Properties_Dock->setIconText(QApplication::translate("SceneModellerClass", "Object Property Dock", 0, QApplication::UnicodeUTF8));
    actionCamera_Property_Window->setText(QApplication::translate("SceneModellerClass", "Camera Property", 0, QApplication::UnicodeUTF8));
    actionCamera->setText(QApplication::translate("SceneModellerClass", "Edit Cameras", 0, QApplication::UnicodeUTF8));
    actionBox->setText(QApplication::translate("SceneModellerClass", "Cube", 0, QApplication::UnicodeUTF8));
    actionSphere->setText(QApplication::translate("SceneModellerClass", "Sphere", 0, QApplication::UnicodeUTF8));
    actionCone->setText(QApplication::translate("SceneModellerClass", "Cone", 0, QApplication::UnicodeUTF8));
    actionCylinder->setText(QApplication::translate("SceneModellerClass", "Cylinder", 0, QApplication::UnicodeUTF8));
    actionCamera_Editing->setText(QApplication::translate("SceneModellerClass", "Camera", 0, QApplication::UnicodeUTF8));
    actionLight_2->setText(QApplication::translate("SceneModellerClass", "Light", 0, QApplication::UnicodeUTF8));
    actionFace->setText(QApplication::translate("SceneModellerClass", "Face", 0, QApplication::UnicodeUTF8));
    actionPoint->setText(QApplication::translate("SceneModellerClass", "Vertex", 0, QApplication::UnicodeUTF8));
    actionPoint_Light->setText(QApplication::translate("SceneModellerClass", "Point Light", 0, QApplication::UnicodeUTF8));
    actionArea_Light->setText(QApplication::translate("SceneModellerClass", "Area Light", 0, QApplication::UnicodeUTF8));
    actionSingle_Object->setText(QApplication::translate("SceneModellerClass", "Single Object", 0, QApplication::UnicodeUTF8));
    actionObject_Tree->setText(QApplication::translate("SceneModellerClass", "Object Tree", 0, QApplication::UnicodeUTF8));
    actionTow_Sided_Cylinder->setText(QApplication::translate("SceneModellerClass", "Two Sided Cylinder", 0, QApplication::UnicodeUTF8));
    actionTorus->setText(QApplication::translate("SceneModellerClass", "Torus", 0, QApplication::UnicodeUTF8));
    actionTriangle->setText(QApplication::translate("SceneModellerClass", "Triangle", 0, QApplication::UnicodeUTF8));
    actionRectangle->setText(QApplication::translate("SceneModellerClass", "Rectangle", 0, QApplication::UnicodeUTF8));
    actionCircle->setText(QApplication::translate("SceneModellerClass", "Circle", 0, QApplication::UnicodeUTF8));
    actionDisk->setText(QApplication::translate("SceneModellerClass", "Disk", 0, QApplication::UnicodeUTF8));
    actionPartial_Disk->setText(QApplication::translate("SceneModellerClass", "Partial Disk", 0, QApplication::UnicodeUTF8));
    actionRotate->setText(QApplication::translate("SceneModellerClass", "Rotate", 0, QApplication::UnicodeUTF8));
    actionScale->setText(QApplication::translate("SceneModellerClass", "Scale", 0, QApplication::UnicodeUTF8));
    actionDuplicate->setText(QApplication::translate("SceneModellerClass", "Duplicate", 0, QApplication::UnicodeUTF8));
    actionDelete_2->setText(QApplication::translate("SceneModellerClass", "Delete", 0, QApplication::UnicodeUTF8));
    actionTranslate->setText(QApplication::translate("SceneModellerClass", "Translate", 0, QApplication::UnicodeUTF8));
    actionAdd_Child->setText(QApplication::translate("SceneModellerClass", "Add Child", 0, QApplication::UnicodeUTF8));
    actionRemove_Child->setText(QApplication::translate("SceneModellerClass", "Remove Child", 0, QApplication::UnicodeUTF8));
    actionNew_Camera->setText(QApplication::translate("SceneModellerClass", "New Camera", 0, QApplication::UnicodeUTF8));
    actionRender->setText(QApplication::translate("SceneModellerClass", "Render", 0, QApplication::UnicodeUTF8));
    actionConvert_to_Mesh->setText(QApplication::translate("SceneModellerClass", "Convert to Mesh", 0, QApplication::UnicodeUTF8));
    actionSplit_Face->setText(QApplication::translate("SceneModellerClass", "Split Face", 0, QApplication::UnicodeUTF8));
    actionExtrude_Face->setText(QApplication::translate("SceneModellerClass", "Extrude Face", 0, QApplication::UnicodeUTF8));
    actionMove_Target->setText(QApplication::translate("SceneModellerClass", "Move Target", 0, QApplication::UnicodeUTF8));
    actionMove_Camera->setText(QApplication::translate("SceneModellerClass", "Move Camera", 0, QApplication::UnicodeUTF8));
    actionFile_Tool_Bar->setText(QApplication::translate("SceneModellerClass", "File Toolbar", 0, QApplication::UnicodeUTF8));
    actionMode_Tool_Bar->setText(QApplication::translate("SceneModellerClass", "Mode Toolbar", 0, QApplication::UnicodeUTF8));
    action3D_Objects_Toolbar->setText(QApplication::translate("SceneModellerClass", "3D Objects Toolbar", 0, QApplication::UnicodeUTF8));
    action2D_Objects_Toolbar->setText(QApplication::translate("SceneModellerClass", "2D Objects Toolbar", 0, QApplication::UnicodeUTF8));
    actionPrimitive_Toolbar->setText(QApplication::translate("SceneModellerClass", "Primitive Toolbar", 0, QApplication::UnicodeUTF8));
    actionMesh_Toolbar->setText(QApplication::translate("SceneModellerClass", "Mesh Toolbar", 0, QApplication::UnicodeUTF8));
    actionRender_Toolbar->setText(QApplication::translate("SceneModellerClass", "Render Toolbar", 0, QApplication::UnicodeUTF8));
    actionCamera_Toolbar->setText(QApplication::translate("SceneModellerClass", "Camera Toolbar", 0, QApplication::UnicodeUTF8));
    actionEdit_Toolbar->setText(QApplication::translate("SceneModellerClass", "Edit Toolbar", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("SceneModellerClass", "File", 0, QApplication::UnicodeUTF8));
    menuWindow->setTitle(QApplication::translate("SceneModellerClass", "Window", 0, QApplication::UnicodeUTF8));
    menuPrimitive->setTitle(QApplication::translate("SceneModellerClass", "Primitive", 0, QApplication::UnicodeUTF8));
    menuObjects->setTitle(QApplication::translate("SceneModellerClass", "3D Objects", 0, QApplication::UnicodeUTF8));
    menu2D_Objects->setTitle(QApplication::translate("SceneModellerClass", "2D Objects", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("SceneModellerClass", "Edit", 0, QApplication::UnicodeUTF8));
    menuRender->setTitle(QApplication::translate("SceneModellerClass", "Render", 0, QApplication::UnicodeUTF8));
    menuMode->setTitle(QApplication::translate("SceneModellerClass", "Mode", 0, QApplication::UnicodeUTF8));
    menuMesh->setTitle(QApplication::translate("SceneModellerClass", "Mesh", 0, QApplication::UnicodeUTF8));
    menuCamera->setTitle(QApplication::translate("SceneModellerClass", "Camera", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("SceneModellerClass", "View", 0, QApplication::UnicodeUTF8));
    ObjectTreeDock->setWindowTitle(QApplication::translate("SceneModellerClass", "Object Tree", 0, QApplication::UnicodeUTF8));
    ObjectPropertyDock->setWindowTitle(QApplication::translate("SceneModellerClass", "Object Property", 0, QApplication::UnicodeUTF8));
    cameraPropertyDock->setWindowTitle(QApplication::translate("SceneModellerClass", "Camera Property", 0, QApplication::UnicodeUTF8));
    Position->setText(QApplication::translate("SceneModellerClass", "Position", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SceneModellerClass", "Target", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("SceneModellerClass", "Up Vector", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SceneModellerClass", "Name", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar", 0, QApplication::UnicodeUTF8));
    toolBar_2->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_2", 0, QApplication::UnicodeUTF8));
    toolBar_3->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_3", 0, QApplication::UnicodeUTF8));
    toolBar_4->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_4", 0, QApplication::UnicodeUTF8));
    toolBar_5->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_5", 0, QApplication::UnicodeUTF8));
    toolBar_6->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_6", 0, QApplication::UnicodeUTF8));
    toolBar_7->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_7", 0, QApplication::UnicodeUTF8));
    toolBar_8->setWindowTitle(QApplication::translate("SceneModellerClass", "toolBar_8", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SceneModellerClass: public Ui_SceneModellerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEMODELLER_H
