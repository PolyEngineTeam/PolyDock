#pragma once

#include <vector>
#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsMovementRequestComponent
	{
	public:
		int indexRequestedForFirstMovedTab = 0;
	};
}