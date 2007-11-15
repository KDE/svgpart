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
#include <QSvgWidget>

// KDE
#include <kparts/genericfactory.h>

// Local

//Factory Code
typedef KParts::GenericFactory<SvgPart> SvgPartFactory;
K_EXPORT_COMPONENT_FACTORY( svgpart /*library name*/, SvgPartFactory )


SvgPart::SvgPart(QWidget* parentWidget, QObject* parent, const QStringList&)
: KParts::ReadOnlyPart(parent)
{
	mSvgWidget = new QSvgWidget(parentWidget);
	setWidget(mSvgWidget);
	setXMLFile("svgpart/svgpart.rc");
}


bool SvgPart::openFile() {
	mSvgWidget->load(localFilePath());
	return true;
}


KAboutData* SvgPart::createAboutData() {
	KAboutData* aboutData = new KAboutData( "svgpart", 0, ki18n("SVG Part"),
		"1.0", ki18n("A KPart to display SVG images"),
		KAboutData::License_GPL,
		ki18n("Copyright 2007, Aurélien Gâteau <aurelien.gateau@free.fr>"));
	return aboutData;
}
