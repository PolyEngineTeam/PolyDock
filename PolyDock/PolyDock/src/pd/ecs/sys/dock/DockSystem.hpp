#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. Component
	// 2. DockRequest
	//
	// Added
	// 1. WidgetUpdateRequest
	// Removed
	// 1. DockRequest
	class DockSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}