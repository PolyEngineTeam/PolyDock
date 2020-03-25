#include <pd/pch/PCH.h>
#include <pd/ecs/sys/root/InputSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>

using namespace ::pd::ecs::sys::root;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void InputSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<InputComponent>();
	Expects(view.size() == 1);

	for (auto entity : view)
	{
		auto& cmp = view.get<InputComponent>(entity);

		updateCursorPos(cmp);
		updateMouseButtonState(cmp);
	}
}

// ---------------------------------------------------------------------------------------------------------
void InputSystem::updateCursorPos(InputComponent& cmp) const
{
	const QPoint pos = QCursor::pos();
	cmp.setNewCursorPos({ pos.x(), pos.y() });
}

// ---------------------------------------------------------------------------------------------------------
void InputSystem::updateMouseButtonState(InputComponent& cmp) const
{
	Qt::MouseButtons buttons = QApplication::mouseButtons();

	InputComponent::ButtonStateArrayType buttonsState = { false };

	if (buttons.testFlag(Qt::MouseButton::LeftButton))
		buttonsState[static_cast<int>(InputComponent::eMouseButton::LEFT)] = true;
	if (buttons.testFlag(Qt::MouseButton::MiddleButton))
		buttonsState[static_cast<int>(InputComponent::eMouseButton::MIDDLE)] = true;
	if (buttons.testFlag(Qt::MouseButton::RightButton))
		buttonsState[static_cast<int>(InputComponent::eMouseButton::RIGHT)] = true;

	cmp.setNewButtonState(std::move(buttonsState));
}
