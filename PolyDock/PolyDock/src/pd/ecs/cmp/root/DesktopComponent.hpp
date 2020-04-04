#pragma once

#include <Eigen/Dense>
#include <vector>

namespace pd::ecs::cmp::root
{
	// ---------------------------------------------------------------------------------------------------------
	class DesktopComponent
	{
	public:
		Eigen::AlignedBox2i desktopSize;
		std::vector<Eigen::AlignedBox2i> screens;


	};
}