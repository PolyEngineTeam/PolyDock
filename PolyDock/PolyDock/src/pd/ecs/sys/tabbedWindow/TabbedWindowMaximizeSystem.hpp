#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. TabbedWindowComponent
	// 2. TabbedWindowWidgetComponent
	// 3. TabbedWindowMaximizeRequestComponent
	// 4. tabbedWindowControl/Component
	//
	// Removed
	// 1. TabbedWindowMaximizeRequestComponent
	// Modified
	// 1. TabbedWindowWidgetComponent
	class TabbedWindowMaximizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}