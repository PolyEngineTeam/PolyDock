#include <pd/pch/PCH.h>
#include <pd/PolyDockRegistry.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

// input
#include <pd/ecs/sys/root/InputSystem.hpp>
#include <pd/ecs/sys/root/DesktopSystem.hpp>
// tabs header - no mode
#include <pd/ecs/sys/tabsHeader/TabsSelectionSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsActivationSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeaderHoverSystem.hpp>
// tabbed window control no mode
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlHoverSystem.hpp>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlReleaseSystem.hpp>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlPressSystem.hpp>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlReleaseSystem.hpp>
// tabbed window focus
#include <pd/ecs/sys/tabbedWindow/TabbedWindowFocusSystem.hpp>
// tabbed window resize
#include <pd/ecs/sys/tabbedWindow/TabbedWindowSnapSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRestoreSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMinimizeSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMaximizeSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeHoverSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeStartSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeDetectionSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeEndSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeSystem.hpp>
// tabbed window movement
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementStartSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementDetectionSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementEndSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementSystem.hpp>
// tabs movement
#include <pd/ecs/sys/tabsHeader/TabsMovementStartSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsMovementDetectionSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsMovementEndSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsMovementSystem.hpp>
// tabs drag in
#include <pd/ecs/sys/tabsHeader/TabsDragInDetectionSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsDragInSystem.hpp>
// tabs drag out
#include <pd/ecs/sys/tabsHeader/TabsDragOutDetectionSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsDragOutSystem.hpp>
// tabbed window control widget support
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetInitializationSystem.hpp>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetUpdateSystem.hpp>
// tabs header widget support
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetInitializationSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetUpdateSystem.hpp>
// tabbed window widget support
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCloseSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRemovalSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCreationSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetInitializationSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetUpdateSystem.hpp>
// tab adding support
#include <pd/ecs/sys/tabsHeader/TabsHeaderTabsAdding.hpp>
// tab removing support
#include <pd/ecs/sys/tabsHeader/TabsRemovalSystem.hpp>

// dock widget support

// root components
#include <pd/ecs/cmp/root/Desktop.hpp>
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
// window creation
#include <pd/ecs/cmp/tabbedWindow/Opening.hpp>
// dock
#include <pd/ecs/cmp/dock/Dock.hpp>

using namespace ::Eigen;
using namespace ::pd;

static void registerQtResources()
{
	Q_INIT_RESOURCE(Resource);
}

// ---------------------------------------------------------------------------------------------------------
PolyDockRegistry::PolyDockRegistry()
{
	registerQtResources();

	m_root = m_registry.create();
	m_registry.assign<ecs::cmp::root::Desktop>(m_root);
	m_registry.assign<ecs::cmp::root::Input>(m_root);
	m_registry.assign<ecs::cmp::root::WidgetsOwner>(m_root);

	// input
	m_systems.push_back(std::make_unique<ecs::sys::root::InputSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::root::DesktopSystem>());
	// tabs header - no mode
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsSelectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsActivationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderHoverSystem>());
	// tabbed window control no mode
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindowControl::TabbedWindowControlHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindowControl::TabbedWindowControlReleaseSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindowControl::TabbedWindowControlPressSystem>());
	// tabbed window focus
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowFocusSystem>());
	// tabbed window resize
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowSnapSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowRestoreSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMinimizeSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMaximizeSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowResizeHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowResizeStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowResizeDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowResizeEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowResizeSystem>());
	// tabbed window movement
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMovementStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMovementDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMovementEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowMovementSystem>());
	// tabs movement
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsMovementStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsMovementDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsMovementEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsMovementSystem>());
	// tabs drag in
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsDragInDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsDragInSystem>());
	// tabs drag out
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsDragOutDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsDragOutSystem>());
	// tab adding
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::AddButtonHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::AddButtonPressSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsCreationSystem>());
	// tabbed window control widget support
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindowControl::TabbedWindowControlWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindowControl::TabbedWindowControlWidgetUpdateSystem>());
	// tabs header widget support
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderWidgetUpdateSystem>());
	// tabbed window widget support
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowCloseSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowRemovalSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowCreationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowWidgetUpdateSystem>());

	//-----------------------------------------------------------------------------------------
	// Late systems
	//-----------------------------------------------------------------------------------------
	// tab removing
	m_lateSystems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsRemovalSystem>());
	m_lateSystems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderWidgetUpdateSystem>()); // needs to update state after removing and before TabsHeaderHoverSystem

	QObject::connect(&m_timer, &QTimer::timeout, this, [this]() { update(); lateUpdate(); });

	m_timer.start(10);
}

// ---------------------------------------------------------------------------------------------------------
PolyDockRegistry::~PolyDockRegistry()
{
}

// ---------------------------------------------------------------------------------------------------------
TabbedWindowHandle PolyDockRegistry::createWindow()
{
	auto windowEntity = m_registry.create();
	auto header = TabsHeaderHandle(m_registry, windowEntity);
	auto control = TabbedWindowControlHandle(m_registry, windowEntity);
	auto window = TabbedWindowHandle(header, control);

	m_registry.assign<ecs::cmp::tabbedWindow::CreateRequest>(windowEntity, 
		std::vector<entt::entity>{}, std::vector<entt::entity>{}, std::optional<entt::entity>{},
		Vector2i{ 100, 100 }, Vector2i{ 500, 500 });

	update();

	return window;
}

// ---------------------------------------------------------------------------------------------------------
DockWidgetHandle pd::PolyDockRegistry::createDockWidget()
{
	auto dockEntity = m_registry.create();
	auto window = DockWidgetHandle(m_registry, dockEntity);

	m_registry.assign<ecs::cmp::dock::Component>(dockEntity);

	update();

	return window;
}

// ---------------------------------------------------------------------------------------------------------
void pd::PolyDockRegistry::update()
{
	for (const std::unique_ptr<ecs::sys::SystemBase>& system : m_systems)
		system->update(m_registry, m_root);
}

void pd::PolyDockRegistry::lateUpdate()
{
	for (const std::unique_ptr<ecs::sys::SystemBase>& system : m_lateSystems)
		system->update(m_registry, m_root);
}
