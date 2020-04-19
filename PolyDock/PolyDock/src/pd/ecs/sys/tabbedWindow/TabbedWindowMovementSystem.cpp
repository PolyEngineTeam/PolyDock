#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementSystem.hpp>

// in
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		MovementRequest,
		Component>();

	for (auto entity : view)
	{
		auto& request = view.get<MovementRequest>(entity);
		auto& window = view.get<Component>(entity);

		window.position = request.newWindowPos;

		registry.remove<MovementRequest>(entity);
		registry.get_or_assign<RequestWidgetUpdate>(entity);
	}
}