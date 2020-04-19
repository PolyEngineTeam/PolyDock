#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. Input
	// 2. Widget
	// 
	// Added
	// 1. ResizeHover
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}