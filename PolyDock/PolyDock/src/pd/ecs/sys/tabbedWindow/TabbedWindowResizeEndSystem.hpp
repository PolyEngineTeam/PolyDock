#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. InputComponent
	// 2. TabbedWindowResizeActiveComponent
	// 
	// Removed
	// 1. TabbedWindowResizeActiveComponent
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeEndSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}