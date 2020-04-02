#pragma once

#include <pd/ecs/cmp/tabbedWindowControl/WidgetComponent.hpp>

namespace pd::ecs::cmp::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	class HoverComponent
	{
	public:
		IWidget::eButton hovered = IWidget::eButton::NONE;
	};
}