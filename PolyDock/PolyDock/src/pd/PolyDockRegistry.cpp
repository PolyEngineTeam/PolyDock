#include <pd/pch/PCH.h>
#include <pd/PolyDockRegistry.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>

// input
#include <pd/ecs/sys/root/InputSystem.hpp>
// tabs header - no mode
#include <pd/ecs/sys/tabsHeader/TabsSelectionSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsActivationSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeaderHoverSystem.hpp>
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
// tabs header widget support
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetInitializationSystem.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWIdgetUpdateSystem.hpp>
// tabbed window widget support
#include <pd/ecs/sys/tabbedWindow/TabbedWindowRemovalSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCreationSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetInitializationSystem.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetUpdateSystem.hpp>

// dock widget support

// root components
#include <pd/ecs/cmp/root/RootComponent.hpp>
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>
// window creation
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCreateRequestComponent.hpp>
// dock
#include <pd/ecs/cmp/dock/DockComponent.hpp>

using namespace ::Eigen;
using namespace ::pd;

// ---------------------------------------------------------------------------------------------------------
PolyDockRegistry::PolyDockRegistry()
{
	m_root = m_registry.create();
	m_registry.assign<ecs::cmp::root::RootComponent>(m_root);
	m_registry.assign<ecs::cmp::root::InputComponent>(m_root);
	m_registry.assign<ecs::cmp::root::WidgetsOwnerComponent>(m_root);

	// input
	m_systems.push_back(std::make_unique<ecs::sys::root::InputSystem>());
	// tabs header - no mode
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsSelectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsActivationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderHoverSystem>());
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
	// tabs header widget support
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabsHeader::TabsHeaderWidgetUpdateSystem>());
	// tabbed window widget support
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowRemovalSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowCreationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::tabbedWindow::TabbedWindowWidgetUpdateSystem>());

	QObject::connect(&m_timer, &QTimer::timeout, this, [this]() { update(); });

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

	m_registry.assign<ecs::cmp::tabbedWindow::TabbedWindowCreateRequestComponent>(windowEntity, 
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

	m_registry.assign<ecs::cmp::dock::DockComponent>(dockEntity);

	update();

	return window;
}

// ---------------------------------------------------------------------------------------------------------
void pd::PolyDockRegistry::update()
{
	for (const std::unique_ptr<ecs::sys::SystemBase>& system : m_systems)
		system->update(m_registry, m_root);
}
