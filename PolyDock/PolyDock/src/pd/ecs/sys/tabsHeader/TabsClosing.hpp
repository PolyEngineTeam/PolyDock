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
	// 1. tabsHeader::CloseButtonHovered
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	class CloseButtonHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root::Input
	// 2. tabsHeader::CloseButtonHovered
	// 
	// Added / Removed
	// 1. tabsHeader::CloseButtonPressed
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	// 2. tabsHeader::CloseTabRequest
	class CloseButtonPressSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};

	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::Component
	// 2. tabsHeader::CloseTabRequest
	// 
	// Added / Removed
	// 2. tabsHeader::TabsRemovalRequest
	// Removed
	// 1. tabsHeader::AddTabRequest
	class TabCloseSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
