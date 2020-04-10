#pragma once

#include <string>
#include <optional>
#include <entt/entt.hpp>
#include <qwidget.h>
#include <qicon.h>

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class WindowTabHandle
	{
	public:
		WindowTabHandle(entt::registry& reg, entt::entity ent) : m_registry(reg), m_entity(ent) {}

		bool valid() const { return m_registry.valid(m_entity); }

		void setName(std::string name);
		void setIcon(std::optional<QIcon> newIcon);
		void setTabContent(QWidget* widget);
		void close();

	private:
		entt::registry& m_registry;
		const entt::entity m_entity;
	};
}