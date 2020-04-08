#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsCreationSystem.hpp>

// in
//#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAddRequest.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
#include <pd/TabsHeaderHandle.hpp>
// out
#include <pd/WindowTabHandle.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;
using namespace ::pd::ecs::cmp::tab;

// ---------------------------------------------------------------------------------------------------------
void TabsCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderWidgetComponent,
                              TabsAddRequest>();

    for (auto entity : view)
    {
        auto& requestCmp = registry.get<TabsAddRequest>(entity);
        auto& newTabEntity = requestCmp.owner;

        registry.get_or_assign<TabComponent>(newTabEntity);
        registry.get_or_assign<DirtyTabComponent>(newTabEntity);
        registry.get_or_assign<DirtyTabContentComponent>(newTabEntity);

        auto& tabsHeader = registry.get<TabsHeaderComponent>(entity);
        tabsHeader.appendTab(std::move(newTabEntity));
        registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
        registry.get_or_assign<ActiveTabComponent>(entity).activeTab = newTabEntity;
        registry.get_or_assign<SelectedTabsComponent>(entity).selectedTabs = { newTabEntity };

        registry.remove<TabsAddRequest>(entity);
    }
}