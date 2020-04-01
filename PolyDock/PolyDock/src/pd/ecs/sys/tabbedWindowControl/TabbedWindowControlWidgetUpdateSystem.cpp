#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetUpdateSystem.hpp>

#include <pd/ecs/cmp/tabbedWindowControl/Component.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/HoverComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/PressComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/WidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/WidgetUpdateRequestComponent.hpp>

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

		const auto* pressCmp = registry.try_get<PressComponent>(entity);
		const IWidget::eButton pressed = pressCmp ? pressCmp->pressed : IWidget::eButton::NONE;

		widgetCmp.widget->update(pressed, hovered, cmp.maximized);

		registry.remove<WidgetUpdateRequestComponent>(entity);
	}
}