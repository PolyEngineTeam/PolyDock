#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeRequestComponent
	{
	public:
		Eigen::Vector2i newWindowSize;
	};
}