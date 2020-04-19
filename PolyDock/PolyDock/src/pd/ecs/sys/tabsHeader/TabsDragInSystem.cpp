#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragInSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragInSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsDragInRequest, Widget>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& request = view.get<TabsDragInRequest>(entity);
			const auto& widget = view.get<Widget>(entity);

			const auto& srcHeader = registry.get<Component>(request.source);
			const auto& srcSelectedTabs = registry.get<SelectedTabs>(request.source);
			const auto& srcActiveTab = registry.get<ActiveTab>(request.source);

			auto& dstHeader = registry.get<Component>(entity);
			auto& dstSelectedTabs = registry.get<SelectedTabs>(entity);
			auto& dstActiveTab = registry.get<ActiveTab>(entity);

			dstHeader.tabsMut().insert(dstHeader.tabs().begin() + request.destinationIndex, 
				srcHeader.tabs().begin(), srcHeader.tabs().end());
			dstSelectedTabs = srcSelectedTabs;
			dstActiveTab = srcActiveTab;

			registry.get_or_assign<TabsMovementActive>(entity, request.cursorInTabSpacePosition);

			registry.get_or_assign<WidgetUpdateRequest>(entity);
			registry.assign<TabbedWindowRemoveRequestComponent>(request.source);
			registry.remove<TabsDragInRequest>(entity);
		}
	}
}