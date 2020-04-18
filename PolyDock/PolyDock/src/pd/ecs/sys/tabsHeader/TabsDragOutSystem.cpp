#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragOutSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCreateRequestComponent.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragOutSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsDragOutRequestComponent,
		TabsHeaderComponent,
		SelectedTabsComponent,
		ActiveTabComponent,
		TabsMovementActiveComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			auto& header = view.get<TabsHeaderComponent>(entity);
			auto& selected = view.get<SelectedTabsComponent>(entity);
			auto& active = view.get<ActiveTabComponent>(entity);
			const auto& tabsMovement = view.get<TabsMovementActiveComponent>(entity);

			const Vector2i windowPos = inputComponent->getCursorPos() - tabsMovement.cursorInTabSpacePosition;
			const size_t activeTabIdx = std::distance(header.tabs().begin(),
				std::find(header.tabs().begin(), header.tabs().end(), active.activeTab));

			for (const entt::entity& ent : selected.selectedTabs)
				header.tabsMut().erase(std::remove(header.tabsMut().begin(), header.tabsMut().end(), ent));

			auto newWindow = registry.create();
			registry.assign<TabbedWindowCreateRequestComponent>(newWindow, selected.selectedTabs, std::move(selected.selectedTabs),
				active.activeTab, windowPos, Vector2i{ 500, 500 }, TabbedWindowCreateRequestComponent::eWindowMovementState::ACTIVE,
				tabsMovement.cursorInTabSpacePosition);

			active.activeTab = header.tabs().at(std::min(activeTabIdx, header.tabs().size() - 1));
			selected.selectedTabs = { active.activeTab };
			registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
			registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
			registry.remove<TabsDragOutRequestComponent>(entity);
			registry.remove<TabsMovementActiveComponent>(entity);
		}
	}
}