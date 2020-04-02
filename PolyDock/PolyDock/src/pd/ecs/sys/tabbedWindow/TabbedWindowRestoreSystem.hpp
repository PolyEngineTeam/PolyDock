#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. TabbedWindowComponent
	// 2. TabbedWindowWidgetComponent
	// 3. TabbedWindowRestoreRequestComponent
	//
	// Removed
	// 1. TabbedWindowRestoreRequestComponent
	// Modified
	// 1. TabbedWindowWidgetComponent
	class TabbedWindowRestoreSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}