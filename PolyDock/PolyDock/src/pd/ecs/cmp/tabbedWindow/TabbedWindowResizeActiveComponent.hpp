#pragma once

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeHoverComponent.hpp>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeActiveComponent
	{
	public:
		TabbedWindowResizeHoverComponent::eVertical vertical = TabbedWindowResizeHoverComponent::eVertical::MIDDLE;
		TabbedWindowResizeHoverComponent::eHorizontal horizontal = TabbedWindowResizeHoverComponent::eHorizontal::MIDDLE;
	};
}