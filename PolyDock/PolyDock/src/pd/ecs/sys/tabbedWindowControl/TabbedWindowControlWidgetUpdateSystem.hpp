#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindowControl/Component
	// 2. tabbedWindowControl/WidgetComponent
	// 3. tabbedWindowControl/WidgetUpdateRequestComponent
	// Optional
	// 1. tabbedWindowControl/HoverComponent
	// 2. tabbedWindowControl/PressComponent
	//
	// Removed
	// 1. tabbedWindowControl/WidgetUpdateRequestComponent
	// Modified
	// 1. tabbedWindowControl/WidgetComponent
	class TabbedWindowControlWidgetUpdateSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}