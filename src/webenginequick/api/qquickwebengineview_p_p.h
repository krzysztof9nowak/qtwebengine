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

#ifndef QQUICKWEBENGINEVIEW_P_P_H
#define QQUICKWEBENGINEVIEW_P_P_H

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

#include "qquickwebengineview_p.h"
#include "qquickwebenginescriptcollection.h"
#include "render_view_context_menu_qt.h"
#include "touch_handle_drawable_client.h"
#include "web_contents_adapter_client.h"

#include <QPointer>
#include <QScopedPointer>
#include <QSharedData>
#include <QString>
#include <QtCore/qcompilerdetection.h>
#include <QtGui/qaccessibleobject.h>

namespace QtWebEngineCore {
class RenderWidgetHostViewQtDelegateQuick;
class TouchHandleDrawableClient;
class TouchSelectionMenuController;
class UIDelegatesManager;
class WebContentsAdapter;
}

QT_BEGIN_NAMESPACE
class QQuickWebEngineView;
class QQmlComponent;
class QQmlContext;
class QWebEngineContextMenuRequest;
class QQuickWebEngineSettings;
class QQuickWebEngineFaviconProvider;
class QQuickWebEngineProfilePrivate;
class QQuickWebEngineTouchHandleProvider;
class QWebEngineFindTextResult;
class QWebEngineHistory;

#if QT_CONFIG(webenginequick_testsupport)
class QQuickWebEngineTestSupport;
#endif

class Q_WEBENGINE_PRIVATE_EXPORT QQuickWebEngineViewPrivate : public QtWebEngineCore::WebContentsAdapterClient
{
public:
    Q_DECLARE_PUBLIC(QQuickWebEngineView)
    QQuickWebEngineView *q_ptr;
    QQuickWebEngineViewPrivate();
    ~QQuickWebEngineViewPrivate();
    void releaseProfile() override;
    void initializeProfile();
    QtWebEngineCore::UIDelegatesManager *ui();

    QtWebEngineCore::RenderWidgetHostViewQtDelegate* CreateRenderWidgetHostViewQtDelegate(QtWebEngineCore::RenderWidgetHostViewQtDelegateClient *client) override;
    QtWebEngineCore::RenderWidgetHostViewQtDelegate* CreateRenderWidgetHostViewQtDelegateForPopup(QtWebEngineCore::RenderWidgetHostViewQtDelegateClient *client) override;
    void initializationFinished() override;
    void lifecycleStateChanged(LifecycleState state) override;
    void recommendedStateChanged(LifecycleState state) override;
    void visibleChanged(bool visible) override;
    void titleChanged(const QString&) override;
    void urlChanged() override;
    void iconChanged(const QUrl&) override;
    void loadProgressChanged(int progress) override;
    void didUpdateTargetURL(const QUrl&) override;
    void selectionChanged() override;
    void recentlyAudibleChanged(bool recentlyAudible) override;
    void renderProcessPidChanged(qint64 pid) override;
    QRectF viewportRect() const override;
    QColor backgroundColor() const override;
    void loadStarted(QWebEngineLoadingInfo info) override;
    void loadCommitted() override;
    void didFirstVisuallyNonEmptyPaint() override;
    void loadFinished(QWebEngineLoadingInfo info) override;
    void focusContainer() override;
    void unhandledKeyEvent(QKeyEvent *event) override;
    QSharedPointer<QtWebEngineCore::WebContentsAdapter>
    adoptNewWindow(QSharedPointer<QtWebEngineCore::WebContentsAdapter> newWebContents,
                   WindowOpenDisposition disposition, bool userGesture, const QRect &,
                   const QUrl &targetUrl) override;
    bool isBeingAdopted() override;
    void close() override;
    void windowCloseRejected() override;
    void requestFullScreenMode(const QUrl &origin, bool fullscreen) override;
    bool isFullScreenMode() const override;
    void contextMenuRequested(QWebEngineContextMenuRequest *request) override;
    void navigationRequested(int navigationType, const QUrl &url, int &navigationRequestAction, bool isMainFrame) override;
    void javascriptDialog(QSharedPointer<QtWebEngineCore::JavaScriptDialogController>) override;
    void runFileChooser(QSharedPointer<QtWebEngineCore::FilePickerController>) override;
    void showColorDialog(QSharedPointer<QtWebEngineCore::ColorChooserController>) override;
    void didRunJavaScript(quint64, const QVariant&) override;
    void didFetchDocumentMarkup(quint64, const QString&) override { }
    void didFetchDocumentInnerText(quint64, const QString&) override { }
    void didPrintPage(quint64 requestId, QSharedPointer<QByteArray>) override;
    void didPrintPageToPdf(const QString &filePath, bool success) override;
    bool passOnFocus(bool reverse) override;
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID) override;
    void authenticationRequired(QSharedPointer<QtWebEngineCore::AuthenticationDialogController>) override;
    void runMediaAccessPermissionRequest(const QUrl &securityOrigin, MediaRequestFlags requestFlags) override;
    void runMouseLockPermissionRequest(const QUrl &securityOrigin) override;
    void runQuotaRequest(QWebEngineQuotaRequest) override;
    void runRegisterProtocolHandlerRequest(QWebEngineRegisterProtocolHandlerRequest) override;
    QObject *accessibilityParentObject() override;
    QWebEngineSettings *webEngineSettings() const override;
    void allowCertificateError(const QWebEngineCertificateError &error) override;
    void selectClientCert(const QSharedPointer<QtWebEngineCore::ClientCertSelectController>
                                  &selectController) override;
    void runFeaturePermissionRequest(QtWebEngineCore::ProfileAdapter::PermissionType permission, const QUrl &securityOrigin) override;
    void renderProcessTerminated(RenderProcessTerminationStatus terminationStatus, int exitCode) override;
    void requestGeometryChange(const QRect &geometry, const QRect &frameGeometry) override;
    void updateScrollPosition(const QPointF &position) override;
    void updateContentsSize(const QSizeF &size) override;
    void updateNavigationActions() override;
    void updateEditActions() override;
    QObject *dragSource() const override;
    bool isEnabled() const override;
    void setToolTip(const QString &toolTipText) override;
    QtWebEngineCore::TouchHandleDrawableClient *createTouchHandle(const QMap<int, QImage> &images) override;
    void showTouchSelectionMenu(QtWebEngineCore::TouchSelectionMenuController *, const QRect &, const QSize &) override;
    void hideTouchSelectionMenu() override;
    const QObject *holdingQObject() const override;
    ClientType clientType() override { return QtWebEngineCore::WebContentsAdapterClient::QmlClient; }

    QtWebEngineCore::ProfileAdapter *profileAdapter() override;
    QtWebEngineCore::WebContentsAdapter *webContentsAdapter() override;
    void printRequested() override;
    void findTextFinished(const QWebEngineFindTextResult &result) override;

    void didCompositorFrameSwap();

    void updateAction(QQuickWebEngineView::WebAction) const;
    void adoptWebContents(QtWebEngineCore::WebContentsAdapter *webContents);
    void setProfile(QQuickWebEngineProfile *profile);
    void updateAdapter();
    void ensureContentsAdapter();
    void setFullScreenMode(bool);

    static void bindViewAndWidget(QQuickWebEngineView *view, QtWebEngineCore::RenderWidgetHostViewQtDelegateQuick *widget);
    void widgetChanged(QtWebEngineCore::RenderWidgetHostViewQtDelegateQuick *oldWidget,
                       QtWebEngineCore::RenderWidgetHostViewQtDelegateQuick *newWidget);

    QQuickWebEngineProfile *m_profile;
    QSharedPointer<QtWebEngineCore::WebContentsAdapter> adapter;
    QScopedPointer<QWebEngineHistory> m_history;
    QScopedPointer<QQuickWebEngineSettings> m_settings;
#if QT_CONFIG(webenginequick_testsupport)
    QQuickWebEngineTestSupport *m_testSupport;
#endif
    QQmlComponent *contextMenuExtraItems;
    QUrl m_url;
    QString m_html;
    QUrl iconUrl;
    int loadProgress;
    bool m_fullscreenMode;
    bool isLoading;
    bool m_activeFocusOnPress;
    bool m_navigationActionTriggered;
    qreal devicePixelRatio;
    QMap<quint64, QJSValue> m_callbacks;
    QQmlWebChannel *m_webChannel;
    QPointer<QQuickWebEngineView> inspectedView;
    QPointer<QQuickWebEngineView> devToolsView;
    uint m_webChannelWorld;
    bool m_defaultAudioMuted;
    bool m_isBeingAdopted;
    mutable QQuickWebEngineAction *actions[QQuickWebEngineView::WebActionCount];
    QtWebEngineCore::RenderWidgetHostViewQtDelegateQuick *widget = nullptr;

    bool profileInitialized() const;

private:
    enum LoadVisuallyCommittedState {
        NotCommitted,
        DidFirstVisuallyNonEmptyPaint,
        DidFirstCompositorFrameSwap
    };

    QScopedPointer<QtWebEngineCore::UIDelegatesManager> m_uIDelegatesManager;
    QColor m_backgroundColor;
    qreal m_zoomFactor;
    bool m_ui2Enabled;
    bool m_profileInitialized;
    QWebEngineContextMenuRequest *m_contextMenuRequest;
    LoadVisuallyCommittedState m_loadVisuallyCommittedState = NotCommitted;
    QScopedPointer<QQuickWebEngineScriptCollection> m_scriptCollection;
    QQuickWebEngineFaviconProvider *m_faviconProvider = nullptr;
};

#ifndef QT_NO_ACCESSIBILITY
class QQuickWebEngineViewAccessible : public QAccessibleObject
{
public:
    QQuickWebEngineViewAccessible(QQuickWebEngineView *o);
    bool isValid() const override;
    QAccessibleInterface *parent() const override;
    QAccessibleInterface *focusChild() const override;
    int childCount() const override;
    QAccessibleInterface *child(int index) const override;
    int indexOfChild(const QAccessibleInterface*) const override;
    QString text(QAccessible::Text) const override;
    QAccessible::Role role() const override;
    QAccessible::State state() const override;

private:
    QQuickWebEngineView *engineView() const { return static_cast<QQuickWebEngineView*>(object()); }
};
#endif // QT_NO_ACCESSIBILITY

class QQuickContextMenuBuilder : public QtWebEngineCore::RenderViewContextMenuQt
{
public:
    QQuickContextMenuBuilder(QWebEngineContextMenuRequest *data, QQuickWebEngineView *view,
                             QObject *menu);
    void appendExtraItems(QQmlEngine *engine);

private:
    virtual bool hasInspector() override;
    virtual bool isFullScreenMode() override;

    virtual void addMenuItem(ContextMenuItem menuItem) override;
    virtual bool isMenuItemEnabled(ContextMenuItem menuItem) override;

    QQuickWebEngineView *m_view;
    QObject *m_menu;
};

class Q_WEBENGINE_PRIVATE_EXPORT QQuickWebEngineTouchHandle : public QtWebEngineCore::TouchHandleDrawableClient {
public:
    QQuickWebEngineTouchHandle(QtWebEngineCore::UIDelegatesManager *ui, const QMap<int, QImage> &images);

    void setImage(int orientation) override;
    void setBounds(const QRect &bounds) override;
    void setVisible(bool visible) override;
    void setOpacity(float opacity) override;

private:
    QScopedPointer<QQuickItem> m_item;
};

QT_END_NAMESPACE

#endif // QQUICKWEBENGINEVIEW_P_P_H
