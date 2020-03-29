#pragma once

#include <vector>
#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	class Component
	{
	public:
		std::vector<entt::entity> tabs;
	};
}