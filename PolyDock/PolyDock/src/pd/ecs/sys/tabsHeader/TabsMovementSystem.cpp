#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsMovementRequest, 
		SelectedTabs, 
		Component>();

	for (auto entity : view)
	{
		const auto& request = registry.get<TabsMovementRequest>(entity);
		const auto& selected = registry.get<SelectedTabs>(entity);
		auto& header = registry.get<Component>(entity);

		for (const entt::entity tab : selected.selectedTabs)
			header.tabsMut().erase(std::remove(header.tabsMut().begin(), header.tabsMut().end(), tab));

		for (int i = 0; i < selected.selectedTabs.size(); ++i)
		{
			header.tabsMut().insert(header.tabs().begin() + request.indexRequestedForFirstMovedTab + i
				, selected.selectedTabs.at(i));
		}

		registry.remove<TabsMovementRequest>(entity);
		registry.get_or_assign<WidgetUpdateRequest>(entity);
	}
}