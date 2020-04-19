#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetInitializationSystem.hpp>

// in
#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>(entt::exclude<Widget>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwner>(root))
	{
		for (auto entity : view)
		{
			DefaultTabsHeaderWidget* widget = new DefaultTabsHeaderWidget();
			widgetsOwner->tabsHeaders.insert({ entity, widget });

			registry.assign<Widget>(entity, widget);
			registry.get_or_assign<WidgetUpdateRequest>(entity);
		}
	}
}