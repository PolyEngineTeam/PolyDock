#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// Required
	// 1. root::Input
	// 2. tabbedWindow::Component
	// 
	// Added / Removed
	// 1. tabbedWindow::ResizeHover
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// Required
	// 1. root::Input
	// 2. tabbedWindow::ResizeHover
	// 
	// Added
	// 1. tabbedWindow::ResizeActive
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeStartSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// Required
	// 1. root::Input
	// 2. tabbedWindow::ResizeActive
	// 
	// Removed
	// 1. tabbedWindow::ResizeActive
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeEndSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// Required
	// 1. root::Input
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::ResizeActive
	// 
	// Added
	// 1. tabbedWindow::Component
	// 2. tabbedWindow::ResizeActive
	// 3. tabbedWindow::ResizeRequest
	// 4. tabbedWindow::MovementRequest
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// Required
	// 1. tabbedWindow::ResizeRequest
	// 2. tabbedWindow::Component
	// 
	// Added
	// 1. tabbedWindow::RequestWidgetUpdate
	// Removed
	// 1. tabbedWindow::ResizeRequest
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}