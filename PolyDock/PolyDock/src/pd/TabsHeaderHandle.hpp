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
		class IObserver
		{
		public:
			virtual bool onTabAdded() = 0;
		};

		TabsHeaderHandle(entt::registry& reg, entt::entity ent) : m_registry(reg), m_entity(std::move(ent)) {}

		void registerObserver(IObserver* observer) { }
		void unregisterObserver(IObserver* observer);

		bool valid() const { return m_registry.valid(m_entity); }

		WindowTabHandle addTab();

	private:
		entt::registry& m_registry;
		const entt::entity m_entity;
	};
}