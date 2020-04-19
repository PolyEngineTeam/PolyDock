#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. Component
	// 2. Widget
	// 3. MinimizeRequest
	// 4. tabbedWindowControl/Component
	//
	// Removed
	// 1. MinimizeRequest
	// Modified
	// 1. Widget
	class TabbedWindowMinimizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}