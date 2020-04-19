#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. Component
	// 2. Widget
	// 3. CloseRequest
	//
	// Removed
	// 1. CloseRequest
	// Added
	// 1. RemoveRequest
	class TabbedWindowCloseSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}