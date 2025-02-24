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

#ifndef QWEBENGINEVIEW_H
#define QWEBENGINEVIEW_H

#include <QtGui/qpainter.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtWidgets/qwidget.h>

#include <QtWebEngineWidgets/qtwebenginewidgetsglobal.h>
#include <QtWebEngineCore/qwebenginecallback.h>
#include <QtWebEngineCore/qwebenginecontextmenurequest.h>
#include <QtWebEngineCore/qwebenginehttprequest.h>
#include <QtWebEngineCore/qwebenginepage.h>

QT_BEGIN_NAMESPACE
class QContextMenuEvent;
class QPrinter;
class QUrl;
class QWebEnginePage;
class QWebEngineSettings;
class QWebEngineViewAccessible;
class QWebEngineViewPrivate;

class QWEBENGINEWIDGETS_EXPORT QWebEngineView : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    Q_PROPERTY(QUrl iconUrl READ iconUrl NOTIFY iconUrlChanged)
    Q_PROPERTY(QIcon icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString selectedText READ selectedText)
    Q_PROPERTY(bool hasSelection READ hasSelection)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit QWebEngineView(QWidget *parent = nullptr);
    virtual ~QWebEngineView();

    QWebEnginePage* page() const;
    void setPage(QWebEnginePage* page);

    void load(const QUrl &url);
    void load(const QWebEngineHttpRequest &request);
    void setHtml(const QString& html, const QUrl& baseUrl = QUrl());
    void setContent(const QByteArray& data, const QString& mimeType = QString(), const QUrl& baseUrl = QUrl());

    QWebEngineHistory* history() const;

    QString title() const;
    void setUrl(const QUrl &url);
    QUrl url() const;
    QUrl iconUrl() const;
    QIcon icon() const;

    bool hasSelection() const;
    QString selectedText() const;

#ifndef QT_NO_ACTION
    QAction* pageAction(QWebEnginePage::WebAction action) const;
#endif
    void triggerPageAction(QWebEnginePage::WebAction action, bool checked = false);

    qreal zoomFactor() const;
    void setZoomFactor(qreal factor);
    void findText(const QString &subString, QWebEnginePage::FindFlags options = {}, const std::function<void(bool)> &resultCallback = std::function<void(bool)>());

    QSize sizeHint() const override;
    QWebEngineSettings *settings() const;

#if QT_CONFIG(menu)
    QMenu *createStandardContextMenu();
#endif
    QWebEngineContextMenuRequest *lastContextMenuRequest() const;

    void printToPdf(const QString &filePath, const QPageLayout &layout = QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF()));
    void printToPdf(const QWebEngineCallback<const QByteArray&> &resultCallback, const QPageLayout &layout = QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF()));
    void print(QPrinter *printer);

public Q_SLOTS:
    void stop();
    void back();
    void forward();
    void reload();

Q_SIGNALS:
    void loadStarted();
    void loadProgress(int progress);
    void loadFinished(bool);
    void titleChanged(const QString& title);
    void selectionChanged();
    void urlChanged(const QUrl&);
    void iconUrlChanged(const QUrl&);
    void iconChanged(const QIcon&);
    void renderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus,
                             int exitCode);
    void pdfPrintingFinished(const QString &filePath, bool success);
    void printRequested();
    void printFinished(bool success);

protected:
    virtual QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
#if QT_CONFIG(contextmenu)
    void contextMenuEvent(QContextMenuEvent*) override;
#endif // QT_CONFIG(contextmenu)
    bool event(QEvent*) override;
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
    void closeEvent(QCloseEvent *) override;
#if QT_CONFIG(draganddrop)
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragLeaveEvent(QDragLeaveEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
#endif // QT_CONFIG(draganddrop)

private:
    Q_DISABLE_COPY(QWebEngineView)
    Q_DECLARE_PRIVATE(QWebEngineView)
    QScopedPointer<QWebEngineViewPrivate> d_ptr;

    friend class QWebEnginePage;
    friend class QWebEnginePagePrivate;
#if QT_CONFIG(accessibility)
    friend class QWebEngineViewAccessible;
#endif
};

QT_END_NAMESPACE

#endif // QWEBENGINEVIEW_H
