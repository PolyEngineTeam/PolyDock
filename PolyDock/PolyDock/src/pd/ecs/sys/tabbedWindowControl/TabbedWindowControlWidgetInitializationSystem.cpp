#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetInitializationSystem.hpp>

#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/Component.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/WidgetComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>(entt::exclude<WidgetComponent>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwnerComponent>(root))
	{
		for (auto entity : view)
		{
			IWidget* widget = new DefaultWidget();
			widgetsOwner->windowControls.insert({ entity, widget });

			registry.assign<WidgetComponent>(entity, widget);
		}
	}
}