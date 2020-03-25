#pragma once

#include <memory>
#include <entt/entt.hpp>

#include <pd/WindowTabHandle.hpp>

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsHeaderHandle
	{
	public:
		TabsHeaderHandle(entt::registry& reg, entt::entity ent) : m_registry(reg), m_entity(std::move(ent)) {}

		bool valid() const { return m_registry.valid(m_entity); }

		WindowTabHandle addTab();

	private:
		entt::registry& m_registry;
		const entt::entity m_entity;
	};
}