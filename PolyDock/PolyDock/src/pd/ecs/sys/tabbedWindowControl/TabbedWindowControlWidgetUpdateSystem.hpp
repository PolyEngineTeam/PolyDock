#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindowControl/Component
	// 2. tabbedWindowControl/Widget
	// 3. tabbedWindowControl/WidgetUpdateRequest
	// Optional
	// 1. tabbedWindowControl/Hover
	// 2. tabbedWindowControl/Press
	//
	// Removed
	// 1. tabbedWindowControl/WidgetUpdateRequest
	// Modified
	// 1. tabbedWindowControl/Widget
	class TabbedWindowControlWidgetUpdateSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}