import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Potenciostat UI")


    Column {
        width: 315
        height: 162
        spacing: 20
        anchors.centerIn: parent



    }

    Text {
        id: serialStatusText
        x: 413
        y: 230
        width: 193
        height: 153
        text: pot.statusText
        wrapMode: Text.WordWrap
    }


    Text {
        id: serialStatusText1
        x: 413
        y: 210
        width: 119
        height: 20
        text: "Status:"
    }

    Row {
        x: 15
        y: 76
        spacing: 15
        Text {
            id: name
            y: 12
            text: qsTr("Select port")
        }

        ComboBox {
            id: selectPort
            y: 0
            model: pot.avaliblePorts
        }

        Button {
            id: port
            y: 0
            text: qsTr("Connect")
            enabled: !pot.isConnected
            onClicked: {
                pot.setSelectedPort(selectPort.currentValue)
                pot.openSerialPort()
            }
        }
        Button {
            id: disconect
            y: 0
            text: qsTr("Disconnect")
            enabled: pot.isConnected
            onClicked: {
                pot.closeSerialPort()
            }
        }
        Button {
            id: refresh
            y: 0
            text: qsTr("Refresh ports")
            enabled: !pot.isConnected
            onClicked: {
                pot.getAvaliablePorts()
            }
        }
    }




    Row{
        x: 15
        y: 171
        spacing: 15
        FileDialog {
            id: fileDialog
            selectFolder: true
            title: "Please choose a file"
            folder: shortcuts.home

            onAccepted: {
                console.log("You chose: " + fileDialog.fileUrl.toString().substring(8))
                folderLocation.text = fileDialog.fileUrl
                pot.setFileLocation(fileDialog.fileUrl.toString().substring(8))
                close()
            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: {
                pot.setFileLocation(folder.toString().substring(8))
            }
        }
        Button {
            id: location
            y: 0
            text: qsTr("File Location")
            onClicked: fileDialog.open()
        }

        Text {
            id:folderLocation
            y: 12
            text: fileDialog.folder.toString().substring(8)
        }

    }



    Row {
        x: 15
        y: 281
        Text {
            y: 12
            text: "File name:"
        }

        TextField {
            id: textField
            y: 0
            placeholderText: qsTr("potenciostat_out")
        }

        Text {
            y: 12
            text: ".csv"
        }
    }


    Row {
        id: row
        x: 218
        y: 386
        width: 171
        height: 40
        Button {
            id: start
            y: 0
            text: qsTr("Start")
            enabled: !pot.isRunning && pot.isConnected
            onClicked:{
                textField.text === "" ? pot.setFileName(textField.placeholderText) : pot.setFileName(textField.text)
                pot.sendStart()
            }
        }

        Rectangle {
            y: 5
            anchors.right: row.right
            width: 30
            height: 30
            color: pot.isRunning ? "green" : "red"
            radius: 15
        }

    }





}
