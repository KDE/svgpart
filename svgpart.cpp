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
#include <QSvgRenderer>

// KDE
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <kparts/genericfactory.h>

// Local

//Factory Code
typedef KParts::GenericFactory<SvgPart> SvgPartFactory;
K_EXPORT_COMPONENT_FACTORY( svgpart /*library name*/, SvgPartFactory )


SvgPart::SvgPart(QWidget* parentWidget, QObject* parent, const QStringList&)
: KParts::ReadOnlyPart(parent)
{
	mScene = new QGraphicsScene(this);
	mView = new QGraphicsView(mScene, parentWidget);
	mView->setDragMode(QGraphicsView::ScrollHandDrag);
	mItem = 0;
	setWidget(mView);

	KStandardAction::zoomIn(this, SLOT(zoomIn()), actionCollection());
	KStandardAction::zoomOut(this, SLOT(zoomOut()), actionCollection());
	setXMLFile("svgpart/svgpart.rc");
}


bool SvgPart::openFile() {
	delete mItem;
	mItem = new QGraphicsSvgItem(localFilePath());
	mScene->addItem(mItem);
	return true;
}


KAboutData* SvgPart::createAboutData() {
	KAboutData* aboutData = new KAboutData( "svgpart", 0, ki18n("SVG Part"),
		"1.0", ki18n("A KPart to display SVG images"),
		KAboutData::License_GPL,
		ki18n("Copyright 2007, Aurélien Gâteau <aurelien.gateau@free.fr>"));
	return aboutData;
}


void SvgPart::zoomIn() {
	setZoom(zoom() * 2);
}


void SvgPart::zoomOut() {
	setZoom(zoom() / 2);
}


qreal SvgPart::zoom() const {
	return mView->matrix().m11();
}


void SvgPart::setZoom(qreal value) {
	QMatrix matrix;
	matrix.scale(value, value);
	mView->setMatrix(matrix);
}
