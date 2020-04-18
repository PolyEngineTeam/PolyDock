#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetUpdateSystem.hpp>

#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlWidgetUpdateSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, WidgetComponent, WidgetUpdateRequestComponent>();

	for (auto entity : view)
	{
		auto& cmp = view.get<Component>(entity);
		auto& widgetCmp = view.get<WidgetComponent>(entity);

		const auto* hoverCmp = registry.try_get<HoverComponent>(entity);
		const IWidget::eButton hovered = hoverCmp ? hoverCmp->hovered : IWidget::eButton::NONE;

		const bool pressed = registry.has<PressComponent>(entity);

		widgetCmp.widget->update(hovered, pressed, cmp.maximized);

		registry.remove<WidgetUpdateRequestComponent>(entity);
	}
}