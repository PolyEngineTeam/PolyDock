#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root/InputComponent
	// 2. tabbedWindowControl/Component
	// 3. tabbedWindowControl/WidgetComponent
	//
	// Removed/Added/Modified
	// 1. tabbedWindowControl/HoverComponent
	// Added
	// 1. tabbedWindowControl/WidgetUpdateRequestComponent
	class TabbedWindowControlHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}