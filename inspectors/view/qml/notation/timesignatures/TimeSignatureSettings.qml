import QtQuick 2.9
import QtQuick.Layouts 1.3
import MuseScore.Inspectors 3.3
import "../../common"

PopupViewButton {
    id: root

    property alias model: timeSignaturePopup.model

    icon: IconNameTypes.TYPE_TIMESIGNATURE
    text: qsTr("Time signatures")

    visible: root.model ? !root.model.isEmpty : false

    TimeSignaturePopup {
        id: timeSignaturePopup

        x: popupPositionX
        y: popupPositionY
        arrowX: parent.x + parent.width / 2
        width: popupAvailableWidth
    }
}
