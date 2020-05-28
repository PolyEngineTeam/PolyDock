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
		updateKeyboardKeysState(cmp);
	}
}

// ---------------------------------------------------------------------------------------------------------
bool InputSystem::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
		m_pressedKeys.insert(static_cast<Qt::Key>(static_cast<QKeyEvent*>(event)->key()));
	if (event->type() == QEvent::KeyRelease)
		m_pressedKeys.erase(static_cast<Qt::Key>(static_cast<QKeyEvent*>(event)->key()));

	return false;
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

	Input::KeyStateContainer<Input::eMouse> buttonsState;

	if (buttons.testFlag(Qt::MouseButton::LeftButton))
		buttonsState[static_cast<int>(Input::eMouse::LEFT)] = true;
	else
		buttonsState[static_cast<int>(Input::eMouse::LEFT)] = false;

	if (buttons.testFlag(Qt::MouseButton::MiddleButton))
		buttonsState[static_cast<int>(Input::eMouse::MIDDLE)] = true;
	else
		buttonsState[static_cast<int>(Input::eMouse::MIDDLE)] = false;

	if (buttons.testFlag(Qt::MouseButton::RightButton))
		buttonsState[static_cast<int>(Input::eMouse::RIGHT)] = true;
	else
		buttonsState[static_cast<int>(Input::eMouse::RIGHT)] = false;

	cmp.setNewKeysState(std::move(buttonsState));
}

// ---------------------------------------------------------------------------------------------------------
void InputSystem::updateKeyboardKeysState(Input& cmp) const
{
	Input::KeyStateContainer<Input::eKeyboard> keyboardState;

	if (m_pressedKeys.find(Qt::Key_Control) != m_pressedKeys.end())
		keyboardState[static_cast<int>(Input::eKeyboard::CTRL)] = true;

	cmp.setNewKeysState(std::move(keyboardState));
}
