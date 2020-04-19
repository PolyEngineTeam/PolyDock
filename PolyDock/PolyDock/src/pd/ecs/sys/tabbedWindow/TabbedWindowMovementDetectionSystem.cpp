#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabbedWindow::MovementActive,
		::tabbedWindow::Component,
		tabbedWindowControl::Component>();

	if (auto* inputComponent = registry.try_get<root::Input>(root))
	{
		if (inputComponent->getCursorDiff() != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				const auto& window = view.get<tabbedWindow::Component>(entity);
				const auto controlCmp = view.get<tabbedWindowControl::Component>(entity);

				if (controlCmp.maximized)
				{
					registry.get_or_assign<tabbedWindow::RestoreRequest>(entity);
					registry.get_or_assign<tabbedWindow::MovementRequest>(
						entity, inputComponent->getCursorPos() - Vector2i{window.size.x() / 2, 20} );
				}
				else
				{
					registry.get_or_assign<tabbedWindow::MovementRequest>(
						entity, window.position + inputComponent->getCursorDiff());
				}
			}
		}
	}
}

} // namespace pd::ecs::sys
