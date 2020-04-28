#pragma once

#include <Eigen/Dense>
#include <vector>

namespace pd::ecs::cmp::root
{
	// ---------------------------------------------------------------------------------------------------------
	class Desktop
	{
	public:
		Eigen::AlignedBox2i desktopSize;
		std::vector<Eigen::AlignedBox2i> screens;

		int getScreenForPosition(const Eigen::Vector2i& pos) const
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