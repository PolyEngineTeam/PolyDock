#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// Required
	// 1. ResizeRequest
	// 2. Component
	// 
	// Added
	// 1. RequestWidgetUpdate
	// Modified
	// 1. Component
	// Removed
	// 1. ResizeRequest
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}