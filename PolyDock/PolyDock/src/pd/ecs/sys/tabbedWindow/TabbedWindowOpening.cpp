#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowOpening.hpp>

#include <pd/ecs/cmp/tabbedWindow/Opening.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::CreateRequest>();

	for (auto entity : view)
	{
		const auto& request = view.get<tabbedWindow::CreateRequest>(entity);

		auto& windowComponent = registry.assign<tabbedWindow::Component>(entity, request.position, request.size);
		if (request.layerUuid.has_value())
			windowComponent.layerUuid = request.layerUuid.value();
		else
			windowComponent.layerUuid = QUuid::createUuid();

		registry.assign<tabsHeader::Component>(entity, request.tabs);
		registry.assign<tabbedWindowControl::Component>(entity);
		registry.assign<tabsHeader::SelectedTabs>(entity, request.selectedTabs);
		if (request.activeTab.has_value())
			registry.assign<tabsHeader::ActiveTab>(entity, request.activeTab.value());

		if (request.windowMovementState == tabbedWindow::CreateRequest::eWindowMovementState::ACTIVE)
			registry.assign<tabbedWindow::MovementActive>(entity, request.cursorInTabSpacePosition);

		registry.remove<tabbedWindow::CreateRequest>(entity);
	}
}

} // namespace pd::ecs::sys
