/*
 * Copyright (C) 2015 Simon Busch <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef DB8MODEL_H
#define DB8MODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>
#include <QJsonValue>
#include <QJsonArray>
#include <luna-service2++/handle.hpp>
#include <luna-service2++/call.hpp>

class Db8Model : public QAbstractListModel,
                 public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QString kind READ kind WRITE setKind NOTIFY kindChanged)
    Q_PROPERTY(QJsonValue query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(bool watch READ watch WRITE setWatch NOTIFY watchChanged)

public:
    explicit Db8Model(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString kind() const { return mKind; }
    void setKind(const QString &kind) { mKind = kind; }

    QJsonValue query() const { return mQuery; }
    void setQuery(const QJsonValue &query) { mQuery = query; }

    bool watch() const { return mWatch; }
    void setWatch(bool watch) { mWatch = watch; }

Q_SIGNALS:
    void kindChanged();
    void queryChanged();
    void watchChanged();

protected:
    virtual void classBegin();
    virtual void componentComplete();

private:
    bool mWatch;
    QString mKind;
    QJsonValue mQuery;
    LS::Handle mHandle;
    LS::Call mCurrentCall;
    QJsonArray mCurrentResults;

    void restart();
    void handleFailedDatabaseQuery(const QString &errorMessage);
    void processResults(const QJsonValue &results);

    static bool cbProcessResults(LSHandle *handle, LSMessage *message, void *context);
    static gboolean cbTriggerRestart(gpointer user_data);
};

#endif // DB8MODEL_H
