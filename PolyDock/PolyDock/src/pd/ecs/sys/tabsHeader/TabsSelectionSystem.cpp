#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsSelectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsSelectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<HoveredTab>();

	if (auto* inputComponent = registry.try_get<Input>(root))
	{
		if (inputComponent->wasJustPressed(Input::eMouseButton::LEFT))
		{
			for (auto entity : view)
			{
				registry.get_or_assign<SelectedTabs>(entity).selectedTabs =
				{ view.get<HoveredTab>(entity).hoveredTab };
					registry.get_or_assign<WidgetUpdateRequest>(entity);
			}
		}
	}
}