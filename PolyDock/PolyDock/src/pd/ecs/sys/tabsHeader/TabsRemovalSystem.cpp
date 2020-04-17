#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsRemovalSystem.hpp>

// in
#include <pd/ecs/cmp/tabsHeader/TabsRemovalRequest.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>

// out
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;

void TabsRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
    auto view = registry.view<TabsHeaderComponent,
                              TabsRemovalRequest>();
    
    for (auto entity : view)
    {
        auto& tabsHeader = registry.get<TabsHeaderComponent>(entity);
        auto& requestCmp = registry.get<TabsRemovalRequest>(entity);
        auto& activeCmp = registry.get<ActiveTabComponent>(entity);

        // for now disallow destroying the only tab
        if (tabsHeader.tabs().size() > 1)
        {
            auto activeIt = std::find(tabsHeader.tabs().begin(), tabsHeader.tabs().end(), activeCmp.activeTab);
            auto activeIdx = std::distance(tabsHeader.tabs().begin(), activeIt);

            if (activeCmp.activeTab == requestCmp.tabToRemove)
            {
                //activate previous one if exists
                if (activeIdx == 0)
                    activeCmp.activeTab = tabsHeader.tabs().at(activeIdx + 1);
                else
                    activeCmp.activeTab = tabsHeader.tabs().at(activeIdx - 1);
            }

            tabsHeader.closeTab(requestCmp.tabToRemove);
            registry.destroy(requestCmp.tabToRemove);

            registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
            registry.get_or_assign<SelectedTabsComponent>(entity).selectedTabs = { activeCmp.activeTab };
        }
        registry.remove<TabsRemovalRequest>(entity);
    }
}