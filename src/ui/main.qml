import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    width: 800
    height: 480
    visible: true
    title: "OwlOS App Installer"
    color: "#E6E6E6"
    visibility: Window.FullScreen

    Column {
        anchors.centerIn: parent
        width: parent.width * 0.9
        spacing: 20

        Text {
            text: "OwlOS Package Installer"
            color: "#4da6ff"
            font.pixelSize: 28
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Input Path File
        Row {
            width: parent.width
            spacing: 10
            
            TextField {
                id: pathInput
                width: parent.width - btnInstall.width - 10
                height: 45
                color: "white"
                placeholderText: "Ketik path file .owl (contoh: /home/pi/SmartHomeApp.owl)"
                background: Rectangle { color: "#333333"; radius: 5 }
                font.pixelSize: 16
                padding: 10
            }

            Button {
                id: btnInstall
                text: installerBackend.isInstalling ? "Memproses..." : "INSTALL PAKET"
                height: 45
                width: 150
                enabled: !installerBackend.isInstalling && pathInput.text.length > 0
                background: Rectangle {
                    color: parent.enabled ? "#4caf50" : "#555555"
                    radius: 5
                }
                contentItem: Text {
                    text: btnInstall.text
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    installerBackend.startInstall(pathInput.text)
                }
            }
        }

        // Terminal Log Viewer
        Rectangle {
            width: parent.width
            height: 250
            color: "black"
            border.color: "#444444"
            radius: 5
            clip: true

            Flickable {
                anchors.fill: parent
                anchors.margins: 10
                contentWidth: width
                contentHeight: logText.height
                
                // Otomatis scroll ke bawah saat log bertambah
                onContentHeightChanged: {
                    if (contentHeight > height) {
                        contentY = contentHeight - height
                    }
                }

                Text {
                    id: logText
                    text: installerBackend.logText
                    color: "#00ff00" // Warna hijau terminal
                    font.family: "Monospace"
                    font.pixelSize: 14
                    width: parent.width
                    wrapMode: Text.Wrap
                }
            }
        }
    }
}