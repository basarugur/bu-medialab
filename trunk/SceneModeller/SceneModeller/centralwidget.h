#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class CentralWidget : public QWidget
{
	Q_OBJECT

public:
	CentralWidget(QWidget *parent) : QWidget(parent)
	{
	}
	~CentralWidget()
	{
	}

signals:
	void sizeChanged();
protected:
	void resizeEvent(QResizeEvent* )
	{
		emit sizeChanged();
	}	
};

#endif // CENTRALWIDGET_H
