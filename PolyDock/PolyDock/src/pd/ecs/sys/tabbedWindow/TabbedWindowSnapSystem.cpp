#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowSnapSystem.hpp>

#include <pd/ecs/cmp/root/DesktopComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys::tabbedWindow
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowSnapSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<::tabbedWindow::Component, tabbedWindowControl::Component, ::tabbedWindow::SnapRequest>();

	if (const auto* desktopCmp = registry.try_get<root::DesktopComponent>(root))
	{
		for (auto entity : view)
		{
			using ePosition = ::tabbedWindow::SnapRequest::ePosition;

			const auto& windowCmp = view.get<::tabbedWindow::Component>(entity);
			const auto& controlCmp = view.get<tabbedWindowControl::Component>(entity);
			const auto& requestCmp = view.get<::tabbedWindow::SnapRequest>(entity);
			const AlignedBox2i& screen = desktopCmp->screens[requestCmp.screenIndex];
			const Vector2i screenSize = screen.sizes();

			auto& rezieRequestCmp = 
				registry.get_or_assign<::tabbedWindow::ResizeRequest>(entity, windowCmp.size);
			auto& moveRequestCmp = 
				registry.get_or_assign<::tabbedWindow::MovementRequest>(entity, windowCmp.position);

			switch (requestCmp.position)
			{
				case ePosition::TOP_LEFT:
				{
					moveRequestCmp.newWindowPos = screen.min();
					rezieRequestCmp.newWindowSize = screenSize / 2;
				}
				break;

				case ePosition::TOP_RIGHT:
				{
					moveRequestCmp.newWindowPos = screen.min() + Vector2i{ screenSize.x() / 2, 0 };
					rezieRequestCmp.newWindowSize = screenSize / 2;
				}
				break;

				case ePosition::BOTTOM_LEFT:
				{
					moveRequestCmp.newWindowPos = screen.min() + Vector2i{ 0, screenSize.y() / 2 };
					rezieRequestCmp.newWindowSize = screenSize / 2;
				}
				break;

				case ePosition::BOTTOM_RIGHT:
				{
					moveRequestCmp.newWindowPos = screen.min() + screenSize / 2;
					rezieRequestCmp.newWindowSize = screenSize / 2;
				}
				break;

				case ePosition::LEFT:
				{
					moveRequestCmp.newWindowPos = screen.min();
					rezieRequestCmp.newWindowSize = Vector2i{ screenSize.x() / 2, screenSize.y() };
				}
				break;

				case ePosition::RIGHT:
				{
					moveRequestCmp.newWindowPos = screen.min() + Vector2i{ screenSize.x() / 2, 0 };
					rezieRequestCmp.newWindowSize = Vector2i{ screenSize.x() / 2, screenSize.y() };
				}
				break;

				case ePosition::MAXIMIZE:
				{
					registry.get_or_assign<::tabbedWindow::MaximizeRequest>(entity);
				}
				break;

				case ePosition::RESTORE:
				{
					registry.get_or_assign<::tabbedWindow::RestoreRequest>(entity);
				}
				break;

				case ePosition::MINIMIZE:
				{
					registry.get_or_assign<::tabbedWindow::MinimizeRequest>(entity);
				}
				break;

				default:
				{
					assert(false);
				}
				break;
			}

			if (requestCmp.position == ePosition::MAXIMIZE
				|| requestCmp.position == ePosition::RESTORE
				|| requestCmp.position == ePosition::MINIMIZE)
			{
				registry.remove<::tabbedWindow::ResizeRequest>(entity);
				registry.remove<::tabbedWindow::MovementRequest>(entity);
			}
			else if (controlCmp.maximized)
				registry.get_or_assign<::tabbedWindow::RestoreRequest>(entity);

			registry.remove<::tabbedWindow::SnapRequest>(entity);
		}
	}
}

} // namespace pd::ecs::sys::tabbedWindow