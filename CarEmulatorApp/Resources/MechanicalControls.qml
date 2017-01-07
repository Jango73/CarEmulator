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

            Pedal {
                width: pedals.pedalWidth
                height: pedals.height * 0.8
                text: "Clutch"
                slider.value: car.clutchPedal
                slider.onValueChanged: car.clutchPedal = slider.value;
                slider.minimumValue: 0
            }

            Pedal {
                width: pedals.pedalWidth
                height: pedals.height * 0.8
                text: "Break"
                slider.value: car.breakPedal
                slider.onValueChanged: car.breakPedal = slider.value;
                slider.minimumValue: 0
            }

            Pedal {
                width: pedals.pedalWidth
                height: pedals.height * 0.8
                text: "Gas"
                slider.value: car.gasPedal
                slider.onValueChanged: car.gasPedal = slider.value;
                slider.minimumValue: 0
            }

            Pedal {
                width: pedals.pedalWidth
                height: pedals.height * 0.8
                text: "Speed"
                slider.value: car.speedDemand
                slider.onValueChanged: car.speedDemand = slider.value;
                slider.minimumValue: 0
            }

            Pedal {
                width: pedals.pedalWidth
                height: pedals.height * 0.8
                text: "Accel"
                slider.value: car.accelDemand
                slider.onValueChanged: car.accelDemand = slider.value;
                slider.stepSize: 0.1
            }
        }
    }
}
