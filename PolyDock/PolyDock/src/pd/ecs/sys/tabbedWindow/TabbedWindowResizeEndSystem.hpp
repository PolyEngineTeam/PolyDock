#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. InputComponent
	// 2. ResizeActive
	// 
	// Removed
	// 1. ResizeActive
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeEndSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}