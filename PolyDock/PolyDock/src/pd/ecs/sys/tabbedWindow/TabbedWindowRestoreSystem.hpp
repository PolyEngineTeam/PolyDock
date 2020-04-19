#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. Component
	// 2. Widget
	// 3. RestoreRequest
	// 4. tabbedWindowControl/Component
	//
	// Removed
	// 1. RestoreRequest
	// Modified
	// 1. Widget
	class TabbedWindowRestoreSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}