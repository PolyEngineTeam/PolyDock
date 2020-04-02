#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRestoreSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRestoreRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/Component.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowRestoreSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent, 
		TabbedWindowWidgetComponent, 
		TabbedWindowRestoreRequestComponent,
		Component>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<TabbedWindowWidgetComponent>(entity);
		auto& controlCmp = view.get<Component>(entity);

		widgetCmp.window->getWidget()->showNormal();
		controlCmp.maximized = false;

		registry.remove<TabbedWindowRestoreRequestComponent>(entity);
	}
}