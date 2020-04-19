#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementEndSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementEndSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsMovementActive>();

	if (auto* inputComponent = registry.try_get<Input>(root))
	{
		if (inputComponent->wasJustReleased(cmp::root::Input::eMouseButton::LEFT))
		{
			for (auto entity : view)
				registry.remove<TabsMovementActive>(entity);
		}
	}
}