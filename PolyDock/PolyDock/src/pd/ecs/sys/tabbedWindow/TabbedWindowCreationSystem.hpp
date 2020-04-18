#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. TabbedWindowCreateRequestComponent
	//
	// Added
	// 1. TabbedWindowComponent
	// 2. Component
	// 3. tabbedWindowControl/Component
	// 4. SelectedTabs
	// 5. ActiveTab
	// 6. TabbedWindowMovementActiveComponent
	// Removed
	// 1. TabbedWindowCreateRequestComponent
	class TabbedWindowCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}