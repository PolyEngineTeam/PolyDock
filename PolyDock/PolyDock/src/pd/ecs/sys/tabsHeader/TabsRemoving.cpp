#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsRemoving.hpp>

#include <pd/ecs/cmp/tabsHeader/TabsRemoving.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabsRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
    auto view = registry.view<tabsHeader::Component, tabsHeader::TabsRemovalRequest>();
    
    for (auto entity : view)
    {
        auto& tabsHeader = registry.get<tabsHeader::Component>(entity);
        auto& requestCmp = registry.get<tabsHeader::TabsRemovalRequest>(entity);
        auto& activeCmp = registry.get<tabsHeader::ActiveTab>(entity);

        // for now disallow destroying the only tab
        if (tabsHeader.tabs().size() > 1)
        {
			for (const entt::entity& toRemove : requestCmp.tabsToRemove)
			{
				auto activeIt = std::find(tabsHeader.tabs().begin(), tabsHeader.tabs().end(), activeCmp.activeTab);
				auto activeIdx = std::distance(tabsHeader.tabs().begin(), activeIt);

				if (activeCmp.activeTab == toRemove)
				{
					//activate previous one if exists
					if (activeIdx == 0)
						activeCmp.activeTab = tabsHeader.tabs().at(activeIdx + 1);
					else
						activeCmp.activeTab = tabsHeader.tabs().at(activeIdx - 1);
				}

				tabsHeader.closeTab(toRemove);
				registry.destroy(toRemove);

				registry.get_or_assign<tabsHeader::SelectedTabs>(entity).selectedTabs = { activeCmp.activeTab };
			}

			registry.remove_if_exists<tabsHeader::HoveredTab>(entity);
			registry.get_or_assign<tabsHeader::WidgetUpdateRequest>(entity);
        }

        registry.remove<tabsHeader::TabsRemovalRequest>(entity);
    }
}

} // namespace pd::ecs::sys