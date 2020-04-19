#pragma once

#include <map>
#include <entt/entt.hpp>
#include <Eigen/Dense>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class DockComponent final
	{
	public:
		std::vector<entt::entity> docks;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class UpdateDockWidgetRequestComponent final
	{
	public:
	};
}