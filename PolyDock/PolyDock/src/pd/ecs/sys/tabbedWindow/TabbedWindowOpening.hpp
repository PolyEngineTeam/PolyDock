#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. CreateRequest
	//
	// Added
	// 1. Component
	// 2. Component
	// 3. tabbedWindowControl/Component
	// 4. SelectedTabs
	// 5. ActiveTab
	// 6. MovementActive
	// Removed
	// 1. CreateRequest
	class TabbedWindowCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}