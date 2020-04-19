#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMaximizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys::tabbedWindow
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMaximizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabbedWindow::Component,
		::tabbedWindow::Widget,
		::tabbedWindow::MaximizeRequest,
		tabbedWindowControl::Component>();

	for (auto entity : view)
	{
		auto& widgetCmp = view.get<::tabbedWindow::Widget>(entity);
		auto& controlCmp = view.get<tabbedWindowControl::Component>(entity);

		widgetCmp.window->getWidget()->showMaximized();
		controlCmp.maximized = true;

		registry.remove<::tabbedWindow::MaximizeRequest>(entity);
	}
}

} // namespace pd::ecs::sys::tabbedWindow