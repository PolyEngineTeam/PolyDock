#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsCreationSystem>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAddRequest.hpp>
// out
#include <WindowTabHandle.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp> // selected too?

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsActivationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderWidgetComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root)) // is this needed?
    {
        for (auto entity : view)
        {
            registry.remove<TabsAddRequest>(entity);

            auto newTabEntity = registry.create();
            auto tab = WindowTabHandle(registry, newTabEntity);
            registry.assign<TabComponent>(newTabEntity);
            registry.assign<DirtyTabComponent>(newTabEntity);
            registry.assign<DirtyTabContentComponent>(newTabEntity);

            auto& tabsHeader = registry.get<TabsHeaderComponent>(entity);
            tabsHeader.tabs.push_back(newTabEntity);
            registry.get_or_assign<DirtyTabsHeaderComponent>(entity);
            registry.get_or_assign<ActiveTabComponent>(entity).activeTab = tab;
            // clear out selected tabs?
        }
    }
}