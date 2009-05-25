#ifndef SMTREEWIDGET_H
#define SMTREEWIDGET_H

#include <QTreeWidget>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QByteArray>

#include <iostream>


class SMTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	SMTreeWidget(QWidget *parent);
	~SMTreeWidget();

protected:
	void dragEnterEvent(QDragEnterEvent* e){ e->accept(); }
	void dragMoveEvent(QDragMoveEvent* e){ e->accept(); }

	QMimeData *mimeData(const QList<QTreeWidgetItem*> items) const
	{
		QByteArray ba;
		QDataStream ds(&ba,QIODevice::WriteOnly);

		for( int i= 0 ; i< items.size() ; i++ )
			ds << items.at(i)->text(0);
		
		QMimeData* md = new QMimeData();
		md->setData("obj\tree",ba);

		if(items.size()>0)
			src_ = items[0];
		else 
			src_ = NULL;

		return md;
	}
	bool dropMimeData(QTreeWidgetItem *parent, int index,
                              const QMimeData *data, Qt::DropAction action)
	{
		if(parent)
		{
			QByteArray ba = data->data("obj\tree");
			QDataStream ds(&ba,QIODevice::ReadOnly);
			while(!ds.atEnd()){
				QString str;
				ds >> str ;
				QTreeWidgetItem *nwItem = new QTreeWidgetItem(parent);
				nwItem->setText(0,str);
			}
			dest_ = parent;
		}
		else
		{
			dest_ = NULL;
		}
		emit dragDrop(src_,dest_);
		return true;
	}

signals:
	void dragDrop(QTreeWidgetItem* src,QTreeWidgetItem* dest);
private:
	mutable QTreeWidgetItem* src_ ; 
	mutable QTreeWidgetItem* dest_;
	
};

#endif // SMTREEWIDGET_H
