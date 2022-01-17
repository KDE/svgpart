/*
    SPDX-FileCopyrightText: 2022 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <QGraphicsView>

class SvgView : public QGraphicsView
{
    Q_OBJECT

public:
    SvgView(QGraphicsScene *scene, QWidget *parent);
    ~SvgView() = default;

public:
    qreal zoom() const;
    int horizontalScrollPosition() const;
    int verticalScrollPosition() const;

    void setHorizontalScrollPosition(int horizontalScrollPosition);
    void setVerticalScrollPosition(int verticalScrollPosition);
    void setZoom(qreal value);

public Q_SLOTS:
    void zoomActualSize();
    void zoomIn();
    void zoomOut();
};

#endif
