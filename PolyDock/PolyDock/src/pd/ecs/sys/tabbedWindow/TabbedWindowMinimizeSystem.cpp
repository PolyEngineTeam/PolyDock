#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMinimizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys::tabbedWindow
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMinimizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabbedWindow::Component,
		::tabbedWindow::Widget,
		::tabbedWindow::MinimizeRequest,
		tabbedWindowControl::Component>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<::tabbedWindow::Widget>(entity);
		auto& controlCmp = view.get<tabbedWindowControl::Component>(entity);

		widgetCmp.window->getWidget()->showMinimized();
		controlCmp.maximized = false;

		registry.remove<::tabbedWindow::MinimizeRequest>(entity);
	}
}

} // namespace pd::ecs::sys::tabbedWindow