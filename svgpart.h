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

// KDE
#include <kparts/readonlypart.h>

class QGraphicsScene;
class QGraphicsSvgItem;
class QGraphicsView;
class QSvgRenderer;

class SvgPart : public KParts::ReadOnlyPart
{
    Q_OBJECT

public:
    SvgPart(QWidget* parentWidget, QObject* parent, const QVariantList&);

    bool closeUrl() override;

protected:
    bool openFile() override;

private Q_SLOTS:
    void zoomActualSize();
    void zoomIn();
    void zoomOut();

private:
    qreal zoom() const;
    void setZoom(qreal value);

private:
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    QGraphicsSvgItem* mItem;
    QSvgRenderer* mRenderer;
};

#endif /* SVGPART_H */
