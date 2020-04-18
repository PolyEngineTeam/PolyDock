#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root/InputComponent
	// 2. tabbedWindowControl/Component
	// 3. tabbedWindowControl/Press
	// 3. tabbedWindowControl/Hover
	//
	// Added
	// 1. tabbedWindow/TabbedWindowMinimizeRequestComponent
	// 2. tabbedWindow/TabbedWindowRestoreRequestComponent
	// 3. tabbedWindow/TabbedWindowMaximizeRequestComponent
	// 4. tabbedWindow/TabbedWindowCloseRequestComponent
	class TabbedWindowControlReleaseSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}