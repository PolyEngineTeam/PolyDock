#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCreationSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCreateRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/Component.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowCreateRequestComponent>();

	for (auto entity : view)
	{
		const auto& request = view.get<TabbedWindowCreateRequestComponent>(entity);

		registry.assign<TabbedWindowComponent>(entity, request.position, request.size);
		registry.assign<TabsHeaderComponent>(entity, request.tabs);
		registry.assign<tabbedWindowControl::Component>(entity);
		registry.assign<SelectedTabsComponent>(entity, request.selectedTabs);
		if (request.activeTab.has_value())
			registry.assign<ActiveTabComponent>(entity, request.activeTab.value());

		if (request.windowMovementState == TabbedWindowCreateRequestComponent::eWindowMovementState::ACTIVE)
			registry.assign<TabbedWindowMovementActiveComponent>(entity, request.cursorInTabSpacePosition);

		registry.remove<TabbedWindowCreateRequestComponent>(entity);
	}
}