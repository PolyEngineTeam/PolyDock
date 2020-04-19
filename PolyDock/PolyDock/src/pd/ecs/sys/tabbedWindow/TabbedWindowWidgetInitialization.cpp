#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetInitialization.hpp>

// in
#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowWidgetInitializationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::Component>(entt::exclude<tabbedWindow::Widget>);

	if (auto* widgetsOwner = registry.try_get<root::WidgetsOwner>(root))
	{
		for (auto entity : view)
		{
			::tabbedWindow::DefaultTabbedWindowWidget* widget = new ::tabbedWindow::DefaultTabbedWindowWidget();
			widgetsOwner->windows.insert({ entity, widget });

			registry.assign<tabbedWindow::Widget>(entity, widget);
			registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
		}
	}
}

} // namespace pd::ecs::sys
