#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementEndSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsMovementActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsMovementActiveComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustReleased(cmp::root::InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : view)
				registry.remove<TabsMovementActiveComponent>(entity);
		}
	}
}