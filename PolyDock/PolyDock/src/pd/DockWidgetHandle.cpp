#include <pd/pch/PCH.h>
#include <pd/DockWidgetHandle.hpp>

using namespace ::pd;

// ---------------------------------------------------------------------------------------------------------
DockWidgetHandle::DockWidgetHandle(entt::registry& registry, entt::entity tabEntity)
	: m_registry(registry), m_entity(std::move(tabEntity))
{
}

// ---------------------------------------------------------------------------------------------------------
QWidget* DockWidgetHandle::getWidget()
{
	return nullptr;
}

// ---------------------------------------------------------------------------------------------------------
std::weak_ptr<DockableTabbedWindow> DockWidgetHandle::addDockableTabbedWindow()
{
	return std::weak_ptr<DockableTabbedWindow>();
}
