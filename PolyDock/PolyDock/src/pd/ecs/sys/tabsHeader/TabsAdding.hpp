#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::Widget
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonHovered
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	class AddButtonHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::AddButtonHovered
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonPressed
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	// 2. tabsHeader::AddTabRequest
	class AddButtonPressSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::Component
	// 2. tabsHeader::AddTabRequest
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonPressed
	// 2. tabsHeader::ActiveTab
	// Removed
	// 1. tabsHeader::AddTabRequest
	class TabsCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
