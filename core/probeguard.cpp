/*
  probeguard.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "probeguard.h"

#include <QThreadStorage>

static QThreadStorage<bool> s_probeGuards;

using namespace GammaRay;

ProbeGuard::ProbeGuard() :
    m_previousState(insideProbe())
{
    setInsideProbe(true);
}

ProbeGuard::~ProbeGuard()
{
    setInsideProbe(m_previousState);
}

bool ProbeGuard::insideProbe()
{
    if (!s_probeGuards.hasLocalData())
        return false;
    return s_probeGuards.localData();
}

void ProbeGuard::setInsideProbe(bool inside)
{
    s_probeGuards.localData() = inside;
}