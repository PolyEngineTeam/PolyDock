#pragma once

#include <set>
#include <QObject>
#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::cmp::root { class Input; }

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	class InputSystem : public SystemBase, public QObject
	{
	public:
		void update(entt::registry&, entt::entity root) const final;

	private:
		bool eventFilter(QObject* watched, QEvent* event) final;

		void updateCursorPos(cmp::root::Input& cmp) const;
		void updateMouseButtonState(cmp::root::Input& cmp) const;
		void updateKeyboardKeysState(cmp::root::Input& cmp) const;

		std::set<Qt::Key> m_pressedKeys;
	};
}