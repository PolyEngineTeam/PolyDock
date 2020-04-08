#include <pd/pch/PCH.h>
#include <pd/TabsHeaderHandle.hpp>

#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAddRequest.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>


using namespace ::pd;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
WindowTabHandle TabsHeaderHandle::addTab()
{
	Expects(valid());

	auto& requestCmp = m_registry.get_or_assign<TabsAddRequest>(m_entity, m_registry.create());
	auto& tabEntity = requestCmp.owner;
	return WindowTabHandle(m_registry,tabEntity);
}
