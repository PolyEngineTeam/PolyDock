#pragma once

#include <memory>
#include <vector>
#include <entt/entt.hpp>
#include <qtimer.h>

#include <pd/TabbedWindowHandle.hpp>
#include <pd/DockWidgetHandle.hpp>

namespace pd::ecs::sys { class SystemBase; }

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class PolyDockRegistry final : private QObject
	{
	public:
		PolyDockRegistry();
		~PolyDockRegistry();

		TabbedWindowHandle createWindow();
		DockWidgetHandle createDockWidget();

	private:
		void update();
		void lateUpdate();

		entt::registry m_registry;
		entt::entity m_root;
		std::vector<std::unique_ptr<ecs::sys::SystemBase>> m_systems;

		QTimer m_timer;
	};
}