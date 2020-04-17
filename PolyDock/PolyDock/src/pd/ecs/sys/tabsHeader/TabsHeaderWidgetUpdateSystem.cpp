#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetUpdateSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAdding.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderWidgetUpdateSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		DirtyTabsHeaderComponent,
		TabsHeaderComponent,
		TabsHeaderWidgetComponent>();

	for (auto entity : view)
	{
		const auto& tabsHeader = view.get<TabsHeaderComponent>(entity);
		auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

		std::vector<std::string> tabsNames;
		std::vector<std::optional<QIcon>> tabsIcons;
		std::vector<int> selectedTabs;
		int hoveredTab = -1;
		int activeTab = -1;

		// gather tabs names and icons
		for (const entt::entity& ent : tabsHeader.tabs())
		{
			if (const auto* tab = registry.try_get<cmp::tab::TabComponent>(ent))
			{
				tabsNames.push_back(tab->name);
				tabsIcons.push_back(tab->icon);
			}
			else
			{
				tabsNames.push_back("Tab name not set");
				tabsIcons.push_back({});
			}
		}

		// gather selected tabs indices
		if (auto* cmp = registry.try_get<SelectedTabsComponent>(entity))
		{
			for (const entt::entity& tab : cmp->selectedTabs)
			{
				auto it = std::find(tabsHeader.tabs().begin(), tabsHeader.tabs().end(), tab);
				selectedTabs.push_back(std::distance(tabsHeader.tabs().begin(), it));
			}
		}

		// set hovered tab if any
		if (auto* cmp = registry.try_get<HoveredTabComponent>(entity))
		{
			auto it = std::find(tabsHeader.tabs().begin(), tabsHeader.tabs().end(), cmp->hoveredTab);
			hoveredTab = std::distance(tabsHeader.tabs().begin(), it);
		}

		// set active tab if any
		if (auto* cmp = registry.try_get<ActiveTabComponent>(entity))
		{
			auto it = std::find(tabsHeader.tabs().begin(), tabsHeader.tabs().end(), cmp->activeTab);
			activeTab = std::distance(tabsHeader.tabs().begin(), it);
		}

		ITabsHeaderWidget::eAddButtonState addButtonState = ITabsHeaderWidget::eAddButtonState::IDLE;
		if (registry.has<AddButtonHovered>(entity))
			addButtonState = ITabsHeaderWidget::eAddButtonState::HOVERED;
		else if (registry.has<AddButtonPressed>(entity))
			addButtonState = ITabsHeaderWidget::eAddButtonState::PRESSED;

		// update widget
		widget.update(std::move(tabsNames), std::move(tabsIcons), std::move(selectedTabs), hoveredTab, activeTab, addButtonState);

		// remove dirty flag component
		registry.remove<DirtyTabsHeaderComponent>(entity);
	}
}