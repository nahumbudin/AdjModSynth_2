/**
* @file		WebTab.cpp
*	@author		Nahum Budin
*	@date		14-5-2020
*	@version	1.0
*
*	@brief		Web Browswr Tab.
*	
*	https://sourceforge.net/projects/qtwebbrowser/
*/

#include "WebTab.h"


WebTabUiHandling *WebTabUiHandling::webTabUiHandlingInstance = NULL;

WebTabUiHandling::WebTabUiHandling(Ui_MainWindow *mainWind)
{
	mainWindow = mainWind;
	webTabUiHandlingInstance = this;
	
	browser = new web_browser_widget(mainWindow->webView);
	browser->show();
}

WebTabUiHandling *WebTabUiHandling::getInstance()
{
	return webTabUiHandlingInstance;
}


