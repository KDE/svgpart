/*
Copyright (C) 2017 by Friedrich W. H. Kossebau <kossebau@kde.org>

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
