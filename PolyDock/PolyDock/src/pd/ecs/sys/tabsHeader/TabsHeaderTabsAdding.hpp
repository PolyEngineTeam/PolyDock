#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::InputComponent
	// 2. tabsHeader::TabsHeaderWidgetComponent
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonHovered
	// Added
	// 1. tabsHeader::DirtyTabsHeaderComponent
	class AddButtonHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::InputComponent
	// 2. tabsHeader::AddButtonHovered
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonPressed
	// Added
	// 1. tabsHeader::DirtyTabsHeaderComponent
	// 2. tabsHeader::AddTabRequest
	class AddButtonPressSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::TabsHeaderComponent
	// 2. tabsHeader::AddTabRequest
	// 
	// Added / Removed
	// 1. tabsHeader::AddButtonPressed
	// 2. tabsHeader::ActiveTabComponent
	// Removed
	// 1. tabsHeader::AddTabRequest
	class TabsCreationSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
