#include <pd/pch/PCH.h>
#include <pd/TabsHeaderHandle.hpp>

#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>

using namespace ::pd;

// ---------------------------------------------------------------------------------------------------------
WindowTabHandle TabsHeaderHandle::addTab()
{
	Expects(valid());

	auto entity = m_registry.create();
	auto tab = WindowTabHandle(m_registry, entity);
	m_registry.assign<ecs::cmp::tab::TabComponent>(entity);
	m_registry.assign<ecs::cmp::tab::DirtyTabComponent>(entity);
	m_registry.assign<ecs::cmp::tab::DirtyTabContentComponent>(entity);

	auto& tabsHeader = m_registry.get<ecs::cmp::tabsHeader::TabsHeaderComponent>(m_entity);
	tabsHeader.tabs.push_back(entity);
	m_registry.get_or_assign<ecs::cmp::tabsHeader::DirtyTabsHeaderComponent>(m_entity);

	return tab;
}
