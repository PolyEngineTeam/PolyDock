#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetInitializationSystem.hpp>

// in
#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderComponent>(entt::exclude<TabsHeaderWidgetComponent>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwnerComponent>(root))
	{
		for (auto entity : view)
		{
			DefaultTabsHeaderWidget* widget = new DefaultTabsHeaderWidget();
			widgetsOwner->tabsHeaders.insert({ entity, widget });

			registry.assign<TabsHeaderWidgetComponent>(entity, widget);
			registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
		}
	}
}