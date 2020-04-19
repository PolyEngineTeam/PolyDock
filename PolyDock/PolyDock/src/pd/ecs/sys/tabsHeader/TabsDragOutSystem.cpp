#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragOutSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Opening.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsDragOutSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabsHeader::TabsDragOutRequest,
		::tabsHeader::Component,
		::tabsHeader::SelectedTabs,
		::tabsHeader::ActiveTab,
		::tabsHeader::TabsMovementActive>();

	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		for (auto entity : view)
		{
			auto& header = view.get<tabsHeader::Component>(entity);
			auto& selected = view.get<tabsHeader::SelectedTabs>(entity);
			auto& active = view.get<tabsHeader::ActiveTab>(entity);
			const auto& tabsMovement = view.get<tabsHeader::TabsMovementActive>(entity);

			const Vector2i windowPos = inputComponent->getCursorPos() - tabsMovement.cursorInTabSpacePosition;
			const size_t activeTabIdx = std::distance(header.tabs().begin(),
				std::find(header.tabs().begin(), header.tabs().end(), active.activeTab));

			for (const entt::entity& ent : selected.selectedTabs)
				header.tabsMut().erase(std::remove(header.tabsMut().begin(), header.tabsMut().end(), ent));

			auto newWindow = registry.create();
			registry.assign<tabbedWindow::CreateRequest>(newWindow, selected.selectedTabs, std::move(selected.selectedTabs),
				active.activeTab, windowPos, Vector2i{ 500, 500 }, tabbedWindow::CreateRequest::eWindowMovementState::ACTIVE,
				tabsMovement.cursorInTabSpacePosition);

			active.activeTab = header.tabs().at(std::min(activeTabIdx, header.tabs().size() - 1));
			selected.selectedTabs = { active.activeTab };
			registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
			registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
			registry.remove<tabsHeader::TabsDragOutRequest>(entity);
			registry.remove<tabsHeader::TabsMovementActive>(entity);
		}
	}
}

} // namespace pd::ecs::sys
