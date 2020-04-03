#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowResizeRequestComponent,
		TabbedWindowComponent>();

	for (auto entity : view)
	{
		const auto& request = view.get<TabbedWindowResizeRequestComponent>(entity);
		auto& window = view.get<TabbedWindowComponent>(entity);

		window.size = request.newWindowSize;

		registry.remove<TabbedWindowResizeRequestComponent>(entity);
		registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
	}
}