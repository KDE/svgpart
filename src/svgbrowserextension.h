/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SVGBROWSEREXTENSION_H
#define SVGBROWSEREXTENSION_H

// Qt
#include <QtGlobal>

// KF
#include <KParts/NavigationExtension>

class SvgPart;

class SvgBrowserExtension : public KParts::NavigationExtension
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
