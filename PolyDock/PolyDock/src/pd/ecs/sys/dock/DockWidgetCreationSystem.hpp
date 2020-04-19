#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. WidgetsOwner
	// 2. Component
	// Banned
	// 1. Widget
	//
	// Added
	// 1. Widget
	// Modified
	// 1. WidgetsOwner
	class DockWidgetCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}