#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. InputComponent
	// 2. TabbedWindowWidgetComponent
	// 
	// Added
	// 1. TabbedWindowResizeActiveComponent
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeStartSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}