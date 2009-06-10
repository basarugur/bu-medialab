#ifndef OBJECT_TREE_H
#define OBJECT_TREE_H

#include <Qt>
#include <QObject>
#include <QDockWidget>

#include "../core/scene.h"

#include "smtreewidget.h"

class ObjectTreeController : public QObject
{
	Q_OBJECT
public:
	ObjectTreeController(QDockWidget* m_);
	~ObjectTreeController();

	QDockWidget* m_dock_widget;

	void setScene(Scene* sc_ ) { m_scene = sc_; }
	void checkScene();

	void activateDragDropMode(bool is_);

signals:
	void sceneChanged();

private:
	SMTreeWidget* m_tree_widget;
	Scene* m_scene;
	int m_obj_sel_counter;

	bool m_signal_blocked;
	void addObjectToItem(QTreeWidgetItem* itm_,GfxObject* obj_);

public slots:
	void showDockWidget(bool sh_);
	void selectObject(QTreeWidgetItem * item, int column);
	void itemsDragDroped(QTreeWidgetItem* src,QTreeWidgetItem* dest);
};

#endif // SMMENUHANDLER_H
