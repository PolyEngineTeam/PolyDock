#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. Desktop
	// 2. SnapRequest
	// 3. Component
	// 4. tabbedWindowControl/Component=
	//
	// Added
	// 1. RestoreRequest
	// Removed
	// 1. MaximizeRequest
	// 2. RestoreRequest
	// 3. MinimizeRequest
	// 4. ResizeRequest
	// 5. MovementRequest
	class TabbedWindowSnapSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}