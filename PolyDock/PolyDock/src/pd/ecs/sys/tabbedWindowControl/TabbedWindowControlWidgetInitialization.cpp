#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetInitialization.hpp>

#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>(entt::exclude<Widget>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwner>(root))
	{
		for (auto entity : view)
		{
			IWidget* widget = new DefaultWidget();
			widgetsOwner->windowControls.insert({ entity, widget });

			registry.assign<Widget>(entity, widget);
		}
	}
}