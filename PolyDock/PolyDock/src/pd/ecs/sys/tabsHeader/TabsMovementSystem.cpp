#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsMovementRequestComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsMovementRequestComponent, 
		SelectedTabsComponent, 
		TabsHeaderComponent>();

	for (auto entity : view)
	{
		const auto& request = registry.get<TabsMovementRequestComponent>(entity);
		const auto& selected = registry.get<SelectedTabsComponent>(entity);
		auto& header = registry.get<TabsHeaderComponent>(entity);

		for (const entt::entity tab : selected.selectedTabs)
			header.tabs.erase(std::remove(header.tabs.begin(), header.tabs.end(), tab));

		for (int i = 0; i < selected.selectedTabs.size(); ++i)
		{
			header.tabs.insert(header.tabs.begin() + request.indexRequestedForFirstMovedTab + i
				, selected.selectedTabs.at(i));
		}

		registry.remove<TabsMovementRequestComponent>(entity);
		registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
	}
}