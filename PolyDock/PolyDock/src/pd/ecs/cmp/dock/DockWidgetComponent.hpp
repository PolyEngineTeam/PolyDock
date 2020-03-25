#pragma once

#include <qwidget.h>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class DockWidget : public QWidget
	{
	public:

	};

	// ---------------------------------------------------------------------------------------------------------
	class DockWidgetComponent final
	{
	public:
		DockWidget* widget = nullptr;
	};
}