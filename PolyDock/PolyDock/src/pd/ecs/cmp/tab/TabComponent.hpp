#pragma once

#include <optional>
#include <string>
#include <qicon.h>

namespace pd::ecs::cmp::tab
{
	// ---------------------------------------------------------------------------------------------------------
	class Component
	{
	public:
		std::string name;
		std::optional<QIcon> icon;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class Content
	{
	public:
		QWidget* contentWidget = nullptr;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class RefreshTabContent
	{
	public:
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class RefreshTab
	{
	public:

	};
}