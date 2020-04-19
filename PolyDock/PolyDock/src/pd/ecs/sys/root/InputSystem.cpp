#include <pd/pch/PCH.h>
#include <pd/ecs/sys/root/InputSystem.hpp>

#include <pd/ecs/cmp/root/Input.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void InputSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Input>();
	Expects(view.size() == 1);

	for (auto entity : view)
	{
		auto& cmp = view.get<Input>(entity);

		updateCursorPos(cmp);
		updateMouseButtonState(cmp);
	}
}

// ---------------------------------------------------------------------------------------------------------
void InputSystem::updateCursorPos(Input& cmp) const
{
	const QPoint pos = QCursor::pos();
	cmp.setNewCursorPos({ pos.x(), pos.y() });
}

// ---------------------------------------------------------------------------------------------------------
void InputSystem::updateMouseButtonState(Input& cmp) const
{
	Qt::MouseButtons buttons = QApplication::mouseButtons();

	Input::ButtonStateArrayType buttonsState = { false };

	if (buttons.testFlag(Qt::MouseButton::LeftButton))
		buttonsState[static_cast<int>(Input::eMouseButton::LEFT)] = true;
	if (buttons.testFlag(Qt::MouseButton::MiddleButton))
		buttonsState[static_cast<int>(Input::eMouseButton::MIDDLE)] = true;
	if (buttons.testFlag(Qt::MouseButton::RightButton))
		buttonsState[static_cast<int>(Input::eMouseButton::RIGHT)] = true;

	cmp.setNewButtonState(std::move(buttonsState));
}
