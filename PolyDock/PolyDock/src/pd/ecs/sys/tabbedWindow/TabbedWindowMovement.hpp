#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::Widget
	// 3. tabsHeader::Component
	// 4. tabsHeader::SelectedTabs
	//
	// Added
	// 1. tabbedWindow::MovementActive
	class TabbedWindowMovementStartSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. root::Desktop
	// 3. tabbedWindow::MovementActive
	// 4. tabbedWindow::Component
	//
	// Removed
	// 1. tabbedWindow::MovementActive
	// Added
	// 1. tabbedWindow::SnapRequest
	class TabbedWindowMovementEndSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::MovementActive
	// 2. tabbedWindow::Component
	// 3. tabbedWindowControl::Component
	//
	// Added
	// 1. tabbedWindow::RestoreRequest
	// 2. tabbedWindow::MovementRequest
	class TabbedWindowMovementDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabbedWindow::MovementRequest
	// 2. tabbedWindow::Component
	//
	// Removed
	// 1. tabbedWindow::MovementRequest
	// Added
	// 1. tabbedWindow::RequestWidgetUpdate
	class TabbedWindowMovementSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}