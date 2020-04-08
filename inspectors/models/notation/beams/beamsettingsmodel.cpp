#include "beamsettingsmodel.h"

BeamSettingsModel::BeamSettingsModel(QObject* parent, IElementRepositoryService* repository) : AbstractInspectorModel(parent, repository)
{
    createProperties();

    setTitle(tr("Beam"));
    setBeamModesModel(new BeamModesModel(this, repository));
}

void BeamSettingsModel::createProperties()
{
    m_featheringHeightLeft = buildPropertyItem(Ms::Pid::GROW_LEFT);
    m_featheringHeightRight = buildPropertyItem(Ms::Pid::GROW_RIGHT);

    m_isForcedHorizontally = buildPropertyItem(Ms::Pid::BEAM_NO_SLOPE, [this] (const int pid, const QVariant& isForcedHorizontally) {
        onPropertyValueChanged(static_cast<Ms::Pid>(pid), isForcedHorizontally.toBool());

        if (isForcedHorizontally.toBool()) {
            m_beamVectorX->setValue(0.0);
            m_beamVectorY->setValue(0.0);
        }
    });

    m_isBeamHidden = buildPropertyItem(Ms::Pid::VISIBLE, [this] (const int pid, const QVariant& isBeamHidden) {
        onPropertyValueChanged(static_cast<Ms::Pid>(pid), !isBeamHidden.toBool());
    });

    m_beamVectorX = buildPropertyItem(Ms::Pid::BEAM_POS, [this] (const int, const QVariant& newValue) {
        updateBeamHeight(newValue.toDouble(), m_beamVectorY->value().toDouble());
    });

    m_beamVectorY = buildPropertyItem(Ms::Pid::BEAM_POS, [this] (const int, const QVariant& newValue) {
        updateBeamHeight(m_beamVectorX->value().toDouble(), newValue.toDouble());
    });
}

void BeamSettingsModel::requestElements()
{
    m_elementList = m_repository->findElementsByType(Ms::ElementType::BEAM);
}

void BeamSettingsModel::loadProperties()
{
    loadPropertyItem(m_featheringHeightLeft);
    loadPropertyItem(m_featheringHeightRight);
    loadPropertyItem(m_isForcedHorizontally);

    loadPropertyItem(m_isBeamHidden, [this] (const QVariant& isVisible) -> QVariant {
       return !isVisible.toBool();
    });

    loadPropertyItem(m_beamVectorX, [this] (const QVariant& elementPropertyValue) -> QVariant {
        return elementPropertyValue.toPointF().x();
    });

    loadPropertyItem(m_beamVectorY, [this] (const QVariant& elementPropertyValue) -> QVariant {
        return elementPropertyValue.toPointF().y();
    });

    m_cachedBeamVector.setX(m_beamVectorX->value().toDouble());
    m_cachedBeamVector.setY(m_beamVectorY->value().toDouble());

    updateFeatheringMode(m_featheringHeightLeft->value().toDouble(), m_featheringHeightRight->value().toDouble());
}

void BeamSettingsModel::resetProperties()
{
    m_featheringHeightLeft->resetToDefault();
    m_featheringHeightRight->resetToDefault();
    m_isForcedHorizontally->resetToDefault();
    m_beamVectorX->resetToDefault();
    m_beamVectorY->resetToDefault();

    m_cachedBeamVector = QPointF();

    setFeatheringMode(static_cast<int>(BeamTypes::FEATHERING_NONE));
    setIsBeamHeightLocked(false);
}

void BeamSettingsModel::updateBeamHeight(const qreal& x, const qreal& y)
{
    qreal deltaX = x - m_cachedBeamVector.x();
    qreal deltaY = y - m_cachedBeamVector.y();

    qreal uniformDelta = 0.0;

    if (qFuzzyIsNull(deltaX)) {
        uniformDelta = deltaY;
    } else {
        uniformDelta = deltaX;
    }

    if (isBeamHeightLocked()) {
        m_beamVectorX->setValue(m_cachedBeamVector.x() + uniformDelta);
        m_beamVectorY->setValue(m_cachedBeamVector.y() + uniformDelta);
    }

    onPropertyValueChanged(Ms::Pid::USER_MODIFIED, true); // TODO проверить, можно ли это перенести в DOM модель
    onPropertyValueChanged(Ms::Pid::BEAM_POS, QPointF(m_beamVectorX->value().toDouble(), m_beamVectorY->value().toDouble()));

    m_cachedBeamVector.setX(m_beamVectorX->value().toDouble());
    m_cachedBeamVector.setY(m_beamVectorY->value().toDouble());
}

void BeamSettingsModel::updateFeatheringMode(const qreal &x, const qreal &y)
{
    if (x != y) {
        setFeatheringMode(x > y ? static_cast<int>(BeamTypes::FEATHERING_LEFT)
                                : static_cast<int>(BeamTypes::FEATHERING_RIGHT));
    } else {
        setFeatheringMode(static_cast<int>(BeamTypes::FEATHERING_NONE));
    }
}

bool BeamSettingsModel::isBeamHeightLocked() const
{
    return m_isBeamHeightLocked;
}

QObject* BeamSettingsModel::beamModesModel() const
{
    return m_beamModesModel;
}

PropertyItem* BeamSettingsModel::featheringHeightLeft() const
{
    return m_featheringHeightLeft;
}

PropertyItem* BeamSettingsModel::featheringHeightRight() const
{
    return m_featheringHeightRight;
}

int BeamSettingsModel::featheringMode() const
{
    return static_cast<int>(m_featheringMode);
}

PropertyItem* BeamSettingsModel::isForcedHorizontally() const
{
    return m_isForcedHorizontally;
}

PropertyItem* BeamSettingsModel::isBeamHidden() const
{
    return m_isBeamHidden;
}

PropertyItem* BeamSettingsModel::beamVectorX() const
{
    return m_beamVectorX;
}

PropertyItem* BeamSettingsModel::beamVectorY() const
{
    return m_beamVectorY;
}

void BeamSettingsModel::setIsBeamHeightLocked(bool isBeamHeightLocked)
{
    if (m_isBeamHeightLocked == isBeamHeightLocked)
        return;

    m_isBeamHeightLocked = isBeamHeightLocked;
    emit isBeamHeightLockedChanged(m_isBeamHeightLocked);
}

void BeamSettingsModel::setFeatheringMode(int featheringMode)
{
    BeamTypes::FeatheringMode newMode = static_cast<BeamTypes::FeatheringMode>(featheringMode);

    if (m_featheringMode == newMode) {
        return;
    }

    m_featheringMode = newMode;

    switch (newMode) {
    case BeamTypes::FEATHERING_NONE:
        m_featheringHeightLeft->setValue(1.0);
        m_featheringHeightRight->setValue(1.0);
        break;
    case BeamTypes::FEATHERING_LEFT:
        m_featheringHeightLeft->setValue(1.0);
        m_featheringHeightRight->setValue(0.0);
        break;
    case BeamTypes::FEATHERING_RIGHT:
        m_featheringHeightLeft->setValue(0.0);
        m_featheringHeightRight->setValue(1.0);
        break;
    }

    emit featheringModeChanged(featheringMode);
}

void BeamSettingsModel::setBeamModesModel(BeamModesModel* beamModesModel)
{
    m_beamModesModel = beamModesModel;

    connect(m_beamModesModel->isFeatheringAvailable(), &PropertyItem::valueChanged, this, [this] (const QVariant& newValue) {
        if (!newValue.toBool()) {
            setFeatheringMode(static_cast<int>(BeamTypes::FEATHERING_NONE));
        }
    });

    emit beamModesModelChanged(m_beamModesModel);
}