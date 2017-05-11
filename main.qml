import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import be.codeminded.asyncundo 1.0
Window {
    visible: true
    width: 360
    height: 360
    Editor {
        id: editor
        onUndoFinished: text.text = "undo"
        onRedoFinished: text.text = "redo"
        onExample1Finished: text.text = "whoohoo " + status.example1
    }
    Text {
        id: text
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    Action {
        shortcut: "Ctrl+z"
        onTriggered: editor.undoAsync()
    }
    Action {
        shortcut: "Ctrl+y"
        onTriggered: editor.redoAsync()
    }
    Button  {
        onClicked: editor.example1Async(99);
    }
}
