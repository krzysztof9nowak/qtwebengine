/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
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

#ifndef QQUICKWEBENGINEACTION_P_H
#define QQUICKWEBENGINEACTION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QObject>
#include <QtQml/qqml.h>
#include "qtwebenginequickglobal_p.h"
#include <QVariant>

namespace QtWebEngineCore {
    class UIDelegatesManager;
    class UI2DelegatesManager;
}

QT_BEGIN_NAMESPACE

class QQuickWebEngineActionPrivate;

class Q_WEBENGINE_EXPORT QQuickWebEngineAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT FINAL)
    Q_PROPERTY(QString iconName READ iconName CONSTANT FINAL)
    Q_PROPERTY(bool enabled READ isEnabled NOTIFY enabledChanged FINAL)

public:
    QQuickWebEngineAction(const QVariant &data, const QString &text, const QString &iconName, bool enabled, QObject *parent);
    QQuickWebEngineAction(QObject *parent);
    ~QQuickWebEngineAction();

    QString text() const;
    QString iconName() const;
    bool isEnabled() const;

public Q_SLOTS:
    Q_INVOKABLE void trigger();

Q_SIGNALS:
    void triggered();
    void enabledChanged();

private:
    Q_DECLARE_PRIVATE(QQuickWebEngineAction)
    friend class QQuickWebEngineView;
    friend class QQuickWebEngineViewPrivate;
    friend class QtWebEngineCore::UIDelegatesManager;
    friend class QtWebEngineCore::UI2DelegatesManager;
    friend class QQuickContextMenuBuilder;

    QScopedPointer<QQuickWebEngineActionPrivate> d_ptr;
};


QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickWebEngineAction)

#endif // QQUICKWEBENGINEACTION_P_H
