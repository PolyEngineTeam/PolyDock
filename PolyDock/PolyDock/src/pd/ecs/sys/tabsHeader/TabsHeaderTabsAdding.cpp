#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderTabsAdding.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAdding.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys::tabsHeader
{

// ---------------------------------------------------------------------------------------------------------
void AddButtonHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<::tabsHeader::Widget>();

		for (auto entity : view)
		{
			const auto& widget = view.get<::tabsHeader::Widget>(entity);

			if (registry.has<::tabsHeader::AddButtonHovered>(entity))
			{
				if (!widget.hoversAddButton(inputComponent->getCursorPos()))
				{
					registry.remove<::tabsHeader::AddButtonHovered>(entity);
					registry.get_or_assign<::tabsHeader::WidgetUpdateRequest>(entity);
				}
			}
			else
			{
				if (widget.hoversAddButton(inputComponent->getCursorPos()))
				{
					registry.assign<::tabsHeader::AddButtonHovered>(entity);
					registry.get_or_assign<::tabsHeader::WidgetUpdateRequest>(entity);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void AddButtonPressSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto hoveredViews = registry.view<::tabsHeader::AddButtonHovered>();
		auto pressedViews = registry.view<::tabsHeader::AddButtonPressed>();

		if (inputComponent->wasJustPressed(root::Input::eMouseButton::LEFT))
		{
			for (auto entity : hoveredViews)
			{
				registry.assign<::tabsHeader::AddButtonPressed>(entity);
				registry.get_or_assign<::tabsHeader::WidgetUpdateRequest>(entity);
			}
		}
		else if (inputComponent->wasJustReleased(root::Input::eMouseButton::LEFT))
		{
			for (auto entity : pressedViews)
			{
				registry.remove<::tabsHeader::AddButtonPressed>(entity);
				registry.get_or_assign<::tabsHeader::WidgetUpdateRequest>(entity);

				if (registry.has<::tabsHeader::AddButtonHovered>(entity))
					registry.get_or_assign<::tabsHeader::AddTabRequest>(entity).requests.push_back({ false, {}, {} });
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<::tabsHeader::Component, ::tabsHeader::AddTabRequest>();

	for (auto entity : view)
	{
		const auto& requestCmp = registry.get<::tabsHeader::AddTabRequest>(entity);
		auto& headerCmp = registry.get<::tabsHeader::Component>(entity);
		
		for (const auto&[focus, index, ent] : requestCmp.requests)
		{
			entt::entity newTab;
			if (ent.has_value())
				newTab = ent.value();
			else
				newTab = registry.create();

			registry.get_or_assign<tab::Component>(newTab, "New tab", std::optional<QIcon>{});
			registry.get_or_assign<tab::RefreshTab>(newTab);
			registry.get_or_assign<tab::RefreshTabContent>(newTab);

			if (focus)
			{
				registry.get_or_assign<::tabsHeader::ActiveTab>(entity).activeTab = newTab;
				registry.get_or_assign<::tabsHeader::SelectedTabs>(entity).selectedTabs = { newTab };
			}

			if (index.has_value())
				headerCmp.insertTab(newTab, index.value());
			else
				headerCmp.appendTab(newTab);
		}

		registry.get_or_assign<::tabsHeader::WidgetUpdateRequest>(entity);
		registry.remove<::tabsHeader::AddTabRequest>(entity);
	}
}

} // namespace pd::ecs::sys::tabsHeader