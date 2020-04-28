#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::Component
	// 3. tabsHeader::Widget
	// 
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	// 2. tabsHeader::TabsRemovalRequest
	// Added / Removed
	// 1. tabsHeader::HoveredTab
	// 2. tabsHeader::HoveredHeader
	class TabsHeaderHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::HoveredTab
	// 
	// Added
	// 1. tabsHeader::ActiveTab
	// 2. tabsHeader::WidgetUpdateRequest
	// 3. tabbedWindow::RequestWidgetUpdate
	class TabsActivationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::HoveredTab
	// 
	// Added
	// 1. tabsHeader::ActiveTab
	// 2. tabsHeader::WidgetUpdateRequest
	// 3. tabbedWindow::RequestWidgetUpdate
	class TabsSelectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
