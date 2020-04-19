#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowFocusSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowFocusSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Widget>();

	for (auto entity : view)
	{
		const auto& widgetCmp = view.get<Widget>(entity);
		
		if (widgetCmp.window->getWidget()->isActiveWindow())
			registry.get_or_assign<Focused>(entity);
		else
			registry.remove_if_exists<Focused>(entity);
	}
}
