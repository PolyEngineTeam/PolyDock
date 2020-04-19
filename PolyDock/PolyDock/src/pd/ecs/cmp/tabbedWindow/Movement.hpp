#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class MovementActive
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};

	// ---------------------------------------------------------------------------------------------------------
	class MovementRequest
	{
	public:
		Eigen::Vector2i newWindowPos;
	};
}