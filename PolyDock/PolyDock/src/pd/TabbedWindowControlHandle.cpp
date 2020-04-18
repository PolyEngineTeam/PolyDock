#include <pd/pch/PCH.h>
#include <pd/TabbedWindowControlHandle.hpp>

#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd;
using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHandle::registerObserver(Observer* observer)
{
	m_registry.get_or_assign<Observers>(m_entity).observers.push_back(observer);
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHandle::unregisterObserver(Observer* observer)
{
	std::vector<TabbedWindowControlHandle::Observer*>& observers = 
		m_registry.get_or_assign<Observers>(m_entity).observers;
		
	observers.erase(std::remove(observers.begin(), observers.end(), observer));
}

// ---------------------------------------------------------------------------------------------------------
bool TabbedWindowControlHandle::canClose()
{
	std::vector<TabbedWindowControlHandle::Observer*>& observers =
		m_registry.get_or_assign<Observers>(m_entity).observers;

	for (Observer* obs : observers)
	{
		if (!obs->canClose())
			return false;
	}

	return true;
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHandle::tryClose()
{
	m_registry.get_or_assign<CloseRequest>(m_entity);
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHandle::forceClose()
{
	m_registry.get_or_assign<CloseRequest>(m_entity, true);
}
