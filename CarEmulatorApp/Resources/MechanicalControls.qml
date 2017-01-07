import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: root
    color: "black"

    Item {
        id: gearControls
        width: parent.width
        height: parent.height * 0.2

        Row {
            anchors.centerIn: parent
            spacing: 5

            Label {
                width: gearControls.width * 0.2
                height: gearControls.height * 0.8
                text: "Gear"
                color: "white"
            }

            Label {
                width: gearControls.width * 0.2
                height: gearControls.height * 0.8
                text: car.gear === 0 ? "REV" : car.gear === 1 ? "N" : car.gear - 1
                color: "white"
            }

            TextButton {
                width: gearControls.width * 0.2
                height: gearControls.height * 0.8
                text: "Up"
                onClicked: {
                    car.gearUp();
                }
            }

            TextButton {
                width: gearControls.width * 0.2
                height: gearControls.height * 0.8
                text: "Down"
                onClicked: {
                    car.gearDown();
                }
            }
        }
    }

    Item {
        id: pedals
        width: parent.width
        anchors.top: gearControls.bottom
        anchors.bottom: parent.bottom

        property int pedalWidth: width * 0.15

        Row {
            anchors.centerIn: parent
            spacing: 5

            Column {
                Text {
                    width: pedals.pedalWidth
                    height: pedals.height * 0.1
                    text: "Clutch"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                Slider {
                    id: clutchPedal
                    width: pedals.pedalWidth
                    height: pedals.height * 0.8
                    orientation: Qt.Vertical
                    value: car.clutchPedal
                    onValueChanged: car.clutchPedal = value;
                }
            }

            Column {
                Text {
                    width: pedals.pedalWidth
                    height: pedals.height * 0.1
                    text: "Break"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                Slider {
                    id: breakPedal
                    width: pedals.pedalWidth
                    height: pedals.height * 0.8
                    orientation: Qt.Vertical
                    value: car.breakPedal
                    onValueChanged: car.breakPedal = value;
                }
            }

            Column {
                Text {
                    width: pedals.pedalWidth
                    height: pedals.height * 0.1
                    text: "Gas"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                Slider {
                    id: gasPedal
                    width: pedals.pedalWidth
                    height: pedals.height * 0.8
                    orientation: Qt.Vertical
                    value: car.gasPedal
                    onValueChanged: car.gasPedal = value;
                }
            }

            Column {
                Text {
                    width: pedals.pedalWidth
                    height: pedals.height * 0.1
                    text: "Speed dem"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                Slider {
                    id: speedDemand
                    width: pedals.pedalWidth
                    height: pedals.height * 0.8
                    orientation: Qt.Vertical
                    minimumValue: -1.0
                    maximumValue: 1.0
                    stepSize: 0.1
                    value: car.speedDemand
                    onValueChanged: car.speedDemand = value;
                }
            }

            Column {
                Text {
                    width: pedals.pedalWidth
                    height: pedals.height * 0.1
                    text: "Accel dem"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                Slider {
                    id: accelDemand
                    width: pedals.pedalWidth
                    height: pedals.height * 0.8
                    orientation: Qt.Vertical
                    minimumValue: -1.0
                    maximumValue: 1.0
                    stepSize: 0.1
                    value: car.accelDemand
                    onValueChanged: car.accelDemand = value;
                }
            }
        }
    }
}
