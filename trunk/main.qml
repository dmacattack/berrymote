import QtQuick 2.5
import QtQuick.Window 2.2

Window
{
    id: rootWindow
    visible: true
    width: 240
    height: 320
    color: "black"

    //----------------------------------
    // local properties
    //----------------------------------
    property int dummyRectWd: 80
    readonly property int maxDrawerY: rootWindow.height - 20
    readonly property int drawerMiddleThreshold: rootWindow.height * 0.5 // at the 75% mark
    readonly property int maxEasingDuration: 500 // 500 ms
    readonly property int gridItemWd: 80
    readonly property string drawerColor: "#E0555555"
    readonly property string drawerFontColor: "white"

    //----------------------------------
    // gridSuperButtons
    //----------------------------------
    Grid
    {
        id: gridSuperButtons
        objectName: "gridSuperButtons"
        anchors.centerIn: parent
        spacing: 10
        columns: 2
        rows: 3

        Rectangle { color: "red";    width: gridItemWd; height: width }
        Rectangle { color: "blue";   width: gridItemWd; height: width }
        Rectangle { color: "green";  width: gridItemWd; height: width }
        Rectangle { color: "yellow"; width: gridItemWd; height: width }
        Rectangle { color: "purple"; width: gridItemWd; height: width }
        Rectangle { color: "orange"; width: gridItemWd; height: width }
    }

    //----------------------------------
    // RoomDrawer
    // slidable drawer to switch between rooms
    //----------------------------------
    RoomDrawer
    {
        id: roomDrawer
        objectName: "roomDrawer"
        visible: true
        width: rootWindow.width
        height: rootWindow.height
        baseColor: rootWindow.drawerColor
        fontColor: rootWindow.drawerFontColor
        x: 0
        y: maxDrawerY

        //----------------------------------
        // draggingMouse
        // mouse event handling for opening/closing the drawer
        // with slide or click events
        //----------------------------------
        MouseArea
        {
            id: draggingMouse
            anchors.fill: roomDrawer
            drag.target: roomDrawer
            drag.axis: Drag.YAxis
            drag.maximumY: maxDrawerY
            drag.minimumY: 0

            property int startY: 0

            onPressed:
            {
                startY = roomDrawer.y;
            }

            onReleased:
            {
                var endY = roomDrawer.y;

                if (startY < endY)
                {
                    animOpenCloseDrawer.close(endY, draggingMouse.drag.maximumY);
                }
                else if (startY > endY)
                {
                    animOpenCloseDrawer.open(endY, draggingMouse.drag.minimumY);
                }
                else
                {
                    // if the user clicked, then if below half, open, otherwise close
                    if (endY > rootWindow.drawerMiddleThreshold)
                    {
                        animOpenCloseDrawer.open(endY, draggingMouse.drag.minimumY);
                    }
                    else
                    {
                        animOpenCloseDrawer.close(endY, draggingMouse.drag.maximumY);
                    }
                }
            }
        }

        //----------------------------------
        // animOpenCloseDrawe
        // Animation to open or close the drawer
        //----------------------------------
        NumberAnimation on y
        {
            id: animOpenCloseDrawer
            from: 0
            to: 0
            duration: rootWindow.maxEasingDuration
            easing.type: Easing.Linear
            running: false

            // open
            // open the drawer
            function open(startY, endY)
            {
                openClose(startY, endY, true);
            }

            // close
            // close the drawer
            function close(startY, endY)
            {
                openClose(startY, endY, false);
            }

            // set the animation end points, and duration and start the animation
            function openClose(startY, endY, isClosing)
            {
                this.from = startY;
                this.to = endY;

                if (!isClosing)
                {
                    this.duration = rootWindow.maxEasingDuration * (rootWindow.height - startY) / rootWindow.height;
                }
                else
                {
                    this.duration = rootWindow.maxEasingDuration * startY / rootWindow.height;
                }

                this.start();
            }

        }
    }


}










