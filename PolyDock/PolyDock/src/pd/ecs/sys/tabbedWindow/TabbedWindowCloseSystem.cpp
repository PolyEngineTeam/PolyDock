#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCloseSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCloseRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRemoveRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCloseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowComponent,
		TabbedWindowCloseRequestComponent>();

	for (auto entity : view)
	{
		registry.remove<TabbedWindowCloseRequestComponent>(entity);
		registry.get_or_assign<TabbedWindowRemoveRequestComponent>(entity);
	}
}