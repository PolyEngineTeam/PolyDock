#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementActiveComponent
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}