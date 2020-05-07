#ifndef TIMESIGNATURESETTINGSMODEL_H
#define TIMESIGNATURESETTINGSMODEL_H

#include "models/abstractinspectormodel.h"

#include "mscore/shortcut.h"
#include <QAction>

class TimeSignatureSettingsModel : public AbstractInspectorModel
{
    Q_OBJECT

    Q_PROPERTY(PropertyItem* hasToShowCourtesy READ hasToShowCourtesy CONSTANT)
    Q_PROPERTY(PropertyItem* type READ type CONSTANT)
    Q_PROPERTY(PropertyItem* scale READ scale CONSTANT)
public:
    explicit TimeSignatureSettingsModel(QObject* parent, IElementRepositoryService* repository);

    void createProperties() override;
    void requestElements() override;
    void loadProperties() override;
    void resetProperties() override;

    PropertyItem* hasToShowCourtesy() const;
    PropertyItem* type() const;
    PropertyItem* scale() const;

    Q_INVOKABLE void showTimeSigProperties() const;

private:
    PropertyItem* m_hasToShowCourtesy = nullptr;
    PropertyItem* m_type = nullptr;
    PropertyItem* m_scale = nullptr;
    QAction* m_showTimeSigPropertiesAction = nullptr;
};

#endif // TIMESIGNATURESETTINGSMODEL_H
