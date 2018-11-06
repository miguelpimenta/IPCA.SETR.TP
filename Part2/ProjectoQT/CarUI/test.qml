import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0

Window {
    width: 600
    height: 400
    visible: true
    title: "Quadrados"
    color: "#808080" //"grey"

    Rectangle {
        width: parent.width
        height: parent.height / 2
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "white";
            }
            GradientStop {
                position: 0.50;
                color: "lightblue";
            }
            GradientStop {
                position: 1.00;
                color: "grey";
            }
        }

        Rectangle {
            x: parent.height / 4
            y: parent.height / 4
            width: parent.height / 2
            height: parent.height / 2
            color: "white"
            BorderImage {
                id: img1
                source: "dashboard"
                width: parent.width; height: parent.height
                border.left: 5; border.top: 15
                border.right: 5; border.bottom: 15
                verticalTileMode: BorderImage.Stretch
                horizontalTileMode: BorderImage.Stretch
            }
        }
    }

    Rectangle {
        y: parent.height / 2
        width: parent.width
        height: parent.height / 2
        color: "green"
        opacity: 1
        TextInput {
            text:"Introduzir valor..."
        }
        Rectangle {
            id: qleft
            objectName: "rect1"
            x: parent.width - parent.width / 2
            y: parent.height / 4
            width: parent.height / 2
            height: parent.height / 4
            color: "white"
            KeyNavigation.right: qright
            MouseArea{
                anchors.fill: parent
                onPressed: parent.color = "red"
                onReleased: parent.color = "white"
            }
        }
        Rectangle {
            id: qright
            objectName: "rect2"
            x: parent.width - parent.width / 4
            y: parent.height / 4
            width: parent.height / 2
            height: parent.height / 4
            color: focus ? "white" : "blue"
            KeyNavigation.left: qleft
        }
    }

    Rectangle {
        id: rectangle
        x: 191
        y: 65
        width: 180
        height: 129
        color: "#ffffff"
        radius: 19
        scale: 0.9
        z: 55
        rotation: 30
        transformOrigin: Item.Center
        border.width: 0
    }
}
