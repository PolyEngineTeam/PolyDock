#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::CloseRequest
	//
	// Removed
	// 1. tabbedWindow::CloseRequest
	// Added
	// 1. tabbedWindow::RemoveRequest
	class TabbedWindowCloseSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::WidgetsOwner
	// 2. tabbedWindow::RemoveRequest
	class TabbedWindowRemovalSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}