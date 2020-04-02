#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root/InputComponent
	// 2. tabbedWindowControl/Component
	// 3. tabbedWindowControl/HoverComponent
	//
	// Removed/Added/Modified
	// 1. tabbedWindowControl/PressComponent
	// Added
	// 1. tabbedWindowControl/WidgetUpdateRequestComponent
	class TabbedWindowControlPressSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}