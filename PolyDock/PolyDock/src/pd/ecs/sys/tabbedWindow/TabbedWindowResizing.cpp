#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizing.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabbedWindow::Component>();

		for (auto entity : view)
		{
			const auto& cmp = view.get<tabbedWindow::Component>(entity);

			const Vector2i pos = inputComponent->getCursorPos();

			const Vector2i outerPos = cmp.position;
			const Vector2i outerSize = cmp.size;
			const Vector2i innerPos = cmp.position + Vector2i{ 7, 7 };
			const Vector2i innerSize = cmp.size - Vector2i{ 14, 14 };

			const AlignedBox2i inner = { innerPos, innerPos + innerSize };
			const AlignedBox2i outer = { outerPos, outerPos + outerSize };

			if (outer.contains(pos) && !inner.contains(pos))
			{
				using eVertical = tabbedWindow::ResizeHover::eVertical;
				using eHorizontal = tabbedWindow::ResizeHover::eHorizontal;

				const eVertical vertical = pos.y() < (inner.min().y() + 5) ? eVertical::TOP
					: (pos.y() > (inner.max().y() - 5) ? eVertical::BOTTOM : eVertical::MIDDLE);
				const eHorizontal horizontal = pos.x() < (inner.min().x() + 5) ? eHorizontal::LEFT
					: (pos.x() > (inner.max().x() - 5) ? eHorizontal::RIGHT : eHorizontal::MIDDLE);

				auto& activeCmp = registry.get_or_assign<tabbedWindow::ResizeHover>(entity);

				if (activeCmp.vertical != vertical || activeCmp.horizontal != horizontal)
				{
					activeCmp.vertical = vertical;
					activeCmp.horizontal = horizontal;

					if ((vertical == eVertical::TOP && horizontal == eHorizontal::LEFT)
						|| (vertical == eVertical::BOTTOM && horizontal == eHorizontal::RIGHT))
					{
						auto* cursor = new QCursor(Qt::SizeFDiagCursor);
						qApp->setOverrideCursor(*cursor);
					}
					else if ((vertical == eVertical::TOP && horizontal == eHorizontal::RIGHT)
						|| (vertical == eVertical::BOTTOM && horizontal == eHorizontal::LEFT))
					{
						auto* cursor = new QCursor(Qt::SizeBDiagCursor);
						qApp->setOverrideCursor(*cursor);
					}
					else if ((vertical == eVertical::TOP && horizontal == eHorizontal::MIDDLE)
						|| (vertical == eVertical::BOTTOM && horizontal == eHorizontal::MIDDLE))
					{
						auto* cursor = new QCursor(Qt::SizeVerCursor);
						qApp->setOverrideCursor(*cursor);
					}
					else if ((vertical == eVertical::MIDDLE && horizontal == eHorizontal::RIGHT)
						|| (vertical == eVertical::MIDDLE && horizontal == eHorizontal::LEFT))
					{
						auto* cursor = new QCursor(Qt::SizeHorCursor);
						qApp->setOverrideCursor(*cursor);
					}
					else
						assert(false);
				}
			}
			else if (registry.has<tabbedWindow::ResizeHover>(entity))
			{
				registry.remove<tabbedWindow::ResizeHover>(entity);
				auto* cursor = new QCursor(Qt::ArrowCursor);
				qApp->setOverrideCursor(*cursor);
			}

		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeStartSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->wasJustPressed(root::Input::eMouseButton::LEFT))
	{
		auto view = registry.view<tabbedWindow::ResizeHover>();

		for (auto entity : view)
		{
			const auto& hoverCmp = view.get<tabbedWindow::ResizeHover>(entity);
			auto& activeCmp = registry.get_or_assign<tabbedWindow::ResizeActive>(entity);
			activeCmp.horizontal = hoverCmp.horizontal;
			activeCmp.vertical = hoverCmp.vertical;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeEndSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputCmp = registry.try_get<root::Input>(root); inputCmp
		&& inputCmp->wasJustReleased(root::Input::eMouseButton::LEFT))
	{
		auto view = registry.view<tabbedWindow::ResizeActive>();

		for (auto entity : view)
			registry.remove<tabbedWindow::ResizeActive>(entity);
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		auto view = registry.view<tabbedWindow::Component, tabbedWindow::ResizeActive>();

		const Vector2i diff = inputComponent->getCursorDiff();
		if (diff != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				using eVertical = tabbedWindow::ResizeHover::eVertical;
				using eHorizontal = tabbedWindow::ResizeHover::eHorizontal;

				const auto& windowCmp = registry.get_or_assign<tabbedWindow::Component>(entity);
				const auto& activeCmp = registry.get_or_assign<tabbedWindow::ResizeActive>(entity);
				auto& resizeRequestCmp = registry.get_or_assign<tabbedWindow::ResizeRequest>(entity);
				auto& movementRequestCmp = registry.get_or_assign<tabbedWindow::MovementRequest>(entity);

				resizeRequestCmp.newWindowSize = windowCmp.size;
				movementRequestCmp.newWindowPos = windowCmp.position;

				if (activeCmp.vertical == eVertical::BOTTOM)
					resizeRequestCmp.newWindowSize.y() = windowCmp.size.y() + diff.y();
				else if (activeCmp.vertical == eVertical::TOP)
				{
					movementRequestCmp.newWindowPos.y() = windowCmp.position.y() + diff.y();
					resizeRequestCmp.newWindowSize.y() = windowCmp.size.y() - diff.y();
				}

				if (activeCmp.horizontal == eHorizontal::RIGHT)
					resizeRequestCmp.newWindowSize.x() = windowCmp.size.x() + diff.x();
				else if (activeCmp.horizontal == eHorizontal::LEFT)
				{
					movementRequestCmp.newWindowPos.x() = windowCmp.position.x() + diff.x();
					resizeRequestCmp.newWindowSize.x() = windowCmp.size.x() - diff.x();
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindow::ResizeRequest, tabbedWindow::Component>();

	for (auto entity : view)
	{
		const auto& request = view.get<tabbedWindow::ResizeRequest>(entity);
		auto& window = view.get<tabbedWindow::Component>(entity);

		window.size = request.newWindowSize;

		registry.remove<tabbedWindow::ResizeRequest>(entity);
		registry.get_or_assign<tabbedWindow::RequestWidgetUpdate>(entity);
	}
}

} // namespace ::pd::ecs::sys