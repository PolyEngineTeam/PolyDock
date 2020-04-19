#include <pd/pch/PCH.h>
#include <pd/WindowTabHandle.hpp>

#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd;

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setName(std::string name)
{
	Expects(valid());

	m_registry.get_or_assign<ecs::cmp::tab::TabComponent>(m_entity).name = std::move(name);
	m_registry.get_or_assign<ecs::cmp::tab::DirtyTabComponent>(m_entity);
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setIcon(std::optional<QIcon> newIcon)
{
	Expects(valid());
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setTabContent(QWidget* widget)
{
	Expects(valid());
	if (widget)
		m_registry.get_or_assign<ecs::cmp::tab::TabContentComponent>(m_entity).contentWidget = widget;
	else
		m_registry.remove_if_exists<ecs::cmp::tab::TabContentComponent>(m_entity);

	m_registry.get_or_assign<ecs::cmp::tab::DirtyTabContentComponent>(m_entity);
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::close()
{
	Expects(valid());
}