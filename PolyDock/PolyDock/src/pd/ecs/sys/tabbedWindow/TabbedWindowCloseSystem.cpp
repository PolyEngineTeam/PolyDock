#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCloseSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCloseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		Component,
		CloseRequest>();

	for (auto entity : view)
	{
		registry.remove<CloseRequest>(entity);
		registry.get_or_assign<RemoveRequest>(entity);
	}
}