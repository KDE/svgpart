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
#include "svgpart.moc"

// Qt
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsView>

// KDE
#include <kaboutdata.h>
#include <kactioncollection.h>
#include <kgenericfactory.h>
#include <kstandardaction.h>
#include <ksvgrenderer.h>

// Local

static KAboutData createAboutData()
{
	KAboutData aboutData( "svgpart", 0, ki18n("SVG Part"),
		"1.0", ki18n("A KPart to display SVG images"),
		KAboutData::License_GPL,
		ki18n("Copyright 2007, Aurélien Gâteau <aurelien.gateau@free.fr>"));
	return aboutData;
}

//Factory Code
K_PLUGIN_FACTORY( SvgPartFactory, registerPlugin< SvgPart >(); )
K_EXPORT_PLUGIN( SvgPartFactory( createAboutData() ) )


SvgPart::SvgPart(QWidget* parentWidget, QObject* parent, const QVariantList&)
: KParts::ReadOnlyPart(parent)
{
	mRenderer = new KSvgRenderer(this);
	mScene = new QGraphicsScene(this);
	mView = new QGraphicsView(mScene, parentWidget);
	mView->setDragMode(QGraphicsView::ScrollHandDrag);
	mItem = 0;
	setWidget(mView);

	KStandardAction::actualSize(this, SLOT(zoomActualSize()), actionCollection());
	KStandardAction::zoomIn(this, SLOT(zoomIn()), actionCollection());
	KStandardAction::zoomOut(this, SLOT(zoomOut()), actionCollection());
	setXMLFile("svgpart/svgpart.rc");
}


bool SvgPart::openFile() {
	delete mItem;
	if (!mRenderer->load(localFilePath())) {
		return false;
	}
	mItem = new QGraphicsSvgItem();
	mItem->setSharedRenderer(mRenderer);
	mScene->addItem(mItem);
	return true;
}


void SvgPart::zoomIn() {
	setZoom(zoom() * 2);
}


void SvgPart::zoomOut() {
	setZoom(zoom() / 2);
}


void SvgPart::zoomActualSize() {
	setZoom(1.0);
}


qreal SvgPart::zoom() const {
	return mView->matrix().m11();
}


void SvgPart::setZoom(qreal value) {
	QMatrix matrix;
	matrix.scale(value, value);
	mView->setMatrix(matrix);
}
