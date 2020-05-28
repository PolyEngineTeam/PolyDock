#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeader.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsRemoving.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabsHeader::Component, tabsHeader::Widget>();

		for (auto entity : view)
		{
			const auto& tabsHeader = view.get<tabsHeader::Component>(entity);
			const auto& widget = view.get<tabsHeader::Widget>(entity);

			const int hoveredIdx = widget.getTabIdxFromPosition(inputCmp->getCursorPos());

			if (hoveredIdx != -1)
			{
				const entt::entity hoveredTab = tabsHeader.tabs().at(hoveredIdx);
				registry.get_or_assign<tabsHeader::HoveredTab>(entity).hoveredTab = hoveredTab;
				registry.get_or_assign<tabsHeader::HoveredHeader>(entity);
				registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);

				if (inputCmp->wasJustReleased(root::Input::eMouse::MIDDLE))
				{
					registry.get_or_assign<tabsHeader::TabsRemovalRequest>(entity, hoveredTab);
					registry.remove<tabsHeader::HoveredTab>(entity);
				}
			}
			else
			{
				if (registry.has<tabsHeader::HoveredTab>(entity))
				{
					registry.remove<tabsHeader::HoveredTab>(entity);
					registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
				}

				if (widget.getWidgetRect().contains(inputCmp->getCursorPos()))
					registry.get_or_assign<tabsHeader::HoveredHeader>(entity);
				else if (registry.has<tabsHeader::HoveredHeader>(entity))
					registry.remove<tabsHeader::HoveredHeader>(entity);
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsActivationSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputCmp = registry.try_get<root::Input>(root); inputCmp 
		&& inputCmp->wasJustPressed(cmp::root::Input::eMouse::LEFT))
	{
		auto view = registry.view<tabsHeader::HoveredTab>();

		// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
		for (auto entity : view)
		{
			auto& hovered = view.get<tabsHeader::HoveredTab>(entity);

			registry.get_or_assign<tabsHeader::ActiveTab>(entity).activeTab = hovered.hoveredTab;
			registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
			registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsSelectionSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputCmp = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabsHeader::HoveredTab>();

		for (auto entity : view)
		{
			const auto& hoveredCmp = view.get<tabsHeader::HoveredTab>(entity);
			auto& selectedCmp = registry.get_or_assign<tabsHeader::SelectedTabs>(entity);
			const bool hoveredIsAlreadySelected = std::find(selectedCmp.selectedTabs.begin(), 
				selectedCmp.selectedTabs.end(), hoveredCmp.hoveredTab) != selectedCmp.selectedTabs.end();

			if (inputCmp->wasJustPressed(root::Input::eMouse::LEFT))
			{
				// CTRL toggles selection
				if (inputCmp->isPressed(root::Input::eKeyboard::CTRL))
				{
					if (hoveredIsAlreadySelected)
						selectedCmp.selectedTabs.erase(std::remove(selectedCmp.selectedTabs.begin(), selectedCmp.selectedTabs.end(), hoveredCmp.hoveredTab));
					else
						selectedCmp.selectedTabs.push_back(hoveredCmp.hoveredTab);
				} 
				else
					selectedCmp.selectedTabs = { hoveredCmp.hoveredTab };
				// selecting a new tab without control, unselects all except the newly hovered tab

				registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
			}
		}
	}
}

} // namespace pd::ecs::sys