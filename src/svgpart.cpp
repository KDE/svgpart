/*
    SPDX-FileCopyrightText: 2007 Aurélien Gâteau

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "svgpart.h"

// part
#include "svgbrowserextension.h"
#include "svgview.h"
// KF
#include <KActionCollection>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KPluginMetaData>
#include <KStandardAction>
// Qt
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QMimeDatabase>
#include <QSvgRenderer>
#include <QTimer>

// Factory Code
K_PLUGIN_FACTORY_WITH_JSON(SvgPartFactory, "svgpart.json", registerPlugin<SvgPart>();)

SvgPart::SvgPart(QWidget *parentWidget, QObject *parent, const KPluginMetaData &metaData, const QVariantList &)
    : KParts::ReadOnlyPart(parent, metaData)
    , mItem(nullptr)
    , m_browserExtension(new SvgBrowserExtension(this))
{
    mRenderer = new QSvgRenderer(this);
    mScene = new QGraphicsScene(this);
    mView = new SvgView(mScene, parentWidget);
    setWidget(mView);

    KStandardAction::actualSize(mView, &SvgView::zoomActualSize, actionCollection());
    KStandardAction::zoomIn(mView, &SvgView::zoomIn, actionCollection());
    KStandardAction::zoomOut(mView, &SvgView::zoomOut, actionCollection());
    setXMLFile(QStringLiteral("svgpart.rc"));
}

bool SvgPart::openUrl(const QUrl &url)
{
    mCloseUrlFromOpen = true;

    const auto success = KParts::ReadOnlyPart::openUrl(url);

    mCloseUrlFromOpen = false;

    return success;
}

bool SvgPart::openFile()
{
    if (!mRenderer->load(localFilePath())) {
        return false;
    }

    createViewForDocument();

    return true;
}

bool SvgPart::doOpenStream(const QString &mimeType)
{
    auto mime = QMimeDatabase().mimeTypeForName(mimeType);
    if (!mime.inherits(QStringLiteral("image/svg+xml")) && !mime.inherits(QStringLiteral("image/svg+xml-compressed"))) {
        return false;
    }

    mStreamedData.clear();

    return true;
}

bool SvgPart::doWriteStream(const QByteArray &data)
{
    mStreamedData.append(data);
    return true;
}

bool SvgPart::doCloseStream()
{
    // too bad QSvgRenderer supports QXmlStreamReader, but not its incremental parsing
    if (!mRenderer->load(mStreamedData)) {
        mStreamedData.clear();
        return false;
    }

    mStreamedData.clear();

    createViewForDocument();

    return true;
}

bool SvgPart::closeUrl()
{
    // protect against repeated call if already closed
    const auto currentUrl = url();
    // remember old view state for a possible reload from same url
    if (currentUrl.isValid()) {
        mPreviousUrl = currentUrl;

        mPreviousZoom = zoom();
        mPreviousHorizontalScrollPosition = mView->horizontalScrollPosition();
        mPreviousVerticalScrollPosition = mView->verticalScrollPosition();
    }

    mView->resetTransform();
    // cannot reset the rect completely, as a null QRectF is ignored
    // so at least just a 1 pixel square one
    mScene->setSceneRect(QRectF(0, 0, 1, 1));

    delete mItem;
    mItem = nullptr;

    // reset arguments
    if (!mCloseUrlFromOpen) {
        mHasExtendedRestoreArguments = false;
    }

    return KParts::ReadOnlyPart::closeUrl();
}

void SvgPart::createViewForDocument()
{
    mItem = new QGraphicsSvgItem();
    mItem->setSharedRenderer(mRenderer);
    mScene->addItem(mItem);
    // we reuse the scene, whose scenerect though is not properly resetable, so ensure up-to-date one
    mScene->setSceneRect(mItem->boundingRect());

    // ideally the viewstate would be restored here, but at this point in time
    // the view has not yet been updated to the scene and is a wrong size,
    // so setting the scrollbars etc now will not have any effect
    // TODO: this results in flickering, needs to find a better way to hook into
    // updating of view state to new content before the first rendering is done
    QTimer::singleShot(0, this, &SvgPart::delayedRestoreViewState);
}

void SvgPart::delayedRestoreViewState()
{
    // arguments set by caller or restore method
    KParts::OpenUrlArguments args(arguments());
    qreal zoomValue = mHasExtendedRestoreArguments ? mRestoreZoom : 1.0;

    // reloading same url?
    // we can't tell if caller has explicitly set xOffset/yOffset of OpenUrlArguments
    // so in case of same url we just assume a reload and ignore the OpenUrlArguments xOffset/yOffset
    if (!mHasExtendedRestoreArguments && (url() == mPreviousUrl)) {
        // restore last view state instead
        zoomValue = mPreviousZoom;
        args.setXOffset(mPreviousHorizontalScrollPosition);
        args.setYOffset(mPreviousVerticalScrollPosition);
    }

    // now restore view state
    mView->setZoom(zoomValue);

    mView->setHorizontalScrollPosition(args.xOffset());
    mView->setVerticalScrollPosition(args.yOffset());
}

void SvgPart::setExtendedRestoreArguments(qreal zoom)
{
    mHasExtendedRestoreArguments = true;
    mRestoreZoom = zoom;
}

qreal SvgPart::zoom() const
{
    return mView->zoom();
}

int SvgPart::horizontalScrollPosition() const
{
    return mView->horizontalScrollPosition();
}

int SvgPart::verticalScrollPosition() const
{
    return mView->verticalScrollPosition();
}

#include "moc_svgpart.cpp"
#include "svgpart.moc"
