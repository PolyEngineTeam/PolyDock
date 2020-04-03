#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeEndSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowResizeActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeEndSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowResizeActiveComponent>();
	
	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustReleased(InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : view)
			{
				registry.remove<TabbedWindowResizeActiveComponent>(entity);
			}
		}
	}
}