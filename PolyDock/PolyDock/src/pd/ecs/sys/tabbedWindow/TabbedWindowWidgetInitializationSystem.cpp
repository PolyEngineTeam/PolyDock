#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetInitializationSystem.hpp>

// in
#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowComponent>(entt::exclude<TabbedWindowWidgetComponent>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwnerComponent>(root))
	{
		for (auto entity : view)
		{
			DefaultTabbedWindowWidget* widget = new DefaultTabbedWindowWidget();
			widgetsOwner->windows.insert({ entity, widget });

			registry.assign<TabbedWindowWidgetComponent>(entity, widget);
			registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
		}
	}
}