/**
* @file		WebTab.h
*	@author		Nahum Budin
*	@date		14-5-2020
*	@version	1.0
*
*	@brief		Web Browswr Tab.
*	
*	https://sourceforge.net/projects/qtwebbrowser/
*/

#ifndef _WEB_TAB
#define _WEB_TAB

#include <QMainWindow>
#include <QObject>

#include "web_browser_widget.h"

#include <ui_MainWindow.h>

class web_browser_widget;

class WebTabUiHandling : public QMainWindow 
{
	Q_OBJECT

public :
	WebTabUiHandling(Ui_MainWindow *mainWind);
	
	static WebTabUiHandling *getInstance();
	
	Ui_MainWindow *mainWindow;
	
private:
		
	web_browser_widget *browser;
	
	static WebTabUiHandling *webTabUiHandlingInstance;
	
};



#endif
