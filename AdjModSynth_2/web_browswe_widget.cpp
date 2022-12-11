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

#include "web_browser_widget.h"

web_browser_widget::web_browser_widget(QWidget *parent)
	: QWidget(parent)
{
	QMenuBar *menuBar = new QMenuBar(0);

	QMenu *file = menuBar->addMenu(tr("&File"));
	QAction *newWindow = new QAction(tr("&New Window"), this);
	QAction *viewSource = new QAction(tr("&View Source"), this);
	QAction *dload = new QAction(tr("&Download..."), this);
	QAction *closeWindow = new QAction(tr("&To Exit"), this);
	file->addAction(newWindow);
	file->addAction(viewSource);
	file->addAction(dload);
	file->addSeparator();
	file->addAction(closeWindow);
	
	historyTab = new QMenu(tr("&History"), this);

	bookmarks = new QMenu(tr("&Bookmarks"), this);
	QAction *add = new QAction(tr("&Add"), this);
	QAction *remove = new QAction(tr("&Remove Current Page From Bookmarks"), this);
	
	bookmarks->addAction(add);
	bookmarks->addAction(remove);
	bookmarks->addSeparator();

	menuBar->addMenu(file);
	menuBar->addMenu(historyTab);
	menuBar->addMenu(bookmarks);
	menuBar->show();
	
	QPushButton *back = new QPushButton(tr("Back"));
	back->setIcon(QIcon(tr(":images/back.png")));
	back->setIconSize(QSize(32, 32));

	QPushButton *forward = new QPushButton(tr("Forward"));
	forward->setIcon(QIcon(tr(":images/forward.png")));
	forward->setIconSize(QSize(32, 32));

	QPushButton *reload = new QPushButton(tr("Reload"));
	reload->setIcon(QIcon(":images/refresh.png"));
	reload->setIconSize(QSize(32, 32));

	QPushButton *stop = new QPushButton(tr("Stop"));
	stop->setIcon(QIcon(":images/stop.png"));
	stop->setIconSize(QSize(32, 32));

	QPushButton *home = new QPushButton(tr("Home"));
	home->setIcon(QIcon(":images/home.png"));
	home->setIconSize(QSize(32, 32));

	urlbar = new QLineEdit(tr("http://www.google.com/"));
	view = new QWebView();  // WebTabUiHandling::getInstance()->mainWindow->webView;
	testView = new QWebView();
	view->load(QUrl("http://www.google.com/"));

	history = view->history();

	QVBoxLayout *layout = new QVBoxLayout;
	QGridLayout *grid = new QGridLayout;
	grid->addWidget(back, 1, 0);
	grid->addWidget(forward, 1, 1);
	grid->addWidget(reload, 1, 2);
	grid->addWidget(stop, 1, 3);
	grid->addWidget(home, 1, 4);
	grid->addWidget(urlbar, 1, 5);
	grid->setColumnMinimumWidth(5, 500);
	int cols = grid->columnCount();
	grid->addWidget(menuBar, 0, 0, 1, cols);
	layout->addLayout(grid);
	layout->addWidget(view);
	setLayout(layout);

	QObject::connect(view, SIGNAL(urlChanged(QUrl)), SLOT(updateUrlText()));
	QObject::connect(urlbar, SIGNAL(returnPressed()), SLOT(updateUrl()));
	QObject::connect(back, SIGNAL(clicked()), view, SLOT(back()));
	QObject::connect(forward, SIGNAL(clicked()), view, SLOT(forward()));
	QObject::connect(reload, SIGNAL(clicked()), view, SLOT(reload()));
	QObject::connect(stop, SIGNAL(clicked()), view, SLOT(stop()));
	QObject::connect(closeWindow, SIGNAL(triggered()), SLOT(closeW()));
	QObject::connect(newWindow, SIGNAL(triggered()), SLOT(handleNewWindow()));
	QObject::connect(historyTab, SIGNAL(aboutToShow()), SLOT(loadHistory()));
	QObject::connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
	QObject::connect(testView, SIGNAL(loadFinished(bool)), SLOT(setInSearch(bool)));
	QObject::connect(add, SIGNAL(triggered()), SLOT(addBookmark()));
	QObject::connect(remove, SIGNAL(triggered()), SLOT(removeBookmark()));
	QObject::connect(viewSource, SIGNAL(triggered()), SLOT(source()));
	QObject::connect(dload, SIGNAL(triggered()), SLOT(downloadWindow()));
	QObject::connect(view, SIGNAL(loadFinished(bool)), SLOT(autoFillData(bool)));

	loadBookmarks();
	
	view->show();
}

void web_browser_widget::downloadWindow() 
{
	downUrl = new QLineEdit(0);
	downUrl->show();
	downUrl->setText("Enter URL here...");
	QObject::connect(downUrl, SIGNAL(returnPressed()), SLOT(getDownload()));
}

void web_browser_widget::autoFillData(bool success) 
{
	if (success) 
	{
		QDir cur;
		QString filename = cur.currentPath() + "/credentials.txt";
		QFile file(filename);
		file.open(QIODevice::ReadOnly);
		QTextStream in(&file);
		while (!in.atEnd()) 
		{
			QUrl line = in.readLine();
			if (view->url() == line) 
			{
				qDebug() << "match founc: " << line.toString();
				QString username = in.readLine();
				QString password = in.readLine();
				if (username != "0") 
				{
					QWebElement user = view->page()->currentFrame()->findFirstElement("input[name=email]");
					user.setAttribute("value", username);
				}
				if (password != "0") 
				{
					QWebElement pass = view->page()->currentFrame()->findFirstElement("input[type=password]");
					pass.setAttribute("value", password);
				}
			}
		}
	}
}

void web_browser_widget::getDownload() 
{
	QUrl url = QUrl(downUrl->text());
	QString temp = url.toString();
	QDir dir;
	int i = temp.lastIndexOf("/");
	QString s = temp.right(temp.length() - i);
	QString filename = dir.homePath() + "/" + s;
	dFile.setFileName(filename);
	dFile.open(QIODevice::ReadWrite | QIODevice::Append);
	QNetworkAccessManager* accessManager = view->page()->networkAccessManager();
	QNetworkRequest request;
	request.setUrl(url);
	setWindowTitle(QString("Download Started!"));
	QNetworkReply* reply = accessManager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(outputDownload()));
}

void web_browser_widget::outputDownload() 
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
	dFile.write(reply->readAll());
	setWindowTitle(QString("Download Finished!"));
	dFile.close();
	reply->deleteLater();
}

void web_browser_widget::source() 
{
	QNetworkAccessManager* accessManager = view->page()->networkAccessManager();
	QNetworkRequest request;
	request.setUrl(view->url());
	QNetworkReply* reply = accessManager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(downloaded()));
}

void web_browser_widget::downloaded() {
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
	QTextEdit* textEdit = new QTextEdit(0);
	textEdit->show();
	textEdit->setPlainText(reply->readAll());
	textEdit->setReadOnly(true);
	textEdit->setMinimumSize(500, 500);
	reply->deleteLater();
}

void web_browser_widget::updateUrl() 
{
	QString temp = urlbar->text();
	if (!temp.contains("https://")) 
	{
		if (!temp.contains(".com") && !temp.contains(".net") && !temp.contains(".org") && !temp.contains(".gov") &&
		    !temp.contains(".edu") && !temp.contains(".tv") && !temp.contains(".mil"))
		{
			temp.insert(temp.size(), QString(".com"));
		}
		if (!temp.contains("www."))
		{	
			temp.insert(0, QString("www."));
		}
		if (!temp.contains("http://"))
		{
			temp.insert(0, QString("http://"));
		}
	}
	urlbar->setText(temp);
	view->load(QUrl(temp));
	testView->load(QUrl(temp));
}

void web_browser_widget::updateUrlText() {
	QString temp = (view->url()).toString();
	urlbar->setText(temp);
	//if(temp == "https://webmail.seas.upenn.edu/imp/login.php?url=/dimp/index.php"){
	if(temp == "http://www.facebook.com/") 
	{
		promptForCredentials();
	}
}

void web_browser_widget::promptForCredentials() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/credentials.txt";
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString username, password;
		QString line = in.readLine();
		if (view->url() == QUrl(line)) 
		{
			// If url has already been saved to credentials.txt, skip
			return;
		}
		else 
		{
			if (!in.atEnd()){ in.readLine(); }
			if (!in.atEnd()){ in.readLine(); }
		}
	}

	prompt = new QWidget(0, 0);
	QGridLayout *layout = new QGridLayout(prompt);
	QLabel *username = new QLabel(*new QString("Username:"), prompt);
	QLabel *password = new QLabel(*new QString("Password:"), prompt);
	QLineEdit *namein = new QLineEdit(prompt);
	QLineEdit *passin = new QLineEdit(prompt);
	QPushButton *check = new QPushButton(*new QString("Don't save or ask again."), prompt);
	QPushButton *end = new QPushButton(*new QString("Accept"), prompt);

	layout->addWidget(username, 0, 0, 0);
	layout->addWidget(namein, 0, 1, 0);
	layout->addWidget(password, 1, 0, 0);
	layout->addWidget(passin, 1, 1, 0);
	layout->addWidget(check, 2, 0, 0);
	layout->addWidget(end, 2, 1, 0);
	prompt->setLayout(layout);
	prompt->show();

	QObject::connect(check, SIGNAL(clicked()), SLOT(dontSave()));
	QObject::connect(end, SIGNAL(clicked()), SLOT(saveData()));
}

void web_browser_widget::saveData() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/credentials.txt";
	QFile file(filename);
	file.open(QIODevice::ReadWrite | QIODevice::Append);
	QTextStream out(&file);
	out << view->url().toString() << "\n";
	QGridLayout *grid = (QGridLayout*)(prompt->layout());
	out << ((QLineEdit*)(grid->itemAtPosition(0, 1)->widget()))->text() << "\n";
	out << ((QLineEdit*)(grid->itemAtPosition(1, 1)->widget()))->text() << "\n";
	file.close();
	prompt->close();
	autoFillData(true);
}

void web_browser_widget::dontSave() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/credentials.txt";
	QFile file(filename);
	file.open(QIODevice::ReadWrite | QIODevice::Append);
	QTextStream out(&file);
	out << view->url().toString() << "\n";
	out << "0\n";
	out << "0\n";
	file.close();
	prompt->close();
}

void web_browser_widget::loadHistory()
{
	historyTab->clear();
	QList<QWebHistoryItem> pastTen = history->backItems(10);
	while (!pastTen.isEmpty()) 
	{
		QWebHistoryItem historyItem = pastTen.takeFirst();
		QAction *item = new QAction(historyItem.title(), historyTab);
		item->setData(historyItem.url());
		historyTab->addAction(item);
		QObject::connect(historyTab, SIGNAL(triggered(QAction*)), SLOT(historyAction(QAction*)));
	}
}

void web_browser_widget::setInSearch(bool success) 
{
	if (!success) 
	{
		QString temp = urlbar->text();
		QString sear = "http://www.google.com/search?hl=en&q=";
		QStringList l;
		int i = 0;
		temp.remove(".com");
		temp.remove("http://www.");
		l = temp.split(" ");
		while (i < l.count()) 
		{
			sear = sear.append(l[i]);
			sear = sear.append("+");
			i++;
		}
		urlbar->setText(sear);
		view->load(QUrl(sear));
	}
}

void web_browser_widget::historyAction(QAction* act)
{
	QUrl toLoad = act->data().toUrl();
	view->load(toLoad);
}

void web_browser_widget::bookmarkAction(QAction* act)
{
	QUrl toLoad = act->data().toUrl();
	view->load(toLoad);
}

void web_browser_widget::setProgress(int prog)
{
	progress = prog;
	if (progress <= 0 || progress >= 100)
	{	
		setWindowTitle(QString("Done!"));
	}
	else
	{	
		setWindowTitle(QString("%1% Loaded...").arg(progress));
	}
}

void web_browser_widget::handleNewWindow() 
{
	web_browser_widget *newW = new web_browser_widget();
	newW->show();
}

void web_browser_widget::closeW() 
{
	close();
}

void web_browser_widget::loadBookmarks() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/bookmarks.txt";
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QUrl line = in.readLine();
		QAction *item = new QAction(line.toString(), bookmarks);
		item->setData(line);
		bookmarks->addAction(item);
		QObject::connect(bookmarks, SIGNAL(triggered(QAction*)), SLOT(bookmarkAction(QAction*)));
	}
}

void web_browser_widget::addBookmark() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/bookmarks.txt";
	QFile file(filename);
	file.open(QIODevice::ReadWrite | QIODevice::Append);
	QTextStream out(&file);
	out << view->url().toString() << "\n";
	QAction *item = new QAction(view->url().toString(), bookmarks);
	item->setData(view->url());
	bookmarks->addAction(item);
	QObject::connect(bookmarks, SIGNAL(triggered(QAction*)), SLOT(bookmarkAction(QAction*)));
	setWindowTitle(QString("Bookmark Added!"));
	file.close();
}

void web_browser_widget::removeBookmark() 
{
	QDir cur;
	QString filename = cur.currentPath() + "/bookmarks.txt";
	QString temp = cur.currentPath() + "/temp.txt";
	QFile file(filename);
	QFile file2(temp);
	file.open(QIODevice::ReadWrite);
	file2.open(QIODevice::ReadWrite | QIODevice::Append);
	QTextStream in(&file);
	QTextStream out(&file2);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
		if (!(line == view->url().toString())) {
			out << line << "\n";
		}
	}
	file.remove("bookmarks.txt");
	file2.rename("bookmarks.txt");
	bookmarks->clear();
	QAction *add = new QAction(tr("&Add"), this);
	QAction *remove = new QAction(tr("&Remove Current Page From Bookmarks"), this);
	bookmarks->addAction(add);
	bookmarks->addAction(remove);
	bookmarks->addSeparator();
	QObject::connect(add, SIGNAL(triggered()), SLOT(addBookmark()));
	QObject::connect(remove, SIGNAL(triggered()), SLOT(removeBookmark()));
	loadBookmarks();
	setWindowTitle(QString("Bookmark Removed!"));
	file.close();
}