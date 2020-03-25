#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::dock
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. DockComponent
	// 2. DockRequestComponent
	//
	// Added
	// 1. UpdateDockWidgetRequestComponent
	// Removed
	// 1. DockRequestComponent
	class DockSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}