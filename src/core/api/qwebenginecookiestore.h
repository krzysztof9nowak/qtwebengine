/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWEBENGINECOOKIESTORE_H
#define QWEBENGINECOOKIESTORE_H

#include <QtWebEngineCore/qtwebenginecoreglobal.h>

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qurl.h>
#include <QtNetwork/qnetworkcookie.h>

#include <functional>

namespace QtWebEngineCore {
class ContentBrowserClientQt;
class CookieMonsterDelegateQt;
class ProfileAdapter;
class RestrictedCookieManagerQt;
} // namespace QtWebEngineCore

QT_BEGIN_NAMESPACE

class QWebEngineCookieStorePrivate;
class Q_WEBENGINECORE_EXPORT QWebEngineCookieStore : public QObject {
    Q_OBJECT

public:
    struct FilterRequest {
        QUrl firstPartyUrl;
        QUrl origin;
        bool thirdParty;
        bool _reservedFlag;
        ushort _reservedType;
    };
    virtual ~QWebEngineCookieStore();

    void setCookieFilter(const std::function<bool(const FilterRequest &)> &filterCallback);
    void setCookieFilter(std::function<bool(const FilterRequest &)> &&filterCallback);
    void setCookie(const QNetworkCookie &cookie, const QUrl &origin = QUrl());
    void deleteCookie(const QNetworkCookie &cookie, const QUrl &origin = QUrl());
    void deleteSessionCookies();
    void deleteAllCookies();
    void loadAllCookies();

Q_SIGNALS:
    void cookieAdded(const QNetworkCookie &cookie);
    void cookieRemoved(const QNetworkCookie &cookie);

private:
    explicit QWebEngineCookieStore(QObject *parent = nullptr);
    friend class QtWebEngineCore::ContentBrowserClientQt;
    friend class QtWebEngineCore::CookieMonsterDelegateQt;
    friend class QtWebEngineCore::ProfileAdapter;
    friend class QtWebEngineCore::RestrictedCookieManagerQt;
    Q_DISABLE_COPY(QWebEngineCookieStore)
    Q_DECLARE_PRIVATE(QWebEngineCookieStore)
    QScopedPointer<QWebEngineCookieStorePrivate> d_ptr;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QWebEngineCookieStore *)

#endif // QWEBENGINECOOKIESTORE_H
