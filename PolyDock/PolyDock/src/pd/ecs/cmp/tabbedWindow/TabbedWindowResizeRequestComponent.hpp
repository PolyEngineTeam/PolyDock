#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowMovementRequestComponent
	{
	public:
		Eigen::Vector2i newWindowPos;
	};
}