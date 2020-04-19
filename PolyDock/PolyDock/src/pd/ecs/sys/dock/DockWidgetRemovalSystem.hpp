#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::dock
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwner
	// 2. Widget
	// Banned
	// 1. Component
	//
	// Removed
	// 1. Widget
	// Modified
	// 1. WidgetsOwner
	class DockWidgetRemovalSystem: public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}