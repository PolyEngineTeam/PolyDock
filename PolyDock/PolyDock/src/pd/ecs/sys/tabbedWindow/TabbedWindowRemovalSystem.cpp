#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRemovalSystem.hpp>

// in
#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRemoveRequestComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowRemoveRequestComponent>();

	if (auto* wiodgetsOwner = registry.try_get<WidgetsOwnerComponent>(root))
	{
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