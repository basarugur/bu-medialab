#include "objecttreecontroller.h"

#include <QGridLayout>

#include "../common.h"

ObjectTreeController::ObjectTreeController(QDockWidget* m_): m_dock_widget(m_)
{
	//m_dock_widget->setVisible(true);

	QGridLayout* lyt_ = new QGridLayout(m_->widget());
	lyt_->setMargin(5);
	m_tree_widget = new SMTreeWidget(m_->widget());
	lyt_->addWidget(m_tree_widget);

	//m_tree_widget->headerItem()->setText(0,"Object Tree");
	m_tree_widget->removeItemWidget(m_tree_widget->headerItem(),0);
	m_tree_widget->setHeaderHidden(true);

	m_tree_widget->invisibleRootItem()->setWhatsThis(0,"-1");

	connect(m_tree_widget,SIGNAL(itemClicked(QTreeWidgetItem*, int)),
		    this,SLOT(selectObject(QTreeWidgetItem*, int)));
	connect(m_tree_widget,SIGNAL(dragDrop(QTreeWidgetItem*,QTreeWidgetItem*)),
		    this,SLOT(itemsDragDroped(QTreeWidgetItem*,QTreeWidgetItem*)));

	m_signal_blocked = false;

}

ObjectTreeController::~ObjectTreeController()
{

}

void ObjectTreeController::activateDragDropMode(bool is_)
{
	if(is_)
	{
		m_tree_widget->setDragDropMode(QAbstractItemView::DragDrop);
		m_tree_widget->setDragEnabled(true);
		m_tree_widget->setAcceptDrops(true);
	}
	else
	{
		m_tree_widget->setDragDropMode(QAbstractItemView::NoDragDrop);
		m_tree_widget->setDragEnabled(false);
		m_tree_widget->setAcceptDrops(false);
	}

}
void ObjectTreeController::showDockWidget(bool sh_)
{
	m_dock_widget->setVisible(sh_);
}
void ObjectTreeController::checkScene()
{
	if(!m_signal_blocked)
	{
		QList<QTreeWidgetItem *> lst_ = m_tree_widget->invisibleRootItem()->takeChildren();
		for(int i=0 ; i<lst_.size();i++)delete (lst_[i]);
		m_obj_sel_counter = 1;
		for(int i=0 ; i<m_scene->objects().size();i++)
			if(m_scene->objects()[i]->getParent() == NULL)
				addObjectToItem(m_tree_widget->invisibleRootItem(),m_scene->objects()[i]);
	}
}
void ObjectTreeController::addObjectToItem(QTreeWidgetItem* itm_,GfxObject* obj_)
{
	QTreeWidgetItem* nwItem = new QTreeWidgetItem(itm_);
	nwItem->setWhatsThis(0,QString::number(m_obj_sel_counter));
	nwItem->setText(0,QString::fromStdString(obj_->getName()));

	switch(obj_->getShape()->type())
	{
	case TRIANGLE_MESH: // ksokoban.png
		nwItem->setIcon(0,QIcon(QPixmap("icons/ksokoban.png")));
		break;
	case CUBE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/cube.png")));
		break;
	case SPHERE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/sphere.png")));
		break;
	case CONE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/cone.png")));
		break;
	case CYLINDER:
		nwItem->setIcon(0,QIcon(QPixmap("icons/cylinder.png")));
		break;
	case TWO_SIDED_CYLINDER:
		nwItem->setIcon(0,QIcon(QPixmap("icons/tw_cylinder.png")));
		break;
	case TORUS:
		nwItem->setIcon(0,QIcon(QPixmap("icons/torus.png")));
		break;
	case TRIANGLE_SHAPE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/triangle.png")));
		break;
	case RECTANGLE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/rectangle.png")));
		break;
	case CIRCLE:
		nwItem->setIcon(0,QIcon(QPixmap("icons/circle.png")));
		break;
	case DISK:
		nwItem->setIcon(0,QIcon(QPixmap("icons/disk.png")));
		break;
	case PARTIAL_DISK:
		nwItem->setIcon(0,QIcon(QPixmap("icons/partial_disk.png")));
		break;
	default:
		break;
	}

	m_obj_sel_counter++;
	for(int i=0 ; i<obj_->getChildList().size();i++)
		addObjectToItem(nwItem,obj_->getChildList()[i]);
}
void ObjectTreeController::selectObject(QTreeWidgetItem * item, int column)
{
	
	int selected_ = item->whatsThis(0).toInt();

	switch(SMGlobalSettings::getEditingMode())
	{
	case SINGLE_OBJECT_MODE:
		m_scene->clearobjectSelections();
		m_scene->traverseTree(selected_)->select(true);
		break;
	case OBJECT_TREE_MODE:
		m_scene->clearTreeSelection();
		m_scene->selectTree(m_scene->traverseTree(selected_));
		break;
	}

	m_signal_blocked = true;
	emit sceneChanged();
	m_signal_blocked = false;
}
void ObjectTreeController::itemsDragDroped(QTreeWidgetItem* src,QTreeWidgetItem* dest)
{
	if(dest != NULL && src != NULL && SMGlobalSettings::getEditingMode()==OBJECT_TREE_MODE) 
	{
		int destInd_ = dest->whatsThis(0).toInt();
		int srcInd_  = src->whatsThis(0).toInt();
		GfxObject* srcObj_ = m_scene->traverseTree(srcInd_);
		if(srcObj_->getParent()!= NULL)
				srcObj_->getParent()->removeChildAt(srcObj_->getChildIndex());
		if(destInd_ != -1)
		{
			GfxObject* destObj_ = m_scene->traverseTree(dest->whatsThis(0).toInt());
			destObj_->addChild(srcObj_);
		}
		emit sceneChanged();
	}
	else if(dest == NULL && src != NULL)
	{
		int srcInd_  = src->whatsThis(0).toInt();
		GfxObject* srcObj_ = m_scene->traverseTree(srcInd_);
		if(srcObj_->getParent()!= NULL)
				srcObj_->getParent()->removeChildAt(srcObj_->getChildIndex());

		emit sceneChanged();
	}
	else
	{
		checkScene();
	}
}