#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementStartSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsMovementActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsHeaderComponent,
		HoveredTabComponent, 
		SelectedTabsComponent,
		TabsHeaderWidgetComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustPressed(cmp::root::InputComponent::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				const auto& header = view.get<TabsHeaderComponent>(entity);
				const auto& hovered = view.get<HoveredTabComponent>(entity);
				const auto& selected = view.get<SelectedTabsComponent>(entity);
				const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

				if (selected.selectedTabs.size() < header.tabs().size())
				{
					registry.assign<TabsMovementActiveComponent>(entity,
						widget.getCursorPosInTabSpace(inputComponent->getCursorPos()));
				}
			}
		}
	}
}