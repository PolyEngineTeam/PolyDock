#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsSelectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsSelectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<HoveredTabComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustPressed(InputComponent::eMouseButton::LEFT))
		{
			for (auto entity : view)
			{
				registry.get_or_assign<SelectedTabsComponent>(entity).selectedTabs =
				{ view.get<HoveredTabComponent>(entity).hoveredTab };
					registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
			}
		}
	}
}