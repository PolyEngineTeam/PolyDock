#pragma once

#include <entt/entt.hpp>
#include <pd/DockWidgetHandle.hpp>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class DockRequestComponent final
	{
	public:
		entt::entity dock;
		DockWidgetHandle::eDockArea dockArea = DockWidgetHandle::eDockArea::CENTER;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class UndockRequestComponent final
	{
	public:
		entt::entity dock;
	};
}