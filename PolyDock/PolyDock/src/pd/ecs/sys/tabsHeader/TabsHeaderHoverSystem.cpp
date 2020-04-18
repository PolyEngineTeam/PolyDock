#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderHoverSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsRemoving.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, Widget>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& tabsHeader = view.get<Component>(entity);
			const auto& widget = view.get<Widget>(entity);

			const int hoveredIdx = widget.getTabIdxFromPosition(inputComponent->getCursorPos());

			if (hoveredIdx != -1)
			{
				const entt::entity hoveredTab = tabsHeader.tabs().at(hoveredIdx);
				registry.get_or_assign<HoveredTab>(entity).hoveredTab = hoveredTab;
				registry.get_or_assign<HoveredHeader>(entity);
				registry.get_or_assign<WidgetUpdateRequest>(entity);

				if (inputComponent->wasJustReleased(InputComponent::eMouseButton::MIDDLE))
				{
					registry.get_or_assign<TabsRemovalRequest>(entity, hoveredTab);
					registry.remove<HoveredTab>(entity);
				}
			}
			else
			{
				if (registry.has<HoveredTab>(entity))
				{
					registry.remove<HoveredTab>(entity);
					registry.get_or_assign<WidgetUpdateRequest>(entity);
				}

				if (widget.getWidgetRect().contains(inputComponent->getCursorPos()))
					registry.get_or_assign<HoveredHeader>(entity);
				else if (registry.has<HoveredHeader>(entity))
					registry.remove<HoveredHeader>(entity);
			}
		}
	}
}