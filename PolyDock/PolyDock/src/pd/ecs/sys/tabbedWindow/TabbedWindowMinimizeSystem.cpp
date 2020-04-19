#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMinimizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMinimizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent,
		TabbedWindowWidgetComponent,
		TabbedWindowMinimizeRequestComponent,
		Component>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<TabbedWindowWidgetComponent>(entity);
		auto& controlCmp = view.get<Component>(entity);

		widgetCmp.window->getWidget()->showMinimized();
		controlCmp.maximized = false;

		registry.remove<TabbedWindowMinimizeRequestComponent>(entity);
	}
}