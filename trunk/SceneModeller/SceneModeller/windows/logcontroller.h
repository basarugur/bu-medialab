#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

#include <Qt>
#include <QObject>
#include <QDockWidget>

class LogController : public QObject
{
	Q_OBJECT
public:
	LogController(QDockWidget* m_);
	~LogController();

	QDockWidget* m_dock_widget;

public slots:
	void showDockWidget(bool sh_);
};

#endif // SMMENUHANDLER_H
