#include "timesignaturesettingsmodel.h"

TimeSignatureSettingsModel::TimeSignatureSettingsModel(QObject* parent, IElementRepositoryService* repository) :
    AbstractInspectorModel(parent, repository)
{
    setModelType(TYPE_TIMESIGNATURE);
    setTitle(tr("Time signatures"));
    createProperties();

    m_showTimeSigPropertiesAction = Ms::Shortcut::getActionByName("show-timesig-properties");
}

void TimeSignatureSettingsModel::createProperties()
{
    m_hasToShowCourtesy = buildPropertyItem(Ms::Pid::SHOW_COURTESY);
    m_type = buildPropertyItem(Ms::Pid::TIMESIG_TYPE);
    m_scale = buildPropertyItem(Ms::Pid::SCALE);
}

void TimeSignatureSettingsModel::requestElements()
{
    m_elementList = m_repository->findElementsByType(Ms::ElementType::TIMESIG);
}

void TimeSignatureSettingsModel::loadProperties()
{
    loadPropertyItem(m_hasToShowCourtesy, [](const QVariant& elementPropertyValue) -> QVariant {
        return elementPropertyValue.toBool();
    });

    loadPropertyItem(m_type);
    loadPropertyItem(m_scale);
}

void TimeSignatureSettingsModel::resetProperties()
{
    m_hasToShowCourtesy->resetToDefault();
    m_type->resetToDefault();
    m_scale->resetToDefault();
}

PropertyItem* TimeSignatureSettingsModel::hasToShowCourtesy() const
{
    return m_hasToShowCourtesy;
}

PropertyItem* TimeSignatureSettingsModel::type() const
{
    return m_type;
}

PropertyItem* TimeSignatureSettingsModel::scale() const
{
    return m_scale;
}

void TimeSignatureSettingsModel::showTimeSigProperties() const
{
    if (!m_showTimeSigPropertiesAction) {
        return;
    }

    m_showTimeSigPropertiesAction->trigger();
}
