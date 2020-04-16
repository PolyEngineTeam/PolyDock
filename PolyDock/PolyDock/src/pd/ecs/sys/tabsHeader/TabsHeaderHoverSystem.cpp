#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderHoverSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsRemovalRequest.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderComponent, TabsHeaderWidgetComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& tabsHeader = view.get<TabsHeaderComponent>(entity);
			const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

			const int hoveredIdx = widget.getTabIdxFromPosition(inputComponent->getCursorPos());

			if (hoveredIdx != -1)
			{
				const entt::entity hoveredTab = tabsHeader.tabs().at(hoveredIdx);
				registry.get_or_assign<HoveredTabComponent>(entity).hoveredTab = hoveredTab;
				registry.get_or_assign<HoveredTabsHeaderComponent>(entity);
				registry.get_or_assign<DirtyTabsHeaderComponent>(entity);

				if (inputComponent->wasJustReleased(InputComponent::eMouseButton::MIDDLE))
				{
					registry.get_or_assign<TabsRemovalRequest>(entity, hoveredTab);
					registry.remove<HoveredTabComponent>(entity);
				}
			}
			else
			{
				if (registry.has<HoveredTabComponent>(entity))
				{
					registry.remove<HoveredTabComponent>(entity);
					registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
				}

				if (widget.getWidgetRect().contains(inputComponent->getCursorPos()))
					registry.get_or_assign<HoveredTabsHeaderComponent>(entity);
				else if (registry.has<HoveredTabsHeaderComponent>(entity))
					registry.remove<HoveredTabsHeaderComponent>(entity);
			}
		}
	}
}