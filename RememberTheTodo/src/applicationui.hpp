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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

#include <bb/pim/notebook/NotebookService>

#include "todotxt/TodoList.h"

namespace bb {
	namespace cascades {
		class Application;
		class LocaleHandler;
	}
	namespace system {
		class InvokeManager;
	}
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI: public QObject {
	Q_OBJECT
public:
	ApplicationUI(bb::cascades::Application *app);
	virtual ~ApplicationUI();

	Q_INVOKABLE	void resendNotification();

private slots:
	void onSystemLanguageChanged();

private:
	QTranslator* m_translator;
	bb::cascades::LocaleHandler* m_localeHandler;
	bb::system::InvokeManager* m_invokeManager;

	bb::pim::notebook::NotebookService* m_pNotebookService;

	QString m_dropboxDirName;
	QString m_todoDirName;
	QString m_todoFileName;
	QString m_cachedTodoFileName;

	QMap<QString,bb::pim::notebook::NotebookId> m_notebookMap;

	void test();
	bool hasDropboxDirectory() const;
	bool hasTodoDirectory() const;
	bool hasTodoFile() const;
	bool hasCachedTodoFile() const;
	bool createCachedTodoFile() const;
	bool printTodoFile() const;

	QString getCachedTodoFile() const;
	void initRTT();
	void initNotebooks(RTT::TodoList todoList);
	bool isValidNotebook(const bb::pim::notebook::Notebook *notebook) const;
	bool createNotebook(const QString &name);
	QString parseNotebookServiceResult(bb::pim::notebook::NotebookServiceResult::Type res) const;
};

#endif /* ApplicationUI_HPP_ */
