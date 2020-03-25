#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsMovementRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsMovementActiveComponent, 
		SelectedTabsComponent,
		HoveredTabComponent,
		ActiveTabComponent,
		TabsHeaderComponent>();

	for (auto entity : view)
	{
		const auto& selected = registry.get<SelectedTabsComponent>(entity);
		const auto& hovered = registry.get<HoveredTabComponent>(entity);
		const auto& active = registry.get<ActiveTabComponent>(entity);
		const auto& header = registry.get<TabsHeaderComponent>(entity);

		if (hovered.hoveredTab != active.activeTab)
		{
			const auto hoveredIt = std::find(header.tabs.begin(), header.tabs.end(), hovered.hoveredTab);
			const auto activeIt = std::find(header.tabs.begin(), header.tabs.end(), active.activeTab);
			const int moveDistance = std::distance(activeIt, hoveredIt);
			const int newActiveTabIdx = std::distance(header.tabs.begin(), activeIt) + moveDistance;
			const auto activeItInSelected 
				= std::find(selected.selectedTabs.begin(), selected.selectedTabs.end(), active.activeTab);
			const int activeIdxInSelected 
				= std::distance(selected.selectedTabs.begin(), activeItInSelected);
			const int maxIdxForFirstSelectedTab 
				= static_cast<int>(header.tabs.size() - selected.selectedTabs.size());
			const int newFirstSelectedTabIdx 
				= std::min(newActiveTabIdx - activeIdxInSelected, maxIdxForFirstSelectedTab);

			registry.assign<TabsMovementRequestComponent>(entity, newFirstSelectedTabIdx);
		}
	}
}