#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabbedWindow::MovementActive
	// 3. tabsHeader::HoveredTab
	// 
	// Added
	// 1. tabsHeader::TabsDragInRequest
	class TabsDragInDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::Widget
	// 3. tabsHeader::TabsMovementActive
	// 
	// Added
	// 1. tabsHeader::TabsDragOutRequest
	class TabsDragOutDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::TabsDragInRequest
	// 3. tabsHeader::Widget
	// 
	// Added
	// 1. tabsHeader::TabsMovementActive
	// 2. tabsHeader::WidgetUpdateRequest
	// 3. tabbedWindow::RemoveRequest
	// Removed
	// 1. tabsHeader::TabsDragInRequest
	class TabsDragInSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::TabsDragOutRequest
	// 3. tabsHeader::Component
	// 4. tabsHeader::SelectedTabs
	// 5. tabsHeader::ActiveTab
	// 6. tabsHeader::TabsMovementActive
	// 
	// Added
	// 1. tabbedWindow::CreateRequest
	// 2. tabsHeader::WidgetUpdateRequest
	// 3. tabbedWindow::RequestWidgetUpdate
	// Removed
	// 1. tabsHeader::TabsDragOutRequest
	// 2. tabsHeader::TabsMovementActive
	class TabsDragOutSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
