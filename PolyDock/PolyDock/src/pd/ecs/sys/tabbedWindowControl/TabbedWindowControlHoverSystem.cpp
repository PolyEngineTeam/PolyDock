#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlHoverSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, Widget>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& widgetCmp = view.get<Widget>(entity);

			const IWidget::eButton hovered = widgetCmp.widget->getButtonFromPos(inputComponent->getCursorPos());

			if (hovered != IWidget::eButton::NONE)
			{
				registry.get_or_assign<Hover>(entity).hovered = hovered;
				registry.get_or_assign<WidgetUpdateRequest>(entity);
			}
			else if (registry.has<Hover>(entity))
			{
				registry.remove<Hover>(entity);
				registry.get_or_assign<WidgetUpdateRequest>(entity);
			}
		}
	}{}
}