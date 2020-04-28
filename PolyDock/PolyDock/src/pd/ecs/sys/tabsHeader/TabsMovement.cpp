#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovement.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->wasJustPressed(root::Input::eMouseButton::LEFT))
	{
		auto view = registry.view<
			tabsHeader::Component,
			tabsHeader::HoveredTab,
			tabsHeader::SelectedTabs,
			tabsHeader::Widget>();

		// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
		for (auto entity : view)
		{
			const auto& header = view.get<tabsHeader::Component>(entity);
			const auto& hovered = view.get<tabsHeader::HoveredTab>(entity);
			const auto& selected = view.get<tabsHeader::SelectedTabs>(entity);
			const auto& widget = view.get<tabsHeader::Widget>(entity);

			if (selected.selectedTabs.size() < header.tabs().size())
			{
				registry.assign<tabsHeader::TabsMovementActive>(entity,
					widget.getCursorPosInTabSpace(inputCmp->getCursorPos()));
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->wasJustReleased(cmp::root::Input::eMouseButton::LEFT))
	{
		auto view = registry.view<tabsHeader::TabsMovementActive>();

		for (auto entity : view)
			registry.remove<tabsHeader::TabsMovementActive>(entity);
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		tabsHeader::TabsMovementActive, 
		tabsHeader::SelectedTabs,
		tabsHeader::HoveredTab,
		tabsHeader::ActiveTab,
		tabsHeader::Component>();

	for (auto entity : view)
	{
		const auto& selected = registry.get<tabsHeader::SelectedTabs>(entity);
		const auto& hovered = registry.get<tabsHeader::HoveredTab>(entity);
		const auto& active = registry.get<tabsHeader::ActiveTab>(entity);
		const auto& header = registry.get<tabsHeader::Component>(entity);

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

			registry.assign<tabsHeader::TabsMovementRequest>(entity, newFirstSelectedTabIdx);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		tabsHeader::TabsMovementRequest, 
		tabsHeader::SelectedTabs, 
		tabsHeader::Component>();

	for (auto entity : view)
	{
		const auto& request = registry.get<tabsHeader::TabsMovementRequest>(entity);
		const auto& selected = registry.get<tabsHeader::SelectedTabs>(entity);
		auto& header = registry.get<tabsHeader::Component>(entity);

		for (const entt::entity tab : selected.selectedTabs)
			header.tabsMut().erase(std::remove(header.tabsMut().begin(), header.tabsMut().end(), tab));

		for (int i = 0; i < selected.selectedTabs.size(); ++i)
		{
			header.tabsMut().insert(header.tabs().begin() + request.indexRequestedForFirstMovedTab + i
				, selected.selectedTabs.at(i));
		}

		registry.remove<tabsHeader::TabsMovementRequest>(entity);
		registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
	}
}

} // namespace pd::ecs::sys