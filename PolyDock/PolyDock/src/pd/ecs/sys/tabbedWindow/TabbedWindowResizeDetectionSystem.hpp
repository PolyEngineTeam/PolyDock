#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// Required
	// 1. Input
	// 1. Component
	// 2. ResizeActive
	// 
	// Added
	// 1. ResizeRequest
	// 2. MovementRequest
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}