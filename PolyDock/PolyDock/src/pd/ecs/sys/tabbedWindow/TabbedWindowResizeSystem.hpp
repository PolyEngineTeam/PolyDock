#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. TabbedWindowResizeRequestComponent
	// 2. TabbedWindowComponent
	// 
	// Added
	// 1. DirtyTabbedWindowComponent
	// Modified
	// 1. TabbedWindowComponent
	// Removed
	// 1. TabbedWindowResizeRequestComponent
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}