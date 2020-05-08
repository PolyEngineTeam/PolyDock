#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControl.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Snapping.hpp>
#include <pd/ecs/cmp/tabbedWindow/Closing.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindowControl::Component, tabbedWindowControl::Widget>();

	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		for (auto entity : view)
		{
			const auto& widgetCmp = view.get<tabbedWindowControl::Widget>(entity);

			const tabbedWindowControl::IWidget::eButton hovered = widgetCmp.widget->getButtonFromPos(inputComponent->getCursorPos());

			if (hovered != tabbedWindowControl::IWidget::eButton::NONE)
			{
				registry.get_or_assign<tabbedWindowControl::Hover>(entity).hovered = hovered;
				registry.get_or_assign<tabbedWindowControl::WidgetUpdateRequest>(entity);
			}
			else if (registry.has<tabbedWindowControl::Hover>(entity))
			{
				registry.remove<tabbedWindowControl::Hover>(entity);
				registry.get_or_assign<tabbedWindowControl::WidgetUpdateRequest>(entity);
			}
		}
	}{}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlReleaseSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		tabbedWindowControl::Component, 
		tabbedWindowControl::Press, 
		tabbedWindowControl::Hover>();

	if (auto* inputComponent = registry.try_get<root::Input>(root))
	{
		for (auto entity : view)
		{
			bool isPressed = inputComponent->isPressed(root::Input::eMouse::LEFT);
			bool wasJustPressed = inputComponent->wasJustPressed(root::Input::eMouse::LEFT);
			bool wasJustReleased = inputComponent->wasJustReleased(root::Input::eMouse::LEFT);

			if (inputComponent->wasJustReleased(root::Input::eMouse::LEFT))
			{
				const auto& cmp = view.get<tabbedWindowControl::Component>(entity);
				const auto& hoverCmp = view.get<tabbedWindowControl::Hover>(entity);
				switch (hoverCmp.hovered)
				{
					case tabbedWindowControl::IWidget::eButton::MINIMIZE:
					{
						registry.get_or_assign<tabbedWindow::MinimizeRequest>(entity);
					}
					break;

					case tabbedWindowControl::IWidget::eButton::MAXIMIZE:
					{
						if (cmp.maximized)
							registry.get_or_assign<tabbedWindow::RestoreRequest>(entity);
						else
							registry.get_or_assign<tabbedWindow::MaximizeRequest>(entity);
					}
					break;

					case tabbedWindowControl::IWidget::eButton::CLOSE:
					{
						registry.get_or_assign<tabbedWindow::CloseRequest>(entity);
					}
					break;

					default:
						break;
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlPressSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<tabbedWindowControl::Component>();

	if (const auto* inputComponent = registry.try_get<root::Input>(root))
	{
		for (auto entity : view)
		{
			if (registry.has<tabbedWindowControl::Hover>(entity)
				&& inputComponent->isPressed(root::Input::eMouse::LEFT))
			{
				registry.get_or_assign<tabbedWindowControl::Press>(entity);
				registry.get_or_assign<tabbedWindowControl::WidgetUpdateRequest>(entity);
			}
			else if (registry.has<tabbedWindowControl::Press>(entity))
			{
				registry.remove<tabbedWindowControl::Press>(entity);
				registry.get_or_assign<tabbedWindowControl::WidgetUpdateRequest>(entity);
			}
		}
	}
}

} // namespace pd::ecs::sys