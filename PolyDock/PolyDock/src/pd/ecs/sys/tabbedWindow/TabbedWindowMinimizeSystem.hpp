#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. TabbedWindowComponent
	// 2. TabbedWindowWidgetComponent
	// 3. TabbedWindowMinimizeRequestComponent
	// 4. tabbedWindowControl/Component
	//
	// Removed
	// 1. TabbedWindowMinimizeRequestComponent
	// Modified
	// 1. TabbedWindowWidgetComponent
	class TabbedWindowMinimizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}