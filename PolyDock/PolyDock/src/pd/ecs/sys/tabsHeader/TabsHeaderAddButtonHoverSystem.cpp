#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsHeaderAddButtonHoverSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/HoveredAddButton.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsHeaderAddButtonHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderWidgetComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
        for (auto entity : view)
        {
            const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);

            if (widget.hoversAddButton(inputComponent->getCursorPos()))
            {
                registry.get_or_assign<HoveredAddButton>(entity);
            }
        }
	}
}
