#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsMovementActive, 
		SelectedTabs,
		HoveredTab,
		ActiveTab,
		Component>();

	for (auto entity : view)
	{
		const auto& selected = registry.get<SelectedTabs>(entity);
		const auto& hovered = registry.get<HoveredTab>(entity);
		const auto& active = registry.get<ActiveTab>(entity);
		const auto& header = registry.get<Component>(entity);

		if (hovered.hoveredTab != active.activeTab)
		{
			const auto hoveredIt = std::find(header.tabs().begin(), header.tabs().end(), hovered.hoveredTab);
			const auto activeIt = std::find(header.tabs().begin(), header.tabs().end(), active.activeTab);
			const int moveDistance = std::distance(activeIt, hoveredIt);
			const int newActiveTabIdx = std::distance(header.tabs().begin(), activeIt) + moveDistance;
			const auto activeItInSelected 
				= std::find(selected.selectedTabs.begin(), selected.selectedTabs.end(), active.activeTab);
			const int activeIdxInSelected 
				= std::distance(selected.selectedTabs.begin(), activeItInSelected);
			const int maxIdxForFirstSelectedTab 
				= static_cast<int>(header.tabs().size() - selected.selectedTabs.size());
			const int newFirstSelectedTabIdx 
				= std::min(newActiveTabIdx - activeIdxInSelected, maxIdxForFirstSelectedTab);

			registry.assign<TabsMovementRequest>(entity, newFirstSelectedTabIdx);
		}
	}
}