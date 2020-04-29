#pragma once

#include <vector>
#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsRemovalRequest
	{
	public:
		std::vector<entt::entity> tabsToRemove;
	};
}