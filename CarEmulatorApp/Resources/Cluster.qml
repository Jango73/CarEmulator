import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root

    property double engineRPM: car.engineRPM
    property double speedKMH: car.speedKMH

    RowLayout {
        anchors.fill: parent

        CircularGauge {
            id: engineRPMGauge
            minimumValue: 0
            maximumValue: 8000
            stepSize: 10
            value: engineRPM

            Behavior on value {
                NumberAnimation {
                    duration: 1000
                }
            }

            style: CircularGaugeStyle {
                tickmarkStepSize: 1000
            }
        }

        CircularGauge {
            id: speedKMHGauge
            minimumValue: 0
            maximumValue: 280
            stepSize: 2
            value: speedKMH

            Behavior on value {
                NumberAnimation {
                    duration: 1000
                }
            }

            style: CircularGaugeStyle {
                tickmarkStepSize: 30
            }
        }
    }
}
