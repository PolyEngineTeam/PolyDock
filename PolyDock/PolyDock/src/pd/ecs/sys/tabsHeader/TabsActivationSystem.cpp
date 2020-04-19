#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsActivationSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsActivationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabsHeader::HoveredTab>();

	if (auto* inputComponent = registry.try_get<root::Input>(root))
	{
		if (inputComponent->wasJustPressed(cmp::root::Input::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				auto& hovered = view.get<tabsHeader::HoveredTab>(entity);

				registry.get_or_assign<tabsHeader::ActiveTab>(entity).activeTab = hovered.hoveredTab;
				registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
				registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
			}
		}
	}
}

} // namespace pd::ecs::sys
