#pragma once

#include <pd/ecs/cmp/tabbedWindowControl/WidgetComponent.hpp>

namespace pd::ecs::cmp::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	class PressComponent
	{
	public:
		IWidget::eButton pressed = IWidget::eButton::NONE;
	};
}