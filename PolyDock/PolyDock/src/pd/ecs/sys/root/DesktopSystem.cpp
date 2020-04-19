#include <pd/pch/PCH.h>
#include <pd/ecs/sys/root/DesktopSystem.hpp>

#include <pd/ecs/cmp/root/Desktop.hpp>

using namespace ::pd::ecs::sys::root;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void DesktopSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Desktop>();
	Expects(view.size() == 1);

	for (auto entity : view)
	{
		auto& cmp = view.get<Desktop>(entity);

		cmp.screens.clear();
		Vector2i min{ 0, 0 };
		Vector2i max{ 0, 0 };
		for (QScreen* screen : qApp->screens())
		{
			QRect geometry = screen->geometry();

			if (geometry.topLeft().x() < min.x())
				min.x() = geometry.topLeft().x();
			if (geometry.topLeft().y() < min.y())
				min.y() = geometry.topLeft().y();
			if (geometry.bottomRight().x() > max.x())
				max.x() = geometry.bottomRight().x();
			if (geometry.bottomRight().y() > max.y())
				max.y() = geometry.bottomRight().y();

			cmp.screens.push_back(AlignedBox2i{ 
				Vector2i{geometry.topLeft().x(), geometry.topLeft().y()},
				Vector2i{geometry.bottomRight().x(), geometry.bottomRight().y()} });
		}
		cmp.desktopSize = AlignedBox2i{ min, max };
	}
}