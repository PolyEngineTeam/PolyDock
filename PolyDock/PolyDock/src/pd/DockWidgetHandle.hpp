#pragma once

#include <memory>
#include <entt/entt.hpp>

class QWidget;

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class DockableTabbedWindow
	{
	public:

	};

	// ---------------------------------------------------------------------------------------------------------
	class DockWidgetHandle
	{
	public:
		enum class eDockArea
		{
			CENTER,
			TOP,
			LEFT,
			RIGHT,
			BOTTOM
		};

		DockWidgetHandle(entt::registry& registry, entt::entity dockEntity);

		QWidget* getWidget();

		std::weak_ptr<DockableTabbedWindow> addDockableTabbedWindow();
		//std::weak_ptr<DockableTabbedWindow> addDockableTabbedWindow(eDockArea globalArea);
		//std::weak_ptr<DockableTabbedWindow> addDockableTabbedWindow(
		//	std::weak_ptr<DockableTabbedWindow> relativeWindow, eDockArea area);
		//
		//void moveDockableTabbedWindow(std::weak_ptr<DockableTabbedWindow> movedWindow, eDockArea globalArea);
		//void moveDockableTabbedWindow(std::weak_ptr<DockableTabbedWindow> movedwindow, 
		//	std::weak_ptr<DockableTabbedWindow> relativeWindow, eDockArea area);
		//
		//void removeDockableTabbedWindow(std::weak_ptr<DockableTabbedWindow> windowToRemove);

	private:
		entt::registry& m_registry;
		const entt::entity m_entity;
	};
}