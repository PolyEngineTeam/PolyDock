#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowSnapMovementSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/root/DesktopComponent.hpp>
#include <pd/ecs/cmp/root/DesktopComponent.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowSnapMovementSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowMovementRequestComponent,
		TabbedWindowComponent>();

	const auto* inputCmp = registry.try_get<InputComponent>(root);
	const auto* desktopCmp = registry.try_get<DesktopComponent>(root);

	if (inputCmp && desktopCmp && inputCmp->wasJustReleased(InputComponent::eMouseButton::LEFT))
	{
		const Vector2i mousePos = inputCmp->getCursorPos();

		for (auto entity : view)
		{
			const int screenIdx = desktopCmp->getScreenForPosition(mousePos);

			auto& request = view.get<TabbedWindowMovementRequestComponent>(entity);
			auto& window = view.get<TabbedWindowComponent>(entity);

			window.position = request.newWindowPos;

			registry.remove<TabbedWindowMovementRequestComponent>(entity);
			registry.get_or_assign<DirtyTabbedWindowComponent>(entity);
		}
	}
}