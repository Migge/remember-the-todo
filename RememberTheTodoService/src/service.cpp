/*
 * Copyright (c) 2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "service.hpp"
#include <bb/Application>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>
#include <bb/system/InvokeManager>
#include <bb/pim/notebook/NotebookService>
#include <QTimer>

#define TODOTXT_FILE "shared/Dropbox/temp/todooo.txt"

using namespace bb::platform;
using namespace bb::system;
using namespace bb::pim;

Service::Service(bb::Application * app)	:
		QObject(app),
		m_notify(new Notification(this)),
		m_invokeManager(new InvokeManager(this))
{
	NotificationDefaultApplicationSettings settings;
	settings.setPreview(NotificationPriorityPolicy::Allow);
	settings.apply();

	m_notify->setTitle("RememberTheTodo Service");
	m_notify->setBody("RememberTheTodo service requires attention");

	bb::system::InvokeRequest request;
	request.setTarget("com.example.RememberTheTodo");
	request.setAction("bb.action.START");
	m_notify->setInvokeRequest(request);

	m_accountKey = account::AccountService().defaultAccount( account::Service::Notebook ).id();
	m_notebookService = new notebook::NotebookService;

	//onTimeout();

	m_invokeManager->connect(m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            this, SLOT(handleInvoke(const bb::system::InvokeRequest&)));

	m_fileSystemWatcher = new QFileSystemWatcher(this);
	QObject::connect(m_fileSystemWatcher, SIGNAL(fileChanged(const QString&)),
			this, SLOT(onFileChanged(const QString&)));
	QFile textfile(TODOTXT_FILE);
	QFileInfo fileinfo(textfile);
	m_fileSystemWatcher->addPath(fileinfo.absoluteFilePath());
}

void Service::handleInvoke(const bb::system::InvokeRequest & request) {
	if (request.action().compare("com.example.RememberTheTodoService.RESET") == 0) {
		triggerNotification();
	}
}

void Service::triggerNotification() {
	// Timeout is to give time for UI to minimize
	QTimer::singleShot(2000, this, SLOT(onTimeout()));
}

void Service::onTimeout() {
	Notification::clearEffectsForAll();
	Notification::deleteAllFromInbox();
	m_notify->notify();

	// Retrieve the account key for the user account that's currently active on the
	// device. This key is used when notebooks are added to the notebook database.
	//account::AccountKey accountKey = account::AccountService().defaultAccount( account::Service::Notebook ).id();

	// Create the notebook service object. Make sure that you don't recreate this
	// object each time you need to access the notebook service, though.
	//NotebookService service;

	// Create the notebook and set its name
	//notebook::Notebook myNotebook;
	//myNotebook.setName("My Notebook");

	// Add the new notebook to the database
	//m_notebookService->addNotebook(&myNotebook, m_accountKey);
	notebook::NotebookKey key = (notebook::NotebookKey)getNotebook("Hejsan");

	// Create the first notebook entry and set its title
	notebook::NotebookEntry firstEntry;
	firstEntry.setTitle("My First Notebook Entry");

	// Add the new notebook entries to the notebook
	m_notebookService->addNotebookEntry(&firstEntry, notebook::NotebookId(m_accountKey, key));
	dumpTodoFile();
}

void Service::onFileChanged(const QString &path)
{
	Q_UNUSED(path);
	dumpTodoFile();
}

unsigned int Service::getNotebook(const QString &name)
{
	QList<notebook::Notebook> notebooks = m_notebookService->notebooks();
	QList<notebook::Notebook>::iterator i;
	for (i = notebooks.begin(); i != notebooks.end(); i++) {
	    if ((*i).name() == name) {
	    	return (*i).id().notebookKey();
	    }
	}
	notebook::Notebook myNotebook;
	myNotebook.setName(name);
	m_notebookService->addNotebook(&myNotebook, m_accountKey);
	return myNotebook.id().notebookKey();
}

void Service::dumpTodoFile()
{
	QFile textfile(TODOTXT_FILE);
	if (!textfile.exists()) {
		qWarning() << "can't find todo.txt";
		return;
	}
	if (textfile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
	    QTextStream stream ( &textfile );
	    QString line;
	    do {
	        line = stream.readLine();
	        qDebug() << line;
	    } while (!line.isNull());
	}
	textfile.close();
}
