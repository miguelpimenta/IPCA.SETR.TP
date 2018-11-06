import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0

Window {
    id: window
    width: 1354
    height: 500
    visible: true
    title: "CarUI"
    color: "#808080"

    // Background
    BorderImage {
        id: dBoard
        objectName: "dashBoard"
        source: "dashboard"
        width: parent.width
        height: parent.height

        // Left Blinker
        BorderImage {
            id: bLeft
            objectName: "bLeft"
            source: "blinkLeft"
            visible: false
            x: 615
            y: 170
        }

        // Right Blinker
        BorderImage {
            id: bRight
            objectName: "bRight"
            source: "blinkRight"
            visible: false
            x: 695
            y: 170
        }

        // Wheel
        BorderImage {
            id: wheel
            objectName: "wheel"
            source: "wheel"
            x: 625
            y: 50
            transform: Rotation {
                id: wheelRot
                objectName: "wheelRot"
                origin.x: 52
                origin.y: 52
            }
            // From the book "Game Programming With Qt"
            Behavior on rotation {
                SmoothedAnimation {
                    velocity: 50
                }
            }
        }

        // Gas
        BorderImage {
            id: gas
            source: "gas"
            x: 540
            y: 280
        }

        // Buzzer
        BorderImage {
            visible: false
            id: buzzer
            objectName: "buzzer"
            width: 35
            height: 35
            source: "buzzer"
            x: 760
            y: 290
        }

        // Temp
        Rectangle
        {
            x: 680
            y: 290
            Text {
                id: temper
                objectName: "temper"
                text: '0'
                color: "yellow"
                font {
                    family: 'Courier';
                    pixelSize: 50;
                    bold: true;
                    capitalization: Font.ExtraBold
                }
            }
        }

        // Speed Light
        Rectangle {
            visible: false
            id: spdLight
            objectName: "spdLight"
            x: 110
            y: 65
            width: 330
            height: 330
            color: "white"
            opacity: 0.2
            radius: width*0.5
        }

        // Speed Marker
        BorderImage {
            id: marker1
            objectName: "marker1"
            source: "marker"
            x: 145
            y: 210
            transform: Rotation {
                id: markerSpd
                objectName: "markerSpd"
                origin.x: 135
                origin.y: 22
            }
            // From the book "Game Programming With Qt"
            Behavior on rotation {
                SmoothedAnimation {
                    velocity: 50
                }
            }
        }

        // RPMs Light
        Rectangle {
            visible: false
            id: rotLight
            objectName: "rotLight"
            x: 915
            y: 65
            width: 330
            height: 330
            color: "white"
            opacity: 0.2
            radius: width*0.5
        }

        // RPMs Marker
        BorderImage {
            id: marker2
            objectName: "marker2"
            source: "marker"
            x: 950
            y: 210
            transform: Rotation {
                id: markerRot
                objectName: "markerRot"
                origin.x: 135
                origin.y: 22
            }
            // From the book "Game Programming With Qt"
            Behavior on rotation {
                SmoothedAnimation {
                    velocity: 50
                }
            }
        }

        // Gears
        Rectangle {
            id: gear
            objectName: "gear"
            x: 525
            //x: 555
            //x: 590
            //x: 625
            //x: 665
            //x: 700
            //x: 740
            //x: 780
            y: 415
            width: 25
            height: 35
            radius: width * 0.8
            color: "yellow"
            opacity: 0.2
        }

    }

}
