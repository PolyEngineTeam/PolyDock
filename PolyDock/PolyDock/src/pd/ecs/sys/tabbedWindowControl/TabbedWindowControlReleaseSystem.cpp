#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlReleaseSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMinimizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRestoreRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMaximizeRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCloseRequestComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlReleaseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, PressComponent, HoverComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			bool isPressed = inputComponent->isPressed(InputComponent::eMouseButton::LEFT);
			bool wasJustPressed = inputComponent->wasJustPressed(InputComponent::eMouseButton::LEFT);
			bool wasJustReleased = inputComponent->wasJustReleased(InputComponent::eMouseButton::LEFT);

			if (inputComponent->wasJustReleased(InputComponent::eMouseButton::LEFT))
			{
				const auto& cmp = view.get<Component>(entity);
				const auto& hoverCmp = view.get<HoverComponent>(entity);
				switch (hoverCmp.hovered)
				{
					case IWidget::eButton::MINIMIZE:
					{
						registry.get_or_assign<TabbedWindowMinimizeRequestComponent>(entity);
					}
					break;

					case IWidget::eButton::MAXIMIZE:
					{
						if (cmp.maximized)
							registry.get_or_assign<TabbedWindowRestoreRequestComponent>(entity);
						else
							registry.get_or_assign<TabbedWindowMaximizeRequestComponent>(entity);
					}
					break;

					case IWidget::eButton::CLOSE:
					{
						registry.get_or_assign<TabbedWindowCloseRequestComponent>(entity);
					}
					break;
				}
			}
		}
	}
}