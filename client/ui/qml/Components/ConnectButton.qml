import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import QtQuick.Particles
import Qt5Compat.GraphicalEffects

import ConnectionState 1.0
import PageEnum 1.0
import Style 1.0

Button {
    id: root

    property string defaultButtonColor: RampageStyle.color.paleGray
    property string progressButtonColor: RampageStyle.color.paleGray
    property string connectedButtonColor: RampageStyle.color.bloodRed
    property bool buttonActiveFocus: activeFocus && (Qt.platform.os !== "android" || SettingsController.isOnTv())

    property bool isFocusable: true
    
    Keys.onTabPressed: {
        FocusController.nextKeyTabItem()
    }

    Keys.onBacktabPressed: {
        FocusController.previousKeyTabItem()
    }

    Keys.onUpPressed: {
        FocusController.nextKeyUpItem()
    }
    
    Keys.onDownPressed: {
        FocusController.nextKeyDownItem()
    }
    
    Keys.onLeftPressed: {
        FocusController.nextKeyLeftItem()
    }

    Keys.onRightPressed: {
        FocusController.nextKeyRightItem()
    }
        
    implicitWidth: 190
    implicitHeight: 190

    text: ConnectionController.isConnected ? "PROTECTED" : ConnectionController.isConnectionInProgress ? "CONNECTING..." : "RAMPAGE"

    Connections {
        target: ConnectionController

        function onPreparingConfig() {
            PageController.showNotificationMessage(qsTr("Unable to disconnect during configuration preparation"))
        }
    }

    background: Item {
        implicitWidth: parent.width
        implicitHeight: parent.height
        transformOrigin: Item.Center

        Shape {
            id: backgroundCircle
            width: parent.implicitWidth
            height: parent.implicitHeight
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            layer.enabled: true
            layer.samples: 4
            layer.smooth: true
            layer.effect: DropShadow {
                anchors.fill: backgroundCircle
                horizontalOffset: 0
                verticalOffset: 0
                radius: root.buttonActiveFocus ? 10 : ConnectionController.isConnected ? 15 : 10
                samples: root.buttonActiveFocus ? 25 : ConnectionController.isConnected ? 35 : 25
                color: root.buttonActiveFocus ? RampageStyle.color.paleGray : ConnectionController.isConnected ? RampageStyle.color.bloodGlow : RampageStyle.color.goldenApricot
                source: backgroundCircle
            }

            Behavior on color {
                PropertyAnimation { duration: 400 }
            }

            ShapePath {
                fillColor: RampageStyle.color.transparent
                strokeColor: RampageStyle.color.paleGray
                strokeWidth: root.buttonActiveFocus ? 1 : 0
                capStyle: ShapePath.RoundCap

                PathAngleArc {
                    centerX: backgroundCircle.width / 2
                    centerY: backgroundCircle.height / 2
                    radiusX: 94
                    radiusY: 94
                    startAngle: 0
                    sweepAngle: 360
                }
            }

            ShapePath {
                id: innerRing
                fillColor: RampageStyle.color.transparent
                strokeColor: {
                    if (ConnectionController.isConnectionInProgress) {
                        return RampageStyle.color.darkCharcoal
                    } else if (ConnectionController.isConnected) {
                        return connectedButtonColor
                    } else {
                        return defaultButtonColor
                    }
                }
                strokeWidth: root.buttonActiveFocus ? 2 : 3
                capStyle: ShapePath.RoundCap

                Behavior on strokeColor {
                    PropertyAnimation { duration: 400 }
                }

                PathAngleArc {
                    centerX: backgroundCircle.width / 2
                    centerY: backgroundCircle.height / 2
                    radiusX: 93 - (root.buttonActiveFocus ? 2 : 0)
                    radiusY: 93 - (root.buttonActiveFocus ? 2 : 0)
                    startAngle: 0
                    sweepAngle: 360
                }
            }

            Rectangle {
                id: bloodFill
                width: backgroundCircle.width - 12
                height: backgroundCircle.height - 12
                radius: width / 2
                anchors.centerIn: parent
                color: ConnectionController.isConnected ? RampageStyle.color.bloodDark : RampageStyle.color.transparent
                opacity: ConnectionController.isConnected ? 0.6 : 0

                Behavior on color {
                    PropertyAnimation { duration: 500 }
                }
                Behavior on opacity {
                    PropertyAnimation { duration: 500 }
                }
            }

            MouseArea {
                anchors.fill: parent

                cursorShape: Qt.PointingHandCursor
                enabled: false
            }
        }

        Shape {
            id: shape
            width: parent.implicitWidth
            height: parent.implicitHeight
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            layer.enabled: true
            layer.samples: 4

            visible: ConnectionController.isConnectionInProgress

            ShapePath {
                fillColor: RampageStyle.color.transparent
                strokeColor: RampageStyle.color.paleGray
                strokeWidth: 3
                capStyle: ShapePath.RoundCap

                PathAngleArc {
                    centerX: shape.width / 2
                    centerY: shape.height / 2
                    radiusX: 93
                    radiusY: 93
                    startAngle: 245
                    sweepAngle: -180
                }
            }

            RotationAnimator {
                target: shape
                running: ConnectionController.isConnectionInProgress
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 1000
            }
        }

        ParticleSystem {
            id: bloodSystem
            running: ConnectionController.isConnected
        }

        Emitter {
            system: bloodSystem
            enabled: ConnectionController.isConnected
            x: parent.width * 0.15
            y: parent.height - 4
            width: parent.width * 0.7
            height: 6
            emitRate: 10
            lifeSpan: 1800
            size: 3
            sizeVariation: 2
            velocity: PointDirection { y: 30; yVariation: 20; xVariation: 10 }
            acceleration: PointDirection { y: 60 }
        }

        ImageParticle {
            system: bloodSystem
            color: RampageStyle.color.bloodDrop
            colorVariation: 0.3
            alpha: 0.8
            alphaVariation: 0.3
        }
    }

    contentItem: Text {
        height: 24

        font.family: "PT Root UI VF"
        font.weight: 700
        font.pixelSize: 20

        color: ConnectionController.isConnected ? RampageStyle.color.bloodGlow : defaultButtonColor
        text: root.text

        Behavior on color {
            PropertyAnimation { duration: 400 }
        }

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    onClicked: {
        ConnectionController.connectButtonClicked()
    }

    Keys.onEnterPressed: this.clicked()
    Keys.onReturnPressed: this.clicked()
}
