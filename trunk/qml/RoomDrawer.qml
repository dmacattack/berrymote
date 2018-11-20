import QtQuick 2.0

Item
{
    id: roomDrawer

    //----------------------------------
    // local properties
    //----------------------------------
    property double widthFactor: 0.9
    property string baseColor: "grey"
    property string fontColor: "black"
    property var buttonClickFn: undefined

    // colors generated from
    // https://coolors.co/171a21-606572-7988aa-91acea-afc5f7
    readonly property string colorDkBlue:     "#171A21"
    readonly property string colorGreyBlue:   "#606572"
    readonly property string colorMediumBlue: "#7988AA"
    readonly property string colorBlue:       "#91ACEA"
    readonly property string colorLightBlue:  "#AFC5F7"
    readonly property int drawerTitleTopMargin: 5

    //----------------------------------
    // roomDrawerBG
    // background container for the drawer
    //----------------------------------
    Rectangle
    {
        id: roomDrawerBG
        objectName: "roomDrawer"
        color: "transparent"
        width: roomDrawer.width * widthFactor
        height: roomDrawer.height
        anchors.centerIn: parent

        //----------------------------------
        // roomDrawerTitleBg
        // background container for the drawer title
        // also provides rounded top corners
        //----------------------------------
        Rectangle
        {
            id: roomDrawerTitleBg
            objectName: "roomDrawerTitleBg"
            color: roomDrawer.baseColor
            radius: 15
            width: roomDrawerBG.width
            height: roomDrawer.height * 1.2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            z: 2

            //----------------------------------
            // txtDrawerTitle
            // title text for the drawer
            //----------------------------------
            Text
            {
                id: txtDrawerTitle
                objectName: "txtDrawerTitle"
                anchors.top: parent.top
                anchors.topMargin: roomDrawer.drawerTitleTopMargin
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Rooms"
                color: roomDrawer.fontColor
                z: 3
            }
        }
    }
}
