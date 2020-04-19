#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindow.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowFocusSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::Widget>();

	for (auto entity : view)
	{
		const auto& widgetCmp = view.get<tabbedWindow::Widget>(entity);

		if (widgetCmp.window->getWidget()->isActiveWindow())
			registry.get_or_assign<tabbedWindow::Focused>(entity);
		else
			registry.remove_if_exists<tabbedWindow::Focused>(entity);
	}
}

} // namespace ::pd::ecs::sys