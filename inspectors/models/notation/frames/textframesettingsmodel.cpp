#include "textframesettingsmodel.h"

TextFrameSettingsModel::TextFrameSettingsModel(QObject* parent, IElementRepositoryService* repository) :
    AbstractInspectorModel(parent, repository)
{
    setModelType(TYPE_TEXT_FRAME);
    setTitle(tr("Text frame"));
    createProperties();
}

void TextFrameSettingsModel::createProperties()
{
    m_gapAbove = buildPropertyItem(Ms::Pid::TOP_GAP);
    m_gapBelow = buildPropertyItem(Ms::Pid::BOTTOM_GAP);
    m_frameLeftMargin = buildPropertyItem(Ms::Pid::LEFT_MARGIN);
    m_frameRightMargin = buildPropertyItem(Ms::Pid::RIGHT_MARGIN);
    m_frameTopMargin = buildPropertyItem(Ms::Pid::TOP_MARGIN);
    m_frameBottomMargin = buildPropertyItem(Ms::Pid::BOTTOM_MARGIN);
}

void TextFrameSettingsModel::requestElements()
{
    m_elementList = m_repository->findElementsByType(Ms::ElementType::TBOX);
}

void TextFrameSettingsModel::loadProperties()
{
    auto formatter = [] (const QVariant& elementPropertyValue) -> QVariant {
        return QString::number(elementPropertyValue.toDouble(), 'f', 2).toDouble();
    };

    loadPropertyItem(m_gapAbove, formatter);
    loadPropertyItem(m_gapBelow, formatter);
    loadPropertyItem(m_frameLeftMargin, formatter);
    loadPropertyItem(m_frameRightMargin, formatter);
    loadPropertyItem(m_frameTopMargin, formatter);
    loadPropertyItem(m_frameBottomMargin, formatter);
}

void TextFrameSettingsModel::resetProperties()
{
    m_gapAbove->resetToDefault();
    m_gapBelow->resetToDefault();
    m_frameLeftMargin->resetToDefault();
    m_frameRightMargin->resetToDefault();
    m_frameTopMargin->resetToDefault();
    m_frameBottomMargin->resetToDefault();
}

PropertyItem* TextFrameSettingsModel::gapAbove() const
{
    return m_gapAbove;
}

PropertyItem *TextFrameSettingsModel::gapBelow() const
{
    return m_gapBelow;
}

PropertyItem *TextFrameSettingsModel::frameLeftMargin() const
{
    return m_frameLeftMargin;
}

PropertyItem *TextFrameSettingsModel::frameRightMargin() const
{
    return m_frameRightMargin;
}

PropertyItem *TextFrameSettingsModel::frameTopMargin() const
{
    return m_frameTopMargin;
}

PropertyItem *TextFrameSettingsModel::frameBottomMargin() const
{
    return m_frameBottomMargin;
}
