#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsClosing.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsClosing.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsRemoving.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void CloseButtonHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabsHeader::Widget, tabsHeader::Component>();

		for (auto entity : view)
		{
			const auto& widget = view.get<tabsHeader::Widget>(entity);
			const auto& component = view.get<tabsHeader::Component>(entity);

			if (registry.has<tabsHeader::CloseButtonHovered>(entity))
			{
				if (widget.getHoveredCloseButtonIdx(inputComponent->getCursorPos()) == -1)
				{
					registry.remove<tabsHeader::CloseButtonHovered>(entity);
					registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
				}
			}
			else
			{
				const int index = widget.getHoveredCloseButtonIdx(inputComponent->getCursorPos());
				if (index != -1)
				{
					registry.assign<tabsHeader::CloseButtonHovered>(entity, component.tabs()[index]);
					registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void CloseButtonPressSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto hoveredViews = registry.view<tabsHeader::CloseButtonHovered>();
		auto pressedViews = registry.view<tabsHeader::CloseButtonPressed>();

		if (inputComponent->wasJustPressed(root::Input::eMouseButton::LEFT))
		{
			for (auto entity : hoveredViews)
			{
				registry.assign<tabsHeader::CloseButtonPressed>(entity);
				registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
			}
		}
		else if (inputComponent->wasJustReleased(root::Input::eMouseButton::LEFT))
		{
			for (auto entity : pressedViews)
			{
				registry.remove<tabsHeader::CloseButtonPressed>(entity);
				registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);

				if (const auto* hoverCmp = registry.try_get<tabsHeader::CloseButtonHovered>(entity))
				{
					registry.get_or_assign<tabsHeader::CloseTabRequest>(entity)
						.tabsToClose.push_back(hoverCmp->tab);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabCloseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabsHeader::Component, tabsHeader::CloseTabRequest>();

	for (auto entity : view)
	{
		const auto& requestCmp = registry.get<tabsHeader::CloseTabRequest>(entity);
		auto& headerCmp = registry.get<tabsHeader::Component>(entity);
		
		auto& removalRequest = registry.get_or_assign<tabsHeader::TabsRemovalRequest>(entity);
		removalRequest.tabsToRemove.insert(removalRequest.tabsToRemove.end(), requestCmp.tabsToClose.begin(),
			requestCmp.tabsToClose.end());

		registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
		registry.remove<tabsHeader::CloseTabRequest>(entity);
	}
}

} // namespace pd::ecs::sys