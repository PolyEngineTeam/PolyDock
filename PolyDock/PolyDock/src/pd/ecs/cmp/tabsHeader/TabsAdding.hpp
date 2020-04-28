#pragma once

#include <optional>
#include <vector>
#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class AddButtonHovered
	{
	};

	// ---------------------------------------------------------------------------------------------------------
	class AddButtonPressed
	{
	};

	// ---------------------------------------------------------------------------------------------------------
	class AddTabRequest
	{
	public:
		class Request
		{
		public:
			bool focus;
			std::optional<int> index;
			std::optional<entt::entity> newTabEntity;
		};

		std::vector<Request> requests;
	};
}