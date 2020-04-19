#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class ResizeHover
	{
	public:
		enum class eVertical { TOP, MIDDLE, BOTTOM };
		enum class eHorizontal { LEFT, MIDDLE, RIGHT };

		eVertical vertical = eVertical::MIDDLE;
		eHorizontal horizontal = eHorizontal::MIDDLE;
	};

	// ---------------------------------------------------------------------------------------------------------
	class ResizeActive
	{
	public:
		ResizeHover::eVertical vertical = ResizeHover::eVertical::MIDDLE;
		ResizeHover::eHorizontal horizontal = ResizeHover::eHorizontal::MIDDLE;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class ResizeRequest
	{
	public:
		Eigen::Vector2i newWindowSize;
	};
}