import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import SortFilterProxyModel 0.2

import PageEnum 1.0
import ContainerProps 1.0
import ContainersModelFilters 1.0
import Style 1.0

import "./"
import "../Controls2"
import "../Controls2/TextTypes"
import "../Config"
import "../Components"

PageType {
    id: root

    Connections {
        target: Qt.application

        function onStateChanged() {
            if (Qt.application.state !== Qt.ApplicationActive) {
                if (homeSplitTunnelingDrawer.isOpened) {
                    homeSplitTunnelingDrawer.closeTriggered()
                }
            }
        }
    }

    Item {
        objectName: "homeColumnItem"

        anchors.fill: parent

        ColumnLayout {
            objectName: "homeColumnLayout"

            anchors.fill: parent
            anchors.topMargin: 12 + PageController.safeAreaTopMargin
            anchors.bottomMargin: 16

            BasicButtonType {
                id: loggingButton
                objectName: "loggingButton"

                property bool isLoggingEnabled: SettingsController.isLoggingEnabled

                Layout.alignment: Qt.AlignHCenter

                implicitHeight: 36

                defaultColor: RampageStyle.color.transparent
                hoveredColor: RampageStyle.color.translucentWhite
                pressedColor: RampageStyle.color.sheerWhite
                disabledColor: RampageStyle.color.mutedGray
                textColor: RampageStyle.color.mutedGray
                borderWidth: 0

                visible: isLoggingEnabled ? true : false
                text: qsTr("Logging enabled")

                Keys.onEnterPressed: this.clicked()
                Keys.onReturnPressed: this.clicked()

                onClicked: {
                    PageController.goToPage(PageEnum.PageSettingsLogging)
                }
            }

            BasicButtonType {
                id: devGatewayButton
                objectName: "devGatewayButton"

                property bool isDevGatewayEnabled: SettingsController.isDevGatewayEnv

                Layout.alignment: Qt.AlignHCenter

                implicitHeight: 36

                defaultColor: RampageStyle.color.transparent
                hoveredColor: RampageStyle.color.translucentWhite
                pressedColor: RampageStyle.color.sheerWhite
                disabledColor: RampageStyle.color.mutedGray
                textColor: RampageStyle.color.mutedGray
                borderWidth: 0

                visible: SettingsController.isDevModeEnabled && isDevGatewayEnabled
                text: qsTr("Dev gateway enabled")

                Keys.onEnterPressed: this.clicked()
                Keys.onReturnPressed: this.clicked()

                onClicked: {
                    PageController.goToPage(PageEnum.PageDevMenu)
                }
            }

            Item {
                Layout.fillHeight: true
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 8

                ConnectButton {
                    id: connectButton
                    objectName: "connectButton"

                    Layout.alignment: Qt.AlignCenter
                }
            }

            Item {
                Layout.fillHeight: true
            }

            BasicButtonType {
                id: splitTunnelingButton
                objectName: "splitTunnelingButton"

                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                leftPadding: 16
                rightPadding: 16

                implicitHeight: 36

                defaultColor: RampageStyle.color.transparent
                hoveredColor: RampageStyle.color.translucentWhite
                pressedColor: RampageStyle.color.sheerWhite
                disabledColor: RampageStyle.color.mutedGray
                textColor: RampageStyle.color.mutedGray
                borderWidth: 0

                buttonTextLabel.lineHeight: 20
                buttonTextLabel.font.pixelSize: 14
                buttonTextLabel.font.weight: 500

                property bool isSplitTunnelingEnabled: IpSplitTunnelingController.isSplitTunnelingEnabled || AppSplitTunnelingController.isSplitTunnelingEnabled ||
                                                       ServersUiController.isDefaultServerDefaultContainerHasSplitTunneling

                text: isSplitTunnelingEnabled ? qsTr("Split tunneling enabled") : qsTr("Split tunneling disabled")

                leftImageSource: isSplitTunnelingEnabled ? "qrc:/images/controls/split-tunneling.svg" : ""
                leftImageColor: ""
                rightImageSource: "qrc:/images/controls/chevron-down.svg"

                Keys.onEnterPressed: this.clicked()
                Keys.onReturnPressed: this.clicked()

                onClicked: {
                    homeSplitTunnelingDrawer.openTriggered()
                }
            }

            AdLabel {
                id: adLabel

                Layout.fillWidth: true
                Layout.preferredHeight: adLabel.contentHeight
                Layout.leftMargin: 16
                Layout.rightMargin: 16
                Layout.topMargin: 22
            }
        }
    }

    HomeSplitTunnelingDrawer {
        id: homeSplitTunnelingDrawer
        objectName: "homeSplitTunnelingDrawer"

        parent: root
    }
}
