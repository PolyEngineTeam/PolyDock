#pragma once

#include <tuple>
#include <Eigen/Dense>

namespace pd::ecs::cmp::root
{
	// ---------------------------------------------------------------------------------------------------------
	class Input
	{
	public:
		enum class eMouse
		{
			LEFT = 0,
			MIDDLE,
			RIGHT,

			COUNT
		};

		enum class eKeyboard
		{
			CTRL = 0,

			COUNT
		};

		template <typename E>
		class KeyStateContainer : public std::array<bool, static_cast<int>(E::COUNT)>
		{
		};

		template <typename E>
		bool isPressed(E key) const { return getCurrent(key); }

		template <typename E>
		bool wasJustPressed(E key) const { return getCurrent(key) == true && getLast(key) == false; }

		template <typename E>
		bool wasJustReleased(E key) const { return getCurrent(key) == false && getLast(key) == true; }

		template <typename E>
		void setNewKeysState(KeyStateContainer<E> newState)
		{ 
			auto& current = std::get<KeyStateContainer<E>>(m_currentKeyStates);
			std::get<KeyStateContainer<E>>(m_lastKeyStates) = std::move(current);
			current = std::move(newState);
		}

		// mouse cursor
		Eigen::Vector2i getCursorPos() const { return m_cursorPos; }
		Eigen::Vector2i getCursorDiff() const { return m_cursorDiff; }

		void setNewCursorPos(Eigen::Vector2i newCursorPos)
		{
			m_cursorDiff = newCursorPos - m_cursorPos;
			m_cursorPos = std::move(newCursorPos);
		}


	private:
		template <typename E>
		bool getCurrent(E key) const { return std::get<KeyStateContainer<E>>(m_currentKeyStates)[static_cast<int>(key)]; }

		template <typename E>
		bool getLast(E key) const { return std::get<KeyStateContainer<E>>(m_lastKeyStates)[static_cast<int>(key)]; }

		std::tuple<KeyStateContainer<eMouse>, KeyStateContainer<eKeyboard>> m_currentKeyStates = { { false }, { false } };
		std::tuple<KeyStateContainer<eMouse>, KeyStateContainer<eKeyboard>> m_lastKeyStates = { { false }, { false } };

		Eigen::Vector2i m_cursorPos;
		Eigen::Vector2i m_cursorDiff;

	};
}