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

		int getScreenForPosition(const Eigen::Vector2i& pos)
		{
			int i = 0;
			for (const Eigen::AlignedBox2i& screen : screens)
			{
				if (screen.contains(pos))
					return i;

				++i;
			}

			return -1;
		}
	};
}