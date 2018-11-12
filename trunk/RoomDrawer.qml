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
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Rooms"
                color: roomDrawer.fontColor
                z: 3
            }
        }
    }
}
