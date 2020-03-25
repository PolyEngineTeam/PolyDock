#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowMovementActiveComponent, TabbedWindowComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->getCursorDiff() != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				auto& window = view.get<TabbedWindowComponent>(entity);

				registry.assign<TabbedWindowMovementRequestComponent>(
					entity, window.position + inputComponent->getCursorDiff());
			}
		}
	}
}