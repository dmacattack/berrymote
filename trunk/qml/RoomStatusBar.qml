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
    property bool isSettingsPage:         false
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
        // Rectangle containing the title and page dots
        //----------------------------------
        Rectangle
        {
            anchors.centerIn: parent
            height: parent.height

            //----------------------------------
            // txtRoomTitle
            // Room Name/Title
            //----------------------------------
            Text
            {
                id: txtRoomTitle
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: roomStatusBar.roomTitle
                color: roomStatusBar.roomTitleFontColor
                font.pointSize: roomStatusBar.roomTitleFontSize
            }

            //----------------------------------
            // pageDots
            //----------------------------------
            Text
            {
                id: pageDots
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: txtRoomTitle.bottom
                anchors.topMargin: 2
                text: roomStatusBar.isSettingsPage ? "\u25ef \u2b24" : "\u2b24 \u25ef"
                font.pointSize: 8
                color: roomStatusBar.roomTitleFontColor
            }
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
