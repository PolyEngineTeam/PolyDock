#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeDetectionSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeActiveComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>

#include <iostream>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent, 
		TabbedWindowResizeActiveComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		const Vector2i diff = inputComponent->getCursorDiff();
		if (diff != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				using eVertical = TabbedWindowResizeHoverComponent::eVertical;
				using eHorizontal = TabbedWindowResizeHoverComponent::eHorizontal;

				const auto& windowCmp = registry.get_or_assign<TabbedWindowComponent>(entity);
				const auto& activeCmp = registry.get_or_assign<TabbedWindowResizeActiveComponent>(entity);
				auto& resizeRequestCmp = registry.get_or_assign<TabbedWindowResizeRequestComponent>(entity);
				auto& movementRequestCmp = registry.get_or_assign<TabbedWindowMovementRequestComponent>(entity);

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

				std::cout << resizeRequestCmp.newWindowSize << std::endl;
			}
		}
	}
}