#include <pd/pch/PCH.h>
#include <pd/TabsHeaderHandle.hpp>

#include <pd/ecs/cmp/tab/TabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabComponent.hpp>
#include <pd/ecs/cmp/tab/DirtyTabContentComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsAdding.hpp>

using namespace ::pd;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
WindowTabHandle TabsHeaderHandle::addTab()
{
	Expects(valid());

	auto tabEntity = m_registry.create();
	m_registry.get_or_assign<AddTabRequest>(m_entity).requests.push_back({ false, {}, tabEntity });

	return WindowTabHandle(m_registry, tabEntity);
}
