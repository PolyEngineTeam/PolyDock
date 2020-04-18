#pragma once

#include <entt/entt.hpp>
#include <Eigen/Dense>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementActive
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementRequest
	{
	public:
		int indexRequestedForFirstMovedTab = 0;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabsDragOutRequest
	{
	public:
	};

	// ---------------------------------------------------------------------------------------------------------
	class TabsDragInRequest
	{
	public:
		entt::entity source;
		int destinationIndex = 0;
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}