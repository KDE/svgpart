/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "svgbrowserextension.h"

#include "svgpart.h"

// Qt
#include <QDataStream>


SvgBrowserExtension::SvgBrowserExtension(SvgPart* part)
    : KParts::BrowserExtension(part)
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

void SvgBrowserExtension::saveState(QDataStream& stream)
{
    stream << m_part->zoom();
    KParts::BrowserExtension::saveState(stream);
}

void SvgBrowserExtension::restoreState(QDataStream& stream)
{
    qreal zoom;
    stream >> zoom;

    m_part->setExtendedRestoreArguments(zoom);
    KParts::BrowserExtension::restoreState(stream);
}

