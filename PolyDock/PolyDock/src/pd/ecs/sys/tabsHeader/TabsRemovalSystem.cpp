#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsRemovalSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsRemovalRequest.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>

// out

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

void TabsRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
    auto view = registry.view<TabsHeaderWidgetComponent,
                              TabsRemovalRequest>();
    
    for (auto entity : view)
    {
        auto& requestCmp = registry.get<TabsRemovalRequest>(entity);
        auto& tabsHeader = registry.get<TabsHeaderComponent>(entity);

        tabsHeader.tabsMut().erase(tabsHeader.tabs().begin() + requestCmp.tabIdx);
        registry.remove(entity);
    }
}