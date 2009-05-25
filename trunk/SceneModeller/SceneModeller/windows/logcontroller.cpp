#include "logcontroller.h"

LogController::LogController(QDockWidget* m_): m_dock_widget(m_)
{
	//m_dock_widget->setVisible(true);
}

LogController::~LogController()
{

}
void LogController::showDockWidget(bool sh_)
{
	m_dock_widget->setVisible(sh_);
}