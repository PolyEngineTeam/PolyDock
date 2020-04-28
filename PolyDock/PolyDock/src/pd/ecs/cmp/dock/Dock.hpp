#pragma once

#include <map>
#include <entt/entt.hpp>
#include <Eigen/Dense>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class Component final
	{
	public:
		std::vector<entt::entity> docks;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class WidgetUpdateRequest final
	{
	public:
	};
}