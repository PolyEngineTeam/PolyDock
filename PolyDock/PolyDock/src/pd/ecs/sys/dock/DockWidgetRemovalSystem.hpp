#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::dock
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwnerComponent
	// 2. DockWidgetComponent
	// Banned
	// 1. DockComponent
	//
	// Removed
	// 1. DockWidgetComponent
	// Modified
	// 1. WidgetsOwnerComponent
	class DockWidgetRemovalSystem: public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}