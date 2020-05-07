#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovement.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/root/Desktop.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->wasJustPressed(root::Input::eMouse::LEFT))
	{
		auto view = registry.view<
			tabsHeader::Widget,
			tabsHeader::Component,
			tabsHeader::SelectedTabs>();

		// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
		for (auto entity : view)
		{
			const auto& widget = view.get<tabsHeader::Widget>(entity);
			const auto& header = view.get<tabsHeader::Component>(entity);
			const auto& selected = view.get<tabsHeader::SelectedTabs>(entity);

			if (widget.getWidgetRect().contains(inputCmp->getCursorPos()))
			{
				if (!registry.has<tabsHeader::HoveredTab>(entity)
					|| selected.selectedTabs.size() == header.tabs().size())
				{
					auto& newCmp = registry.assign<tabbedWindow::MovementActive>(entity);

					if (selected.selectedTabs.size() == header.tabs().size())
					{
						newCmp.cursorInTabSpacePosition =
							widget.getCursorPosInTabSpace(inputCmp->getCursorPos());
					}
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	const auto* inputCmp = registry.try_get<root::Input>(root);
	const auto* desktopCmp = registry.try_get<root::Desktop>(root);

	if (inputCmp && desktopCmp && inputCmp->wasJustReleased(root::Input::eMouse::LEFT))
	{
		auto view = registry.view<tabbedWindow::MovementActive, tabbedWindowControl::Component>();

		const Vector2i mousePos = inputCmp->getCursorPos();

		for (auto entity : view)
		{
			const int screenIdx = desktopCmp->getScreenForPosition(mousePos);
			const AlignedBox2i& screen = desktopCmp->screens[screenIdx];
			const AlignedBox2i inner =
				AlignedBox2i{ screen.min() + Vector2i{ 20, 20 }, screen.max() - Vector2i{ 20, 20 } };

			if (screen.contains(mousePos) && !inner.contains(mousePos))
			{
				using ePosition = tabbedWindow::SnapRequest::ePosition;
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
					auto& request = registry.get_or_assign<tabbedWindow::SnapRequest>(entity);
					request.screenIndex = screenIdx;
					request.position = position;
				}
			}

			auto& controlCmp = view.get<tabbedWindowControl::Component>(entity);
			controlCmp.maximized = false;

			registry.remove<tabbedWindow::MovementActive>(entity);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	if (auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->getCursorDiff() != Vector2i{ 0, 0 })
	{
		auto view = registry.view<
			tabbedWindow::MovementActive,
			tabbedWindow::Component,
			tabbedWindowControl::Component>();

		for (auto entity : view)
		{
			const auto& window = view.get<tabbedWindow::Component>(entity);
			const auto controlCmp = view.get<tabbedWindowControl::Component>(entity);

			if (controlCmp.maximized)
			{
				registry.get_or_assign<tabbedWindow::RestoreRequest>(entity);
				registry.get_or_assign<tabbedWindow::MovementRequest>(
					entity, inputCmp->getCursorPos() - Vector2i{ window.size.x() / 2, 20 });
			}
			else
			{
				registry.get_or_assign<tabbedWindow::MovementRequest>(
					entity, window.position + inputCmp->getCursorDiff());
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::MovementRequest, tabbedWindow::Component>();

	for (auto entity : view)
	{
		const auto& request = view.get<tabbedWindow::MovementRequest>(entity);
		auto& window = view.get<tabbedWindow::Component>(entity);

		window.position = request.newWindowPos;

		registry.remove<tabbedWindow::MovementRequest>(entity);
		registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
	}
}

} // namespace ::pd::ecs::sys