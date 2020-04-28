#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDraggingInOut.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>
#include <pd/ecs/cmp/tabbedWindow/Opening.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsDragInDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root))
	{
		auto srcView = registry.view<tabbedWindow::MovementActive, tabsHeader::HoveredTab>();
		auto dstView = registry.view<
			tabsHeader::Widget,
			tabsHeader::Component
		>(entt::exclude<tabbedWindow::MovementActive>);

		for (auto source : srcView)
		{
			for (auto destination : dstView)
			{
				const auto& movementCmp = srcView.get<tabbedWindow::MovementActive>(source);
				const auto& dstWidget = dstView.get<tabsHeader::Widget>(destination);
				const auto& dstHeader = dstView.get<tabsHeader::Component>(destination);
				int dstPos = dstWidget.getTabIdxFromPosition(inputCmp->getCursorPos());

				if (dstPos == -1 && dstWidget.isPositionOnTheRightOfLastTab(inputCmp->getCursorPos()))
					dstPos = static_cast<int>(dstHeader.tabs().size());

				if (dstPos != -1 && dstWidget.getWidgetRect().contains(inputCmp->getCursorPos()))
				{
					registry.assign<tabsHeader::TabsDragInRequest>(destination, source, dstPos,
						movementCmp.cursorInTabSpacePosition);
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsDragOutDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabsHeader::Widget, tabsHeader::TabsMovementActive>();

		if (inputComponent->getCursorDiff() != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				auto& widget = registry.get<tabsHeader::Widget>(entity);

				auto pos = inputComponent->getCursorPos();
				auto rect = widget.getWidgetRect();

				if (!widget.getWidgetRect().contains(inputComponent->getCursorPos()))
					registry.assign<tabsHeader::TabsDragOutRequest>(entity);
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsDragInSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabsHeader::TabsDragInRequest, tabsHeader::Widget>();

		for (auto entity : view)
		{
			const auto& request = view.get<tabsHeader::TabsDragInRequest>(entity);
			const auto& widget = view.get<tabsHeader::Widget>(entity);

			const auto& srcHeader = registry.get<tabsHeader::Component>(request.source);
			const auto& srcSelectedTabs = registry.get<tabsHeader::SelectedTabs>(request.source);
			const auto& srcActiveTab = registry.get<tabsHeader::ActiveTab>(request.source);

			auto& dstHeader = registry.get<tabsHeader::Component>(entity);
			auto& dstSelectedTabs = registry.get<tabsHeader::SelectedTabs>(entity);
			auto& dstActiveTab = registry.get<tabsHeader::ActiveTab>(entity);

			dstHeader.tabsMut().insert(dstHeader.tabs().begin() + request.destinationIndex, 
				srcHeader.tabs().begin(), srcHeader.tabs().end());
			dstSelectedTabs = srcSelectedTabs;
			dstActiveTab = srcActiveTab;

			registry.get_or_assign<tabsHeader::TabsMovementActive>(entity, request.cursorInTabSpacePosition);

			registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
			registry.assign<tabbedWindow::RemoveRequest>(request.source);
			registry.remove<tabsHeader::TabsDragInRequest>(entity);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabsDragOutSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<
			tabsHeader::TabsDragOutRequest,
			tabsHeader::Component,
			tabsHeader::SelectedTabs,
			tabsHeader::ActiveTab,
			tabsHeader::TabsMovementActive>();

		for (auto entity : view)
		{
			auto& header = view.get<tabsHeader::Component>(entity);
			auto& selected = view.get<tabsHeader::SelectedTabs>(entity);
			auto& active = view.get<tabsHeader::ActiveTab>(entity);
			const auto& tabsMovement = view.get<tabsHeader::TabsMovementActive>(entity);

			const Vector2i windowPos = inputCmp->getCursorPos() - tabsMovement.cursorInTabSpacePosition;
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
