#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::Widget
	// 3. tabbedWindow::MinimizeRequest
	// 4. tabbedWindowControl::Component
	//
	// Removed
	// 1. tabbedWindow::MinimizeRequest
	// Modified
	// 1. tabbedWindow::Widget
	class TabbedWindowMinimizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::Widget
	// 3. tabbedWindow::RestoreRequest
	// 4. tabbedWindowControl::Component
	//
	// Removed
	// 1. tabbedWindow::RestoreRequest
	// Modified
	// 1. tabbedWindow::Widget
	class TabbedWindowRestoreSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::Widget
	// 3. tabbedWindow::MinimizeRequest
	// 4. tabbedWindowControl::Component
	//
	// Removed
	// 1. tabbedWindow::MaximizeRequest
	// Modified
	// 1. tabbedWindow::Widget
	class TabbedWindowMaximizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Desktop
	// 2. tabbedWindow::Component
	// 3. tabbedWindowControl::Component
	// 4. tabbedWindow::SnapRequest
	//
	// Added
	// 1. tabbedWindow::ResizeRequest
	// 2. tabbedWindow::MovementRequest
	// 3. tabbedWindow::MaximizeRequest
	// 4. tabbedWindow::RestoreRequest
	// 5. tabbedWindow::MinimizeRequest
	// Removed
	// 1. tabbedWindow::ResizeRequest
	// 2. tabbedWindow::MovementRequest
	// 3. tabbedWindow::SnapRequest
	class TabbedWindowSnapSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}