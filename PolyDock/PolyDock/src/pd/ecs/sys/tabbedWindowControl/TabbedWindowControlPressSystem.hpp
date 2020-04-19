#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root/Input
	// 2. tabbedWindowControl/Component
	// Optional
	// 1. tabbedWindowControl/Hover
	//
	// Removed/Added/Modified
	// 1. tabbedWindowControl/Press
	// Added
	// 1. tabbedWindowControl/WidgetUpdateRequest
	class TabbedWindowControlPressSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}