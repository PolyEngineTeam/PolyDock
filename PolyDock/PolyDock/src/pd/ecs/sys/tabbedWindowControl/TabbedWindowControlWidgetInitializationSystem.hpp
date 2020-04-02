#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwnerComponent
	// 2. tabbedWindowControl/Component
	// Banned
	// 1. tabbedWindowControl/WidgetComponent
	//
	// Added
	// 1. tabbedWindowControl/WidgetComponent
	// Modified
	// 1. WidgetsOwnerComponent
	class TabbedWindowControlWidgetInitializationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}