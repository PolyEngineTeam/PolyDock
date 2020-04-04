#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 2. TabbedWindowWidgetComponent
	//
	// Removed/Added
	// 1. TabbedWindowFocusComponent
	class TabbedWindowFocusSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}