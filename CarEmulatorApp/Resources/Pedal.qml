import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Column {
    property alias text: theText.text
    property alias slider: theSlider

    spacing: 0

    Text {
        id: theText
        width: parent.width
        height: parent.height * 0.1
        text: ""
        color: "white"
        horizontalAlignment: Text.AlignHCenter
    }

    Slider {
        id: theSlider
        width: parent.width
        height: parent.height * 0.9
        orientation: Qt.Vertical
        minimumValue: -1.0
        maximumValue: 1.0
        value: 0
    }
}
