//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2019 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#include "google_analytics/ganalytics.h"
#include "settings/types/preferencekeys.h"
#include "telemetryservice.h"

TelemetryService::TelemetryService()
    {
    }

TelemetryService::TelemetryService(const TelemetryService &) : TelemetryService()
    {
    }

void TelemetryService::sendEvent(const QString &category, const QString &action, const QString &label, const QVariant &value, const QVariantMap &customValues)
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance()->sendEvent(category, action, label, value, customValues);
      }

void TelemetryService::sendException(const QString &exceptionDescription, bool exceptionFatal, const QVariantMap &customValues)
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance()->sendException(exceptionDescription, exceptionFatal, customValues);
      }

void TelemetryService::startSession()
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance()->startSession();
      }

void TelemetryService::endSession()
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance()->endSession();
      }

bool TelemetryService::isTelemetryAllowed() const
      {
      return m_settings.value(PREF_APP_TELEMETRY_ALLOWED, false).toBool();
      }