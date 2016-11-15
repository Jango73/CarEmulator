import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: root
    color: "black"

    property double engineRPM: car.engineRPM
    property double speedKMH: car.speedKMH
    property double fuelPercent: car.fuelPercent

    Row {
        anchors.centerIn: parent

        CircularGauge {
            id: engineRPMGauge
            width: height
            height: root.height * 0.98
            anchors.bottom: parent.bottom
            minimumValue: 0
            maximumValue: 6000
            stepSize: 10
            value: engineRPM

            Behavior on value {
                NumberAnimation {
                    duration: 100
                }
            }

            style: CircularGaugeStyle {
                labelStepSize: 1000
                tickmarkStepSize: 1000
            }
        }

        CircularGauge {
            id: speedFuelGauge
            width: height
            height: root.height * 0.60
            anchors.bottom: parent.bottom
            minimumValue: 0
            maximumValue: 100
            stepSize: 0.5
            value: fuelPercent

            style: CircularGaugeStyle {
                labelStepSize: 25
                tickmarkStepSize: 25
                minimumValueAngle: 150
                maximumValueAngle: 30
            }
        }

        CircularGauge {
            id: speedKMHGauge
            width: height
            height: root.height * 0.98
            anchors.bottom: parent.bottom
            minimumValue: 0
            maximumValue: 280
            stepSize: 0.5
            value: speedKMH

            Behavior on value {
                NumberAnimation {
                    duration: 100
                }
            }

            style: CircularGaugeStyle {
                labelStepSize: 30
                tickmarkStepSize: 50
            }
        }
    }
}
