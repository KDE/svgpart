/*
    SPDX-FileCopyrightText: 2007 Aurélien Gâteau

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SVGPART_H
#define SVGPART_H

// KF
#include <KParts/ReadOnlyPart>

class SvgBrowserExtension;
class KPluginMetaData;
class QGraphicsScene;
class QGraphicsSvgItem;
class QGraphicsView;
class QSvgRenderer;

class SvgPart : public KParts::ReadOnlyPart
{
    Q_OBJECT

public:
    SvgPart(QWidget *parentWidget, QObject *parent, const KPluginMetaData &metaData, const QVariantList &);

    bool openUrl(const QUrl &url) override;
    bool closeUrl() override;

    void setExtendedRestoreArguments(qreal zoom);

    qreal zoom() const;
    int horizontalScrollPosition() const;
    int verticalScrollPosition() const;

protected:
    bool openFile() override;
    bool doOpenStream(const QString &mimeType) override;
    bool doWriteStream(const QByteArray &data) override;
    bool doCloseStream() override;

private Q_SLOTS:
    void zoomActualSize();
    void zoomIn();
    void zoomOut();

    void delayedRestoreViewState();

private:
    void setZoom(qreal value);

    void createViewForDocument();

private:
    QGraphicsScene *mScene;
    QGraphicsView *mView;
    QGraphicsSvgItem *mItem;
    QSvgRenderer *mRenderer;

    SvgBrowserExtension *m_browserExtension;

    bool mCloseUrlFromOpen = false;

    bool mHasExtendedRestoreArguments = false;
    qreal mRestoreZoom;

    QUrl mPreviousUrl;
    qreal mPreviousZoom = 1.0;
    int mPreviousHorizontalScrollPosition = 0;
    int mPreviousVerticalScrollPosition = 0;

    QByteArray mStreamedData;
};

#endif /* SVGPART_H */
