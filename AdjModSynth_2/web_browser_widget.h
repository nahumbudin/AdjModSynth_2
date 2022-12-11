/**
* @file		web_browser_widget.cpp
*	@author		Nahum Budin
*	@date		14-5-2020
*	@version	1.0
*
*	@brief		Web Browswr Widget.
*	
*	https://sourceforge.net/projects/qtwebbrowser/
*/

#ifndef _WEB_BRO_WIDG
#define _WEB_BRO_WIDG

#include <QLayout>
#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

#include <QMenuBar>

#include <QFile>
#include <QDir>

#include <QWebHistory>
#include <QWebView>
#include <QWebElement>
#include <QWebFrame>
#include <QNetworkReply>


class web_browser_widget : public QWidget
{
	Q_OBJECT
	
public :
	web_browser_widget(QWidget *parent = 0);
	
public slots :
	void handleNewWindow();
	void setProgress(int p);
	void loadHistory();
	void updateUrlText();
	void historyAction(QAction* act);
	void updateUrl();
	void closeW();
	void setInSearch(bool success);
	void addBookmark();
	void removeBookmark();
	void bookmarkAction(QAction* act);
	void loadBookmarks();
	void source();
	void downloaded();
	void downloadWindow();
	void getDownload();
	void outputDownload();
	void promptForCredentials();
	void dontSave();
	void saveData();
	void autoFillData(bool success);
	
private:
	int progress;
	QFile dFile;
	QWebHistory *history;
	QLineEdit *downUrl;
	QMenu *historyTab;
	QMenu *bookmarks;
	QLineEdit *urlbar;
	QWebView *view;
	QWebView *testView;
	
protected:
	QWidget *prompt;
	
};

#endif
