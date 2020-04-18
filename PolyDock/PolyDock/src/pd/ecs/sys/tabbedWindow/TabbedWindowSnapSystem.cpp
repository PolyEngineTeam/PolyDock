#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowSnapSystem.hpp>

#include <pd/ecs/cmp/root/DesktopComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowSnapRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMaximizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRestoreRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMinimizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowSnapSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowComponent, Component, TabbedWindowSnapRequestComponent>();

	if (const auto* desktopCmp = registry.try_get<DesktopComponent>(root))
	{
		for (auto entity : view)
		{
			using ePosition = TabbedWindowSnapRequestComponent::ePosition;

			const auto& windowCmp = view.get<TabbedWindowComponent>(entity);
			const auto& controlCmp = view.get<Component>(entity);
			const auto& requestCmp = view.get<TabbedWindowSnapRequestComponent>(entity);
			const AlignedBox2i& screen = desktopCmp->screens[requestCmp.screenIndex];
			const Vector2i screenSize = screen.sizes();

			auto& rezieRequestCmp = 
				registry.get_or_assign<TabbedWindowResizeRequestComponent>(entity, windowCmp.size);
			auto& moveRequestCmp = 
				registry.get_or_assign<TabbedWindowMovementRequestComponent>(entity, windowCmp.position);

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
					registry.get_or_assign<TabbedWindowMaximizeRequestComponent>(entity);
				}
				break;

				case ePosition::RESTORE:
				{
					registry.get_or_assign<TabbedWindowRestoreRequestComponent>(entity);
				}
				break;

				case ePosition::MINIMIZE:
				{
					registry.get_or_assign<TabbedWindowMinimizeRequestComponent>(entity);
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
				registry.remove<TabbedWindowResizeRequestComponent>(entity);
				registry.remove<TabbedWindowMovementRequestComponent>(entity);
			}
			else if (controlCmp.maximized)
				registry.get_or_assign<TabbedWindowRestoreRequestComponent>(entity);

			registry.remove<TabbedWindowSnapRequestComponent>(entity);
		}
	}
}