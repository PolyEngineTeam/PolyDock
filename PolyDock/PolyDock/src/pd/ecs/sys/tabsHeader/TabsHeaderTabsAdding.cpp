#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderTabsAdding.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAdding.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::tab;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void AddButtonHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		auto view = registry.view<Widget>();

		for (auto entity : view)
		{
			const auto& widget = view.get<Widget>(entity);

			if (registry.has<AddButtonHovered>(entity))
			{
				if (!widget.hoversAddButton(inputComponent->getCursorPos()))
				{
					registry.remove<AddButtonHovered>(entity);
					registry.get_or_assign<WidgetUpdateRequest>(entity);
				}
			}
			else
			{
				if (widget.hoversAddButton(inputComponent->getCursorPos()))
				{
					registry.assign<AddButtonHovered>(entity);
					registry.get_or_assign<WidgetUpdateRequest>(entity);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void AddButtonPressSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		auto hoveredViews = registry.view<AddButtonHovered>();
		auto pressedViews = registry.view<AddButtonPressed>();

		if (inputComponent->wasJustPressed(InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : hoveredViews)
			{
				registry.assign<AddButtonPressed>(entity);
				registry.get_or_assign<WidgetUpdateRequest>(entity);
			}
		}
		else if (inputComponent->wasJustReleased(InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : pressedViews)
			{
				registry.remove<AddButtonPressed>(entity);
				registry.get_or_assign<WidgetUpdateRequest>(entity);

				if (registry.has<AddButtonHovered>(entity))
					registry.get_or_assign<AddTabRequest>(entity).requests.push_back({ false, {}, {} });
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, AddTabRequest>();

	for (auto entity : view)
	{
		const auto& requestCmp = registry.get<AddTabRequest>(entity);
		auto& headerCmp = registry.get<Component>(entity);
		
		for (const auto&[focus, index, ent] : requestCmp.requests)
		{
			entt::entity newTab;
			if (ent.has_value())
				newTab = ent.value();
			else
				newTab = registry.create();

			registry.get_or_assign<TabComponent>(newTab, "New tab", std::optional<QIcon>{});
			registry.get_or_assign<DirtyTabComponent>(newTab);
			registry.get_or_assign<DirtyTabContentComponent>(newTab);

			if (focus)
			{
				registry.get_or_assign<ActiveTab>(entity).activeTab = newTab;
				registry.get_or_assign<SelectedTabs>(entity).selectedTabs = { newTab };
			}

			if (index.has_value())
				headerCmp.insertTab(newTab, index.value());
			else
				headerCmp.appendTab(newTab);
		}

		registry.get_or_assign<WidgetUpdateRequest>(entity);
		registry.remove<AddTabRequest>(entity);
	}
}