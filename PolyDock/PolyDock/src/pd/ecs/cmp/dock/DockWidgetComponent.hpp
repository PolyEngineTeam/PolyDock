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
	class Widget final
	{
	public:
		DockWidget* widget = nullptr;
	};
}