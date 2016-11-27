import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Button {
    id: root

    style: ButtonStyle {
        background: Rectangle {
            color: control.pressed ? "gray" : "transparent"
            border.color: "white"
        }

        label: Text {
            color: "white"
            text: root.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
