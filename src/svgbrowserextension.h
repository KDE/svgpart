/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SVGBROWSEREXTENSION_H
#define SVGBROWSEREXTENSION_H

// Qt
#include <QtGlobal>

// KF
#if QT_VERSION_MAJOR == 5
#include <KParts/BrowserExtension>
#else
#include <KParts/NavigationExtension>
#endif

class SvgPart;

#if QT_VERSION_MAJOR == 5
class SvgBrowserExtension : public KParts::BrowserExtension
#else
class SvgBrowserExtension : public KParts::NavigationExtension
#endif
{
    Q_OBJECT

public:
    explicit SvgBrowserExtension(SvgPart *part);

    int xOffset() override;
    int yOffset() override;

    void saveState(QDataStream &stream) override;
    void restoreState(QDataStream &stream) override;

private:
    SvgPart *m_part;
};

#endif
