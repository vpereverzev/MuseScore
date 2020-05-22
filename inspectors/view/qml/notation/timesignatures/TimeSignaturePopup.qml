import QtQuick 2.9
import QtQuick.Controls 2.2
import MuseScore.Inspectors 3.3
import QtQuick.Layouts 1.3
import "../../common"

StyledPopup {
    id: root

    property QtObject model: null

    implicitHeight: contentColumn.implicitHeight + topPadding + bottomPadding
    width: parent.width

    Column {
        id: contentColumn

        width: parent.width

        spacing: 16

        Column {
            spacing: 8

            width: parent.width

            StyledTextLabel {
                text: qsTr("Scale")
            }

            Item {
                height: childrenRect.height
                width: parent.width

                IncrementalPropertyControl {
                    anchors.left: parent.left
                    anchors.right: parent.horizontalCenter
                    anchors.rightMargin: 4
                    measureUnitsSymbol: "%"
                    step: 1

                    icon: IconNameTypes.HORIZONTAL

                    enabled: model ? model.scale.isEnabled : false
                    // isIndeterminate: NEEDED?
                    currentValue: model ? model.scale.value.width * 100.0 : 0

                    onValueEdited: { model.scale.value.width = newValue / 100.0 }
                }

                IncrementalPropertyControl {
                    anchors.left: parent.horizontalCenter
                    anchors.leftMargin: 4
                    anchors.right: parent.right
                    measureUnitsSymbol: "%"
                    step: 1

                    icon: IconNameTypes.VERTICAL

                    enabled: model ? model.scale.isEnabled : false
                    // isIndeterminate: NEEDED?
                    currentValue: model ? model.scale.value.height * 100.0 : 0

                    onValueEdited: { model.scale.value.height = newValue / 100.0 }
                }
            }
        }

        CheckBox {
            isIndeterminate: model ? model.hasToShowCourtesy.isUndefined : false
            checked: model && !isIndeterminate ? model.hasToShowCourtesy.value : false
            text: qsTr("Show courtesy time signature on previous system")

            onClicked: { model.hasToShowCourtesy.value = !checked }
        }

        Column {
            spacing: 8

            width: parent.width

            FlatButton {
                text: qsTr("Change time signature")
                anchors.left: parent.left
                anchors.right: parent.right

                onClicked: {
                    model.showTimeSigProperties();
                }
            }
        }
    }
}
