#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowMovementActiveComponent
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};

	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowMovementRequestComponent
	{
	public:
		Eigen::Vector2i newWindowPos;
	};
}