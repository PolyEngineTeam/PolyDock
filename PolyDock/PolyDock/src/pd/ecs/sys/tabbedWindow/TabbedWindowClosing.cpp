#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowClosing.hpp>

#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCloseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::Component, tabbedWindow::CloseRequest>();

	for (auto entity : view)
	{
		registry.remove<tabbedWindow::CloseRequest>(entity);
		registry.get_or_assign<tabbedWindow::RemoveRequest>(entity);
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* wiodgetsOwner = registry.try_get<root::WidgetsOwner>(root))
	{
		auto view = registry.view<tabbedWindow::RemoveRequest>();

		for (auto entity : view)
		{
			delete wiodgetsOwner->tabsHeaders.at(entity);
			delete wiodgetsOwner->windowControls.at(entity);
			delete wiodgetsOwner->windows.at(entity);
			wiodgetsOwner->tabsHeaders.erase(entity);
			wiodgetsOwner->windowControls.erase(entity);
			wiodgetsOwner->windows.erase(entity);
			registry.destroy(entity);
		}
	}
}

} // namespace ::pd::ecs::sys