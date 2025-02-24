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

#ifndef QWEBENGINEPAGE_H
#define QWEBENGINEPAGE_H

#include <QtWebEngineCore/qtwebenginecoreglobal.h>
#include <QtWebEngineCore/qwebengineclientcertificateselection.h>
#include <QtWebEngineCore/qwebenginedownloadrequest.h>
#include <QtWebEngineCore/qwebenginehttprequest.h>

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtCore/qvariant.h>
#include <QtGui/qpagelayout.h>
#include <QtGui/qaction.h>
#include <QtNetwork/qnetworkaccessmanager.h>

#include <functional>

QT_BEGIN_NAMESPACE
class QMenu;

class QContextMenuBuilder;
class QWebChannel;
class QWebEngineCertificateError;
class QWebEngineClientCertificateSelection;
class QWebEngineFindTextResult;
class QWebEngineFullScreenRequest;
class QWebEngineHistory;
class QWebEngineLoadingInfo;
class QWebEngineNavigationRequest;
class QWebEngineNewWindowRequest;
class QWebEnginePage;
class QWebEnginePagePrivate;
class QWebEngineProfile;
class QWebEngineQuotaRequest;
class QWebEngineRegisterProtocolHandlerRequest;
class QWebEngineScriptCollection;
class QWebEngineSettings;
class QWebEngineUrlRequestInterceptor;

class Q_WEBENGINECORE_EXPORT QWebEnginePage : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString selectedText READ selectedText)
    Q_PROPERTY(bool hasSelection READ hasSelection)
    Q_PROPERTY(QUrl requestedUrl READ requestedUrl)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    Q_PROPERTY(QUrl iconUrl READ iconUrl NOTIFY iconUrlChanged)
    Q_PROPERTY(QIcon icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QSizeF contentsSize READ contentsSize NOTIFY contentsSizeChanged)
    Q_PROPERTY(QPointF scrollPosition READ scrollPosition NOTIFY scrollPositionChanged)
    Q_PROPERTY(bool audioMuted READ isAudioMuted WRITE setAudioMuted NOTIFY audioMutedChanged)
    Q_PROPERTY(bool recentlyAudible READ recentlyAudible NOTIFY recentlyAudibleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(LifecycleState lifecycleState READ lifecycleState WRITE setLifecycleState NOTIFY lifecycleStateChanged)
    Q_PROPERTY(LifecycleState recommendedState READ recommendedState NOTIFY recommendedStateChanged)
    Q_PROPERTY(qint64 renderProcessPid READ renderProcessPid NOTIFY renderProcessPidChanged)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged FINAL)

public:
    enum WebAction {
        NoWebAction = - 1,
        Back,
        Forward,
        Stop,
        Reload,

        Cut,
        Copy,
        Paste,

        Undo,
        Redo,
        SelectAll,
        ReloadAndBypassCache,

        PasteAndMatchStyle,

        OpenLinkInThisWindow,
        OpenLinkInNewWindow,
        OpenLinkInNewTab,
        CopyLinkToClipboard,
        DownloadLinkToDisk,

        CopyImageToClipboard,
        CopyImageUrlToClipboard,
        DownloadImageToDisk,

        CopyMediaUrlToClipboard,
        ToggleMediaControls,
        ToggleMediaLoop,
        ToggleMediaPlayPause,
        ToggleMediaMute,
        DownloadMediaToDisk,

        InspectElement,
        ExitFullScreen,
        RequestClose,
        Unselect,
        SavePage,
        OpenLinkInNewBackgroundTab,
        ViewSource,

        ToggleBold,
        ToggleItalic,
        ToggleUnderline,
        ToggleStrikethrough,

        AlignLeft,
        AlignCenter,
        AlignRight,
        AlignJustified,
        Indent,
        Outdent,

        InsertOrderedList,
        InsertUnorderedList,

        WebActionCount
    };
    Q_ENUM(WebAction)

    enum FindFlag {
        FindBackward = 1,
        FindCaseSensitively = 2,
    };
    Q_DECLARE_FLAGS(FindFlags, FindFlag)

    enum WebWindowType {
        WebBrowserWindow,
        WebBrowserTab,
        WebDialog,
        WebBrowserBackgroundTab
    };
    Q_ENUM(WebWindowType)

    enum PermissionPolicy {
        PermissionUnknown,
        PermissionGrantedByUser,
        PermissionDeniedByUser
    };
    Q_ENUM(PermissionPolicy)

    // must match WebContentsAdapterClient::NavigationType
    enum NavigationType {
        NavigationTypeLinkClicked,
        NavigationTypeTyped,
        NavigationTypeFormSubmitted,
        NavigationTypeBackForward,
        NavigationTypeReload,
        NavigationTypeOther,
        NavigationTypeRedirect,
    };
    Q_ENUM(NavigationType)

    enum Feature {
        Notifications = 0,
        Geolocation = 1,
        MediaAudioCapture = 2,
        MediaVideoCapture,
        MediaAudioVideoCapture,
        MouseLock,
        DesktopVideoCapture,
        DesktopAudioVideoCapture
    };
    Q_ENUM(Feature)

    // Ex-QWebFrame enum

    enum FileSelectionMode {
        FileSelectOpen,
        FileSelectOpenMultiple,
        FileSelectUploadFolder,
    };
    Q_ENUM(FileSelectionMode)

    // must match WebContentsAdapterClient::JavaScriptConsoleMessageLevel
    enum JavaScriptConsoleMessageLevel {
        InfoMessageLevel = 0,
        WarningMessageLevel,
        ErrorMessageLevel
    };
    Q_ENUM(JavaScriptConsoleMessageLevel)

    // must match WebContentsAdapterClient::RenderProcessTerminationStatus
    enum RenderProcessTerminationStatus {
        NormalTerminationStatus = 0,
        AbnormalTerminationStatus,
        CrashedTerminationStatus,
        KilledTerminationStatus
    };
    Q_ENUM(RenderProcessTerminationStatus)

    // must match WebContentsAdapterClient::LifecycleState
    enum class LifecycleState {
        Active,
        Frozen,
        Discarded,
    };
    Q_ENUM(LifecycleState)

    explicit QWebEnginePage(QObject *parent = nullptr);
    QWebEnginePage(QWebEngineProfile *profile, QObject *parent = nullptr);
    ~QWebEnginePage();
    QWebEngineHistory *history() const;

    bool hasSelection() const;
    QString selectedText() const;

    QWebEngineProfile *profile() const;

#ifndef QT_NO_ACTION
    QAction *action(WebAction action) const;
#endif
    virtual void triggerAction(WebAction action, bool checked = false);

    void replaceMisspelledWord(const QString &replacement);

    bool event(QEvent*) override;

    void findText(const QString &subString, FindFlags options = {}, const std::function<void(bool)> &resultCallback = std::function<void(bool)>());

    void setFeaturePermission(const QUrl &securityOrigin, Feature feature, PermissionPolicy policy);

    bool isLoading() const;

    void load(const QUrl &url);
    void load(const QWebEngineHttpRequest &request);
    void download(const QUrl &url, const QString &filename = QString());
    void setHtml(const QString &html, const QUrl &baseUrl = QUrl());
    void setContent(const QByteArray &data, const QString &mimeType = QString(), const QUrl &baseUrl = QUrl());

    void toHtml(const std::function<void(const QString &)> &resultCallback) const;
    void toPlainText(const std::function<void(const QString &)> &resultCallback) const;

    QString title() const;
    void setUrl(const QUrl &url);
    QUrl url() const;
    QUrl requestedUrl() const;
    QUrl iconUrl() const;
    QIcon icon() const;

    qreal zoomFactor() const;
    void setZoomFactor(qreal factor);

    QPointF scrollPosition() const;
    QSizeF contentsSize() const;

    void runJavaScript(const QString& scriptSource);
    void runJavaScript(const QString& scriptSource, quint32 worldId);
    void runJavaScript(const QString& scriptSource, const std::function<void(const QVariant &)> &resultCallback);
    void runJavaScript(const QString& scriptSource, quint32 worldId, const std::function<void(const QVariant &)> &resultCallback);
    QWebEngineScriptCollection &scripts();
    QWebEngineSettings *settings() const;

    QWebChannel *webChannel() const;
    void setWebChannel(QWebChannel *);
    void setWebChannel(QWebChannel *, uint worldId);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    void save(const QString &filePath, QWebEngineDownloadRequest::SavePageFormat format
                                                = QWebEngineDownloadRequest::MimeHtmlSaveFormat) const;

    bool isAudioMuted() const;
    void setAudioMuted(bool muted);
    bool recentlyAudible() const;
    qint64 renderProcessPid() const;

    void setInspectedPage(QWebEnginePage *page);
    QWebEnginePage *inspectedPage() const;
    void setDevToolsPage(QWebEnginePage *page);
    QWebEnginePage *devToolsPage() const;

    void setUrlRequestInterceptor(QWebEngineUrlRequestInterceptor *interceptor);

    LifecycleState lifecycleState() const;
    void setLifecycleState(LifecycleState state);

    LifecycleState recommendedState() const;

    bool isVisible() const;
    void setVisible(bool visible);

    void acceptAsNewWindow(QWebEngineNewWindowRequest &request);

    static QWebEnginePage* fromDownloadRequest(QWebEngineDownloadRequest * request);

Q_SIGNALS:
    void loadStarted();
    void loadProgress(int progress);
    void loadFinished(bool ok);
    void loadingChanged(const QWebEngineLoadingInfo &loadingInfo);

    void linkHovered(const QString &url);
    void selectionChanged();
    void geometryChangeRequested(const QRect& geom);
    void windowCloseRequested();

    void featurePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
    void featurePermissionRequestCanceled(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
    void fullScreenRequested(QWebEngineFullScreenRequest fullScreenRequest);
    void quotaRequested(QWebEngineQuotaRequest quotaRequest);
    void registerProtocolHandlerRequested(QWebEngineRegisterProtocolHandlerRequest request);
    void selectClientCertificate(QWebEngineClientCertificateSelection clientCertSelection);
    void authenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QUrl &requestUrl, QAuthenticator *authenticator, const QString &proxyHost);

    void renderProcessTerminated(RenderProcessTerminationStatus terminationStatus, int exitCode);
    void certificateError(const QWebEngineCertificateError &certificateError);
    bool navigationRequested(QWebEngineNavigationRequest &request);
    void newWindowRequested(QWebEngineNewWindowRequest &request);

    // Ex-QWebFrame signals
    void titleChanged(const QString &title);
    void urlChanged(const QUrl &url);
    void iconUrlChanged(const QUrl &url);
    void iconChanged(const QIcon &icon);

    void scrollPositionChanged(const QPointF &position);
    void contentsSizeChanged(const QSizeF &size);
    void audioMutedChanged(bool muted);
    void recentlyAudibleChanged(bool recentlyAudible);
    void renderProcessPidChanged(qint64 pid);

    void visibleChanged(bool visible);

    void lifecycleStateChanged(LifecycleState state);
    void recommendedStateChanged(LifecycleState state);

    void findTextFinished(const QWebEngineFindTextResult &result);

    // TODO: fixme / rewrite bindPageToView
    void _q_aboutToDelete();

protected:
    virtual QWebEnginePage *createWindow(WebWindowType type);
    virtual QStringList chooseFiles(FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes);
    virtual void javaScriptAlert(const QUrl &securityOrigin, const QString& msg);
    virtual bool javaScriptConfirm(const QUrl &securityOrigin, const QString& msg);
    virtual bool javaScriptPrompt(const QUrl &securityOrigin, const QString& msg, const QString& defaultValue, QString* result);
    virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID);
    virtual bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);

private:
    Q_DISABLE_COPY(QWebEnginePage)
    Q_DECLARE_PRIVATE(QWebEnginePage)
    QScopedPointer<QWebEnginePagePrivate> d_ptr;
#ifndef QT_NO_ACTION
    Q_PRIVATE_SLOT(d_func(), void _q_webActionTriggered(bool checked))
#endif

    friend class QContextMenuBuilder;
    friend class QWebEngineFullScreenRequest;
    friend class QWebEngineView;
    friend class QWebEngineViewPrivate;
#ifndef QT_NO_ACCESSIBILITY
    friend class QWebEngineViewAccessible;
#endif // QT_NO_ACCESSIBILITY
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QWebEnginePage::FindFlags)

Q_WEBENGINECORE_EXPORT QDataStream &operator<<(QDataStream &stream,
                                                 const QWebEngineHistory &history);
Q_WEBENGINECORE_EXPORT QDataStream &operator>>(QDataStream &stream, QWebEngineHistory &history);

QT_END_NAMESPACE

#endif // QWEBENGINEPAGE_H
