#pragma once

#include <entt/entt.hpp>
#include <Eigen/Dense>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementActiveComponent
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementRequestComponent
	{
	public:
		int indexRequestedForFirstMovedTab = 0;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabsDragOutRequestComponent
	{
	public:
	};

	// ---------------------------------------------------------------------------------------------------------
	class TabsDragInRequestComponent
	{
	public:
		entt::entity source;
		int destinationIndex = 0;
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}