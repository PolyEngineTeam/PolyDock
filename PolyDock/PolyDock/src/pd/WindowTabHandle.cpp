#include <pd/pch/PCH.h>
#include <pd/WindowTabHandle.hpp>

#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd;

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setName(std::string name)
{
	assert(valid());

	m_registry.get_or_assign<ecs::cmp::tab::Component>(m_entity).name = std::move(name);
	m_registry.get_or_assign<ecs::cmp::tab::RefreshTab>(m_entity);
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setIcon(std::optional<QIcon> newIcon)
{
	assert(valid());
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::setTabContent(QWidget* widget)
{
	assert(valid());
	if (widget)
		m_registry.get_or_assign<ecs::cmp::tab::Content>(m_entity).contentWidget = widget;
	else
		m_registry.remove_if_exists<ecs::cmp::tab::Content>(m_entity);

	m_registry.get_or_assign<ecs::cmp::tab::RefreshTabContent>(m_entity);
}

// ---------------------------------------------------------------------------------------------------------
void WindowTabHandle::close()
{
	assert(valid());
}