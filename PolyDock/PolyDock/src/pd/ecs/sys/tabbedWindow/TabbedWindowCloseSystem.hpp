#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. TabbedWindowComponent
	// 2. TabbedWindowWidgetComponent
	// 3. TabbedWindowCloseRequestComponent
	//
	// Removed
	// 1. TabbedWindowCloseRequestComponent
	// Added
	// 1. TabbedWindowRemoveRequestComponent
	class TabbedWindowCloseSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}