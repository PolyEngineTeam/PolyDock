#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. tabsHeader::Component
	// 2. tabsHeader::TabsRemovalRequest
	// 
	// Added
	// 1. tabsHeader::WidgetUpdateRequest
	// 2. tabsHeader::SelectedTabs
	// Removed
	// 1. tabsHeader::TabsRemovalRequest
	class TabsRemovalSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
