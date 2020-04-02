#pragma once

#include <vector>
#include <entt/entt.hpp>

#include <pd/WindowTabHandle.hpp>

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowControlHandle
	{
	public:
		class Observer
		{
		public:
			virtual bool canClose() = 0;
			virtual bool onClose(bool forced) = 0;
		};

		TabbedWindowControlHandle(entt::registry& reg, entt::entity ent) 
			: m_registry(reg), m_entity(std::move(ent)) {}

		void registerObserver(Observer* observer);
		void unregisterObserver(Observer* observer);

		bool valid() const { return m_registry.valid(m_entity); }

		bool canClose();
		void tryClose();
		void forceClose();

	private:
		entt::registry& m_registry;
		const entt::entity m_entity;
	};
}