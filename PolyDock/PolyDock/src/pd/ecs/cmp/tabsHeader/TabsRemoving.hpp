#pragma once

#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsRemovalRequest
	{
	public:
		entt::entity tabToRemove;
	};
}