#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsActivationSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsActivationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<HoveredTabComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustPressed(cmp::root::InputComponent::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				auto& hovered = view.get<HoveredTabComponent>(entity);

				registry.get_or_assign<ActiveTabComponent>(entity).activeTab = hovered.hoveredTab;
				registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
				registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
			}
		}
	}
}