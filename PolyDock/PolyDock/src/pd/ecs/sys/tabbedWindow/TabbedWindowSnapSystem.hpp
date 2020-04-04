#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. DesktopComponent
	// 2. TabbedWindowSnapRequestComponent
	// 3. TabbedWindowComponent
	// 4. tabbedWindowControl/Component=
	//
	// Added
	// 1. TabbedWindowRestoreRequestComponent
	// Removed
	// 1. TabbedWindowMaximizeRequestComponent
	// 2. TabbedWindowRestoreRequestComponent
	// 3. TabbedWindowMinimizeRequestComponent
	// 4. TabbedWindowResizeRequestComponent
	// 5. TabbedWindowMovementRequestComponent
	class TabbedWindowSnapSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}