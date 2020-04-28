#pragma once

#include <vector>
#include <entt/entt.hpp>
#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class CreateRequest
	{
	public:
		enum class eWindowMovementState
		{
			ACTIVE,
			INACTIVE
		};

		std::vector<entt::entity> tabs;
		std::vector<entt::entity> selectedTabs;
		std::optional<entt::entity> activeTab;
		Eigen::Vector2i position;
		Eigen::Vector2i size;
		eWindowMovementState windowMovementState = eWindowMovementState::INACTIVE;
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}