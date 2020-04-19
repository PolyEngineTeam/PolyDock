#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeHoverSystem.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>();

	if (const auto* inputComponent = registry.try_get<Input>(root))
	{
		for (auto entity : view)
		{
			const auto& cmp = view.get<Component>(entity);

			const Vector2i pos = inputComponent->getCursorPos();

			const Vector2i outerPos = cmp.position;
			const Vector2i outerSize = cmp.size;
			const Vector2i innerPos = cmp.position + Vector2i{ 7, 7 };
			const Vector2i innerSize = cmp.size - Vector2i{ 14, 14 };

			const AlignedBox2i inner = { innerPos, innerPos + innerSize };
			const AlignedBox2i outer = { outerPos, outerPos + outerSize };

			if (outer.contains(pos) && !inner.contains(pos))
			{
				using eVertical = ResizeHover::eVertical;
				using eHorizontal = ResizeHover::eHorizontal;

				const eVertical vertical = pos.y() < (inner.min().y() + 5) ? eVertical::TOP
					: (pos.y() > (inner.max().y() - 5) ? eVertical::BOTTOM : eVertical::MIDDLE);
				const eHorizontal horizontal = pos.x() < (inner.min().x() + 5) ? eHorizontal::LEFT
					: (pos.x() > (inner.max().x() - 5) ? eHorizontal::RIGHT : eHorizontal::MIDDLE);

				auto& activeCmp = registry.get_or_assign<ResizeHover>(entity);

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
			else if (registry.has<ResizeHover>(entity))
			{
				registry.remove<ResizeHover>(entity);
				auto* cursor = new QCursor(Qt::ArrowCursor);
				qApp->setOverrideCursor(*cursor);
			}

		}
	}
}