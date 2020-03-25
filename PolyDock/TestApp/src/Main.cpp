#include <qwidget.h>
#include <qapplication.h>
#include <qcommandlineparser.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>

#include <pd/PolyDockRegistry.hpp>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("QtProject");
	QCoreApplication::setApplicationName("Application Example");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);
	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(app);

	pd::PolyDockRegistry reg;
	pd::TabbedWindowHandle window1 = reg.createWindow();
	pd::WindowTabHandle tab1 = window1.getTabsHeader().addTab();
	pd::WindowTabHandle tab2 = window1.getTabsHeader().addTab();
	pd::WindowTabHandle tab3 = window1.getTabsHeader().addTab();

	tab1.setName("tab1");
	tab1.setTabContent(new QPushButton("tab1"));
	tab2.setName("tab2");
	tab2.setTabContent(new QLabel("tab2"));
	tab3.setName("tab3");
	tab3.setTabContent(new QLineEdit("tab3"));

	int result = app.exec();

	return result;
}
