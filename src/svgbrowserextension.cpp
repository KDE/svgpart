/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "svgbrowserextension.h"

#include "svgpart.h"

// Qt
#include <QDataStream>

SvgBrowserExtension::SvgBrowserExtension(SvgPart *part)
#if QT_VERSION_MAJOR == 5
    : KParts::BrowserExtension(part)
#else
    : KParts::NavigationExtension(part)
#endif
    , m_part(part)
{
}

int SvgBrowserExtension::xOffset()
{
    return m_part->horizontalScrollPosition();
}

int SvgBrowserExtension::yOffset()
{
    return m_part->verticalScrollPosition();
}

void SvgBrowserExtension::saveState(QDataStream &stream)
{
    stream << m_part->zoom();
#if QT_VERSION_MAJOR == 5
    KParts::BrowserExtension::saveState(stream);
#else
    KParts::NavigationExtension::saveState(stream);
#endif
}

void SvgBrowserExtension::restoreState(QDataStream &stream)
{
    qreal zoom;
    stream >> zoom;

    m_part->setExtendedRestoreArguments(zoom);
#if QT_VERSION_MAJOR == 5
    KParts::BrowserExtension::restoreState(stream);
#else
    KParts::NavigationExtension::restoreState(stream);
#endif
}

#include "moc_svgbrowserextension.cpp"
