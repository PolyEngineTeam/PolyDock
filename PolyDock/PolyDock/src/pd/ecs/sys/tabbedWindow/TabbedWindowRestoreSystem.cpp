#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRestoreSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRestoreRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowRestoreSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent, 
		TabbedWindowWidgetComponent, 
		TabbedWindowRestoreRequestComponent>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<TabbedWindowWidgetComponent>(entity);

		widgetCmp.window->getWidget()->showNormal();

		registry.remove<TabbedWindowRestoreRequestComponent>(entity);
	}
}