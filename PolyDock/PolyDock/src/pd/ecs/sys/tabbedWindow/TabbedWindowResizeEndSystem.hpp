#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// Required
	// 1. Input
	// 2. ResizeActive
	// 
	// Removed
	// 1. ResizeActive
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeEndSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}