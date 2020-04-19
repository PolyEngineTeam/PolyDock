#pragma once

#include <entt/entt.hpp>
#include <pd/DockWidgetHandle.hpp>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class DockRequest final
	{
	public:
		entt::entity dock;
		DockWidgetHandle::eDockArea dockArea = DockWidgetHandle::eDockArea::CENTER;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class UndockRequest final
	{
	public:
		entt::entity dock;
	};
}