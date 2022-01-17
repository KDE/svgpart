/*
    SPDX-FileCopyrightText: 2022 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "svgview.h"

// Qt
#include <QScrollBar>
#include <QTransform>
#include <QWheelEvent>

constexpr qreal zoomFactor = 1.2;

SvgView::SvgView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setFrameStyle(QFrame::NoFrame);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void SvgView::zoomIn()
{
    setZoom(zoom() * zoomFactor);
}

void SvgView::zoomOut()
{
    setZoom(zoom() / zoomFactor);
}

void SvgView::zoomActualSize()
{
    setZoom(1.0);
}

void SvgView::setZoom(qreal value)
{
    QTransform matrix;
    matrix.scale(value, value);
    setTransform(matrix);
}

void SvgView::setHorizontalScrollPosition(int horizontalScrollPosition)
{
    horizontalScrollBar()->setValue(horizontalScrollPosition);
}

void SvgView::setVerticalScrollPosition(int verticalScrollPosition)
{
    verticalScrollBar()->setValue(verticalScrollPosition);
}

int SvgView::horizontalScrollPosition() const
{
    return horizontalScrollBar()->value();
}

int SvgView::verticalScrollPosition() const
{
    return verticalScrollBar()->value();
}

qreal SvgView::zoom() const
{
    return transform().m11();
}

void SvgView::wheelEvent(QWheelEvent *wheelEvent)
{
    if (wheelEvent->modifiers() & Qt::ControlModifier) {
        const int delta = wheelEvent->angleDelta().y();
        if (delta > 0) {
            zoomIn();
        } else if (delta < 0) {
            zoomOut();
        }

        wheelEvent->accept();
        return;
    }

    QGraphicsView::wheelEvent(wheelEvent);
}
