#pragma once

#include <optional>
#include <string>
#include <qicon.h>

namespace pd::ecs::cmp::tab
{
	// ---------------------------------------------------------------------------------------------------------
	class TabComponent
	{
	public:
		std::string name;
		std::optional<QIcon> icon;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabContentComponent
	{
	public:
		QWidget* contentWidget = nullptr;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class DirtyTabContentComponent
	{
	public:
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class DirtyTabComponent
	{
	public:

	};
}