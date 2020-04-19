#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementEndSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/root/DesktopComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<MovementActive, Component>();

	const auto* inputCmp = registry.try_get<InputComponent>(root);
	const auto* desktopCmp = registry.try_get<DesktopComponent>(root);

	if (inputCmp && desktopCmp && inputCmp->wasJustReleased(InputComponent::eMouseButton::LEFT))
	{
		const Vector2i mousePos = inputCmp->getCursorPos();

		for (auto entity : view)
		{
			const int screenIdx = desktopCmp->getScreenForPosition(mousePos);
			const AlignedBox2i& screen = desktopCmp->screens[screenIdx];
			const AlignedBox2i inner =
				AlignedBox2i{ screen.min() + Vector2i{ 20, 20 }, screen.max() - Vector2i{ 20, 20 } };

			if (screen.contains(mousePos) && !inner.contains(mousePos))
			{
				using ePosition = SnapRequest::ePosition;
				ePosition position = ePosition::INVALID;

				// top
				if (mousePos.y() < inner.min().y())
				{
					// left
					if (mousePos.x() < inner.min().x())
						position = ePosition::TOP_LEFT;
					// right
					else if (mousePos.x() > inner.max().x())
						position = ePosition::TOP_RIGHT;
					// mid
					else
						position = ePosition::MAXIMIZE;

				}
				// bottom
				else if (mousePos.y() > inner.max().y())
				{
					// left
					if (mousePos.x() < inner.min().x())
						position = ePosition::BOTTOM_LEFT;
					// right
					else if (mousePos.x() > inner.max().x())
						position = ePosition::BOTTOM_RIGHT;
					// mid
					else
						position = ePosition::INVALID;
				}
				// mid
				else
				{
					// left
					if (mousePos.x() < inner.min().x())
						position = ePosition::LEFT;
					// right
					else if (mousePos.x() > inner.max().x())
						position = ePosition::RIGHT;
					// mid
					else
						position = ePosition::INVALID;
				}

				if (position != ePosition::INVALID)
				{
					auto& request = registry.get_or_assign<SnapRequest>(entity);
					request.screenIndex = screenIdx;
					request.position = position;
				}
			}

			auto& controlCmp = view.get<Component>(entity);
			controlCmp.maximized = false;

			registry.remove<MovementActive>(entity);
		}
	}
}