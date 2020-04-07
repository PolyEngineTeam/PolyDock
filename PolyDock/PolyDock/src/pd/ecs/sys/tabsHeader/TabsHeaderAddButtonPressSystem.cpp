#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderAddButtonPressSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsAddRequest.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredAddButton.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderAddButtonPressSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderWidgetComponent, 
                              HoveredAddButton>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
        for (auto entity : view)
        {
            const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

            if (inputComponent->wasJustReleased(InputComponent::eMouseButton::LEFT) 
                && widget.hoversAddButton(inputComponent->getCursorPos()))
            {
                registry.get_or_assign<TabsAddRequest>(entity);
                registry.remove<HoveredAddButton>(entity);
            }
        }
	}
}
