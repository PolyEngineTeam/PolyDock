#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementEndSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowMovementActiveComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustReleased(cmp::root::InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : view)
				registry.remove<TabbedWindowMovementActiveComponent>(entity);
		}
	}
}