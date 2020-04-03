#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. InputComponent
	// 1. TabbedWindowComponent
	// 2. TabbedWindowResizeActiveComponent
	// 
	// Added
	// 1. TabbedWindowResizeRequestComponent
	// 2. TabbedWindowMovementRequestComponent
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}