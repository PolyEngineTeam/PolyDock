#include <pd/pch/PCH.h>
#include <pd/ecs/sys/dock/DockWidgetRemovalSystem.hpp>

#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/dock/DockComponent.hpp>
#include <pd/ecs/cmp/dock/DockWidgetComponent.hpp>

using namespace ::pd::ecs::sys::dock;
using namespace ::pd::ecs::cmp::dock;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void DockWidgetRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<DockComponent>(entt::exclude<DockWidgetComponent>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwner>(root))
	{
		for (auto entity : view)
		{
			delete widgetsOwner->docks.at(entity);
			widgetsOwner->docks.erase(entity);
			registry.destroy(entity);
		}
	}
}