#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlReleaseSystem.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys::tabbedWindowControl
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlReleaseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabbedWindowControl::Component, 
		::tabbedWindowControl::Press, 
		::tabbedWindowControl::Hover>();

	if (auto* inputComponent = registry.try_get<root::Input>(root))
	{
		for (auto entity : view)
		{
			bool isPressed = inputComponent->isPressed(root::Input::eMouseButton::LEFT);
			bool wasJustPressed = inputComponent->wasJustPressed(root::Input::eMouseButton::LEFT);
			bool wasJustReleased = inputComponent->wasJustReleased(root::Input::eMouseButton::LEFT);

			if (inputComponent->wasJustReleased(root::Input::eMouseButton::LEFT))
			{
				const auto& cmp = view.get<::tabbedWindowControl::Component>(entity);
				const auto& hoverCmp = view.get<::tabbedWindowControl::Hover>(entity);
				switch (hoverCmp.hovered)
				{
					case ::tabbedWindowControl::IWidget::eButton::MINIMIZE:
					{
						registry.get_or_assign<tabbedWindow::MinimizeRequest>(entity);
					}
					break;

					case ::tabbedWindowControl::IWidget::eButton::MAXIMIZE:
					{
						if (cmp.maximized)
							registry.get_or_assign<tabbedWindow::RestoreRequest>(entity);
						else
							registry.get_or_assign<tabbedWindow::MaximizeRequest>(entity);
					}
					break;

					case ::tabbedWindowControl::IWidget::eButton::CLOSE:
					{
						registry.get_or_assign<tabbedWindow::CloseRequest>(entity);
					}
					break;
				}
			}
		}
	}
}

} // namespace pd::ecs::sys::tabbedWindowControl