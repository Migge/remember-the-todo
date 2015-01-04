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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/system/InvokeManager>
#include <bb/pim/account/AccountService>
#include <bb/pim/notebook/NotebookServiceResult>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QString>
#include <QTextStream>

#include "todotxt/TodoItem.h"

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::pim::notebook;
using namespace bb::pim::account;

ApplicationUI::ApplicationUI(Application *app):
		QObject(app),
		m_translator(new QTranslator(this)),
		m_localeHandler(new LocaleHandler(this)),
		m_invokeManager(new InvokeManager(this)),
		m_pNotebookService(new NotebookService)
{
	// prepare the localization
	if (!QObject::connect(m_localeHandler, SIGNAL(systemLanguageChanged()),
			this, SLOT(onSystemLanguageChanged()))) {
		// This is an abnormal situation! Something went wrong!
		// Add own code to recover here
		qWarning() << "Recovering from a failed connect()";
	}

	// initial load
	onSystemLanguageChanged();

	// Create scene document from main.qml asset, the parent is set
	// to ensure the document gets destroyed properly at shut down.
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	// Make app available to the qml.
	qml->setContextProperty("app", this);

	// Create root object for the UI
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	// Set created root object as the application scene
	app->setScene(root);

	m_dropboxDirName = QDir::currentPath() + "/shared/Dropbox";
	m_todoDirName = m_dropboxDirName + "/todo2";
	m_todoFileName = m_todoDirName + "/todo.txt";
	m_cachedTodoFileName = QDir::homePath() + "/todo.txt";

	test();
}

ApplicationUI::~ApplicationUI()
{
    delete m_pNotebookService;
}

void ApplicationUI::onSystemLanguageChanged()
{
	QCoreApplication::instance()->removeTranslator(m_translator);
	// Initiate, load and install the application translation files.
	QString locale_string = QLocale().name();
	QString file_name = QString("RememberTheTodo_%1").arg(locale_string);
	if (m_translator->load(file_name, "app/native/qm")) {
		QCoreApplication::instance()->installTranslator(m_translator);
	}
}

void ApplicationUI::resendNotification()
{
	InvokeRequest request;
	request.setTarget("com.example.RememberTheTodoService");
	request.setAction("com.example.RememberTheTodoService.RESET");
	m_invokeManager->invoke(request);
	Application::instance()->minimize();
}


void ApplicationUI::test() {
    if (!hasDropboxDirectory()) {
        qWarning() << "No Dropbox directory; alternatively, there's a problem with the permissions.";
        return;
    }
    if (!hasTodoDirectory()) {
        qWarning() << "No todo directory, or a problem with the permissions. Create the directory?";
        return;
    }
    if (!hasTodoFile()) {
        qWarning() << "No todo.txt file, or problem with the permissions. Create the file?";
        return;
    }
    bool res = printTodoFile();
    if (!res) {
        qWarning() << "Error printing todo.txt file.";
    }
    if (!hasCachedTodoFile()) {
        qDebug() << "No cached todo file. Creating it...";
        if (!createCachedTodoFile()) {
            qWarning() << "Couldn't create cached todo.txt file, which is mandatory.";
            return;
        }
        initRTT();
    }
}

bool ApplicationUI::hasDropboxDirectory() const
{
    QFileInfo fileInfo(m_dropboxDirName);
    return fileInfo.exists() && fileInfo.isDir();
}

bool ApplicationUI::hasTodoDirectory() const
{
    QFileInfo fileInfo(m_todoDirName);
    return fileInfo.exists() && fileInfo.isDir() &&
            fileInfo.isReadable() && fileInfo.isWritable() && fileInfo.isExecutable();
}

bool ApplicationUI::hasTodoFile() const
{
    QFileInfo fileInfo(m_todoFileName);
    return fileInfo.exists() && fileInfo.isFile() && fileInfo.isReadable() && fileInfo.isWritable();
}

bool ApplicationUI::hasCachedTodoFile() const
{
    QFileInfo fileInfo(m_cachedTodoFileName);
    return fileInfo.exists() && fileInfo.isFile() && fileInfo.isReadable() && fileInfo.isWritable();
}

bool ApplicationUI::createCachedTodoFile() const
{
    return QFile::copy(m_todoFileName, m_cachedTodoFileName);
}

bool ApplicationUI::printTodoFile() const
{
    QFile file(m_todoFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }

    return true;
}

QString ApplicationUI::getCachedTodoFile() const
{
    QFile file(m_cachedTodoFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    QTextStream in(&file);
    return in.readAll();
}

void ApplicationUI::initRTT()
{
    QString rawData = getCachedTodoFile();
    RTT::TodoList todoList;
    todoList.buildList(rawData);
    initNotebooks(todoList);
}

void ApplicationUI::initNotebooks(RTT::TodoList todoList)
{
    QList<Notebook> notebooks = m_pNotebookService->notebooks();

    QList<Notebook>::iterator i;
    m_notebookMap.clear();
    for (i = notebooks.begin(); i != notebooks.end(); i++) {
        Notebook *notebook = &(*i);
        if(isValidNotebook(notebook)) {
            QString name = notebook->name();
            qDebug() << name;
            m_notebookMap[name] = notebook->id();
        }
    }

    for (int i=0; i<todoList.size(); i++) {
        RTT::TodoItem item = todoList[i];
        QString context = item.getContext();
        if (context.isEmpty()) {
            qDebug() << "Item has no context.";
            // TODO: Add to unsorted.
        } else if (m_notebookMap.contains(context)) {
            qDebug() << "Foldern " << context << " fanns redan.";
        } else {
            qDebug() << "Foldern " << context << " fanns inte.";
            createNotebook(context);
        }
    }

    /*
    NotebookService service;
    Notebook defaultNotebook = service.defaultNotebook();
    NotebookEntryFilter filter;
    filter.setParentNotebookId( defaultNotebook.id() );
    filter.setStatus(NotebookEntryStatus::NotCompleted);
    QList<NotebookEntry> entries = service.notebookEntries( filter );
    for (int i=0; i<entries.size(); i++) {
        NotebookEntry entry = entries[i];
        qDebug() << "Task: " << entry.title();
    }
    NotebookEntry entry;
    entry.setTitle( "New NotebookEntry" );
    entry.setStatus( NotebookEntryStatus::NotCompleted );
    entry.setDueDateTime( QDateTime::currentDateTime().addDays( 1 ) );
    NotebookId notebookId = service.defaultNotebook().id();
    */

    // You should be sure to check the return code from addNotebookEntry() for
    // success
    //service.addNotebookEntry( &entry, notebookId );

}

bool ApplicationUI::isValidNotebook(const Notebook *notebook) const
{
    const QChar firstChar =
            (notebook->name().length() > 0) ? notebook->name().at(0) : '.';
    return notebook->isValid() && notebook->type() == Notebook::Generic &&
            firstChar == QChar('@');
}

bool ApplicationUI::createNotebook(const QString& name)
{
    AccountKey accountKey =
            AccountService().defaultAccount(Service::Notebook).id();
    Notebook notebook;
    notebook.setName(name);

    NotebookServiceResult::Type res =
            m_pNotebookService->addNotebook(&notebook, accountKey);
    if (res != NotebookServiceResult::Success) {
        qWarning() << "Couldn't create notebook due to: "
                   << parseNotebookServiceResult(res);
        return false;
    }

    m_notebookMap[name] = notebook.id();
    return true;
}

QString ApplicationUI::parseNotebookServiceResult(NotebookServiceResult::Type res) const
{
    QString str = "";
    switch (res) {
        case NotebookServiceResult::InaccessibleAccount:
            str = "Inaccessible account.";
            break;
        // TODO: Uncomment below for 10.3
//        case NotebookServiceResult::DomainLockedError:
//            str = "Domain locked.";
//            break;
//        case NotebookServiceResult::NotebookNotSupported:
//            str = "Notebook not supported.";
//            break;
        case NotebookServiceResult::InternalError:
        default:
            str = "Internal error.";
    }
    return str;
}
