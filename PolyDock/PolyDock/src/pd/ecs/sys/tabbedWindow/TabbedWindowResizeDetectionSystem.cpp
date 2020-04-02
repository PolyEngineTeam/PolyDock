#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementSystem.hpp>

// in
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowMovementRequestComponent,
		TabbedWindowComponent>();

	for (auto entity : view)
	{
		auto& request = view.get<TabbedWindowMovementRequestComponent>(entity);
		auto& window = view.get<TabbedWindowComponent>(entity);

		window.position = request.newWindowPos;
		registry.remove<TabbedWindowMovementRequestComponent>(entity);
		registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
	}
}