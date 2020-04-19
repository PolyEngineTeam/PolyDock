#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::Component
	// 3. tabsHeader::HoveredTab
	// 4. tabsHeader::SelectedTabs
	// 5. tabsHeader::Widget
	// 
	// Added
	// 1. tabsHeader::TabsMovementActive
	class TabsMovementStartSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::TabsMovementActive
	// 
	// Added
	// 1. tabsHeader::TabsMovementActive
	class TabsMovementEndSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::TabsMovementActive
	// 2. tabsHeader::SelectedTabs
	// 3. tabsHeader::HoveredTab
	// 4. tabsHeader::ActiveTab
	// 5. tabsHeader::Component
	// 
	// Added
	// 1. tabsHeader::TabsMovementRequest
	class TabsMovementDetectionSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::TabsMovementRequest
	// 2. tabsHeader::SelectedTabs
	// 3. tabsHeader::Component
	// 
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	// Removed
	// 1. tabsHeader::TabsMovementRequest
	class TabsMovementSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
