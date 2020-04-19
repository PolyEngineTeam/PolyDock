#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwner
	// 2. tabbedWindowControl/Component
	// Banned
	// 1. tabbedWindowControl/Widget
	//
	// Added
	// 1. tabbedWindowControl/Widget
	// Modified
	// 1. WidgetsOwner
	class TabbedWindowControlWidgetInitializationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}