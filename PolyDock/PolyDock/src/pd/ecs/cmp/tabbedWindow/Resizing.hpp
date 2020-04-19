#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeHoverComponent
	{
	public:
		enum class eVertical { TOP, MIDDLE, BOTTOM };
		enum class eHorizontal { LEFT, MIDDLE, RIGHT };

		eVertical vertical = eVertical::MIDDLE;
		eHorizontal horizontal = eHorizontal::MIDDLE;
	};

	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeActiveComponent
	{
	public:
		TabbedWindowResizeHoverComponent::eVertical vertical = TabbedWindowResizeHoverComponent::eVertical::MIDDLE;
		TabbedWindowResizeHoverComponent::eHorizontal horizontal = TabbedWindowResizeHoverComponent::eHorizontal::MIDDLE;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeRequestComponent
	{
	public:
		Eigen::Vector2i newWindowSize;
	};
}