#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::root
{
	// ---------------------------------------------------------------------------------------------------------
	class Input
	{
	public:
		enum class eMouseButton
		{
			LEFT = 0,
			MIDDLE,
			RIGHT,

			COUNT
		};

		using ButtonStateArrayType = std::array<bool, static_cast<int>(eMouseButton::COUNT)>;

		bool isPressed(eMouseButton button) const { return m_currentButtonState[static_cast<int>(button)]; }

		bool wasJustPressed(eMouseButton button) const
		{
			return m_currentButtonState[static_cast<int>(button)] == true
				&& m_lastButtonState[static_cast<int>(button)] == false;
		}

		bool wasJustReleased(eMouseButton button) const
		{
			return m_currentButtonState[static_cast<int>(button)] == false
				&& m_lastButtonState[static_cast<int>(button)] == true;
		}

		Eigen::Vector2i getCursorPos() const { return m_cursorPos; }
		Eigen::Vector2i getCursorDiff() const { return m_cursorDiff; }

		void setNewButtonState(ButtonStateArrayType newState) 
		{ 
			m_lastButtonState = std::move(m_currentButtonState); 
			m_currentButtonState = std::move(newState); 
		}

		void setNewCursorPos(Eigen::Vector2i newCursorPos)
		{
			m_cursorDiff = newCursorPos - m_cursorPos;
			m_cursorPos = std::move(newCursorPos);
		}

	private:
		ButtonStateArrayType m_currentButtonState = { false };
		ButtonStateArrayType m_lastButtonState = { false };

		Eigen::Vector2i m_cursorPos;
		Eigen::Vector2i m_cursorDiff;

	};
}