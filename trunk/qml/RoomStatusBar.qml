import QtQuick 2.0

Item
{
    id: roomStatusBar

    //----------------------------------
    // local properties
    //----------------------------------
    property string roomTitle:            ""
    property string roomTitleFontColor:   "black"
    property int roomTitleFontSize:       12
    property int roomIconFontSize:        10
    property string taskBarBgColor:       "transparent"
    property bool wifiConnected:          false
    readonly property int rowIconSpacing: 5

    // fonts
    FontLoader
    {
        id: fontAwesome;
        source: "qrc:/fonts/fontAwesomev5.5.0.otf"
    }

    //----------------------------------
    // taskbarBg
    // background of the task bar
    //----------------------------------
    Rectangle
    {
        id: taskbarBg
        color: taskBarBgColor
        width: parent.width
        height: parent.height

        //----------------------------------
        // txtRoomTitle
        // Room Name/Title
        //----------------------------------
        Text
        {
            id: txtRoomTitle
            text: roomStatusBar.roomTitle
            anchors.centerIn: parent
            color: roomStatusBar.roomTitleFontColor
            font.pointSize: roomStatusBar.roomTitleFontSize
        }

        //----------------------------------
        // rowIcons
        // row of available icons
        //----------------------------------
        Row
        {
            id: rowIcons
            spacing: roomStatusBar.rowIconSpacing
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: roomStatusBar.rowIconSpacing

            //----------------------------------
            // txtWifiIcon
            // wifi icon
            //----------------------------------
            Text
            {
                id: txtWifiIcon
                visible: roomStatusBar.wifiConnected
                text: "\uf1eb"
                font.family: fontAwesome.name
                font.pointSize: roomStatusBar.roomIconFontSize
                color: roomStatusBar.roomTitleFontColor
            }

            //----------------------------------
            // txtBattIcon
            // battery icon
            //----------------------------------
            Text
            {
                id: txtBattIcon
                visible: false
                text: "\uf241"
                font.family: fontAwesome.name
                font.pointSize: roomStatusBar.roomIconFontSize
                color: roomStatusBar.roomTitleFontColor
            }
        }

    }

}
