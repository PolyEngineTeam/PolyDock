#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragInSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragInRequestComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRemoveRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragInSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsDragInRequestComponent, TabsHeaderWidgetComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& request = view.get<TabsDragInRequestComponent>(entity);
			const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

			const auto& srcHeader = registry.get<TabsHeaderComponent>(request.source);
			const auto& srcSelectedTabs = registry.get<SelectedTabsComponent>(request.source);
			const auto& srcActiveTab = registry.get<ActiveTabComponent>(request.source);

			auto& dstHeader = registry.get<TabsHeaderComponent>(entity);
			auto& dstSelectedTabs = registry.get<SelectedTabsComponent>(entity);
			auto& dstActiveTab = registry.get<ActiveTabComponent>(entity);

			dstHeader.tabsMut().insert(dstHeader.tabs().begin() + request.destinationIndex, 
				srcHeader.tabs().begin(), srcHeader.tabs().end());
			dstSelectedTabs = srcSelectedTabs;
			dstActiveTab = srcActiveTab;

			registry.get_or_assign<TabsMovementActiveComponent>(entity, request.cursorInTabSpacePosition);

			registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
			registry.assign<TabbedWindowRemoveRequestComponent>(request.source);
			registry.remove<TabsDragInRequestComponent>(entity);
		}
	}
}