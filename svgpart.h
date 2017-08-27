/*
Copyright 2007 Aurélien Gâteau

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef SVGPART_H
#define SVGPART_H

// KF
#include <KParts/ReadOnlyPart>

class SvgBrowserExtension;

class QGraphicsScene;
class QGraphicsSvgItem;
class QGraphicsView;
class QSvgRenderer;

class SvgPart : public KParts::ReadOnlyPart
{
    Q_OBJECT

public:
    SvgPart(QWidget* parentWidget, QObject* parent, const QVariantList&);

    bool openUrl(const QUrl& url) override;
    bool closeUrl() override;

    void setExtendedRestoreArguments(qreal zoom);

    qreal zoom() const;
    int horizontalScrollPosition() const;
    int verticalScrollPosition() const;

protected:
    bool openFile() override;
    bool doOpenStream(const QString& mimeType) override;
    bool doWriteStream(const QByteArray& data) override;
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
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    QGraphicsSvgItem* mItem;
    QSvgRenderer* mRenderer;

    SvgBrowserExtension* m_browserExtension;

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
