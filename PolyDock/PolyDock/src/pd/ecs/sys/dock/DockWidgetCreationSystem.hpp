#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::dock
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwner
	// 2. DockComponent
	// Banned
	// 1. DockWidgetComponent
	//
	// Added
	// 1. DockWidgetComponent
	// Modified
	// 1. WidgetsOwner
	class DockWidgetCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}