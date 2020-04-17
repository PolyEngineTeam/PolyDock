#pragma once

#include <pd/TabsHeaderHandle.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsHeaderComponent
	{
	public:
		explicit TabsHeaderComponent(std::vector<entt::entity> tabs) : m_tabs(std::move(tabs)) {};
		void registerObserver(pd::TabsHeaderHandle::IObserver* observer)
		{
			m_observers.push_back(observer);
		}

		void unregisterObserver(pd::TabsHeaderHandle::IObserver* observer)
		{
			m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer));
		}

		void insertTab(entt::entity entity, size_t idx)
		{
			m_tabs.insert(m_tabs.begin() + idx, entity);
			for (auto obs : m_observers)
				obs->onTabAdded();
		}

		void appendTab(entt::entity entity)
		{
			m_tabs.push_back(entity);
			for (auto obs : m_observers)
				obs->onTabAdded();
		}

		void closeTab(entt::entity entity)
		{
			m_tabs.erase(std::remove(m_tabs.begin(), m_tabs.end(), entity));
			for (auto obs : m_observers)
				obs->onTabClosed();
		}

		const std::vector<entt::entity>& tabs() const { return m_tabs; }
		std::vector<entt::entity>& tabsMut() { return m_tabs; }

	private:
		std::vector<entt::entity> m_tabs;
		std::vector<pd::TabsHeaderHandle::IObserver*> m_observers;
	};
}