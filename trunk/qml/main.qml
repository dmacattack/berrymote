import QtQuick 2.5
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window
{
    id: rootWindow
    visible: true
    width: 240
    height: 320

    RadialGradient
    {
        anchors.fill: parent
        verticalOffset: 100
        gradient: Gradient
        {
            GradientStop { position: 0.0; color: colorGradientStart }
            GradientStop { position: 0.7; color: colorGradientStop }
        }
    }

    //----------------------------------
    // local properties
    //----------------------------------
    readonly property int drawerClosedHt: 20
    readonly property int maxDrawerY: rootWindow.height - drawerClosedHt
    readonly property int drawerMiddleThreshold: rootWindow.height * 0.5 // at the 75% mark
    readonly property int maxEasingDuration: 500 // 500 ms
    readonly property int gridItemWd: 80
    readonly property int gridItemSpacing: 20
    readonly property string drawerColor: "#E0555555"
    readonly property string drawerFontColor: "white"

    // colors generated from
    // https://coolors.co/171a21-606572-7988aa-91acea-afc5f7
    readonly property string colorDkBlue:     "#171A21"
    readonly property string colorGreyBlue:   "#606572"
    readonly property string colorMediumBlue: "#7988AA"
    readonly property string colorBlue:       "#91ACEA"
    readonly property string colorLightBlue:  "#AFC5F7"
    // bg gradient colors
    readonly property string colorGradientStart : "#EDFACE"
    readonly property string colorGradientStop  : "#055F79"

    // fonts
    FontLoader
    {
        id: fontAwesome;
        source: "qrc:/fonts/fontAwesomev5.5.0.otf"
    }

    //----------------------------------
    // signals
    //----------------------------------
    signal buttonClick(int btnId);

    //----------------------------------
    // roomStatusBar
    // status bar of this room/system events
    //----------------------------------
    RoomStatusBar
    {
        id: roomStatusBar
        objectName: "roomStatusBar"
        width: parent.width
        height: drawerClosedHt
        anchors.top: parent.top
    }

    Rectangle
    {
        id: rectPages
        color: "transparent"
        height: rootWindow.height - drawerClosedHt*2
        width: rootWindow.width * 2
        x: 0
        y: 0

        //----------------------------------
        // gridSuperButtons
        //----------------------------------
        Grid
        {
            id: gridSuperButtons
            objectName: "gridSuperButtons"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: (rootWindow.width - gridSuperButtons.width)/2
            spacing: gridItemSpacing
            columns: 2
            rows: 3

            SuperButton { title: "Power";       color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf011"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
            SuperButton { title: "Fan";         color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf72e"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
            SuperButton { title: "Living Room"; color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf4b8"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
            SuperButton { title: "TV Room";     color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf26c"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
            SuperButton { title: "Wifi";        color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf1eb"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
            SuperButton { title: "Settings";    color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf013"; buttonClickFn: buttonClick; width: gridItemWd; height: width }
        }


        // dummy rectangle for the settings page
        Rectangle
        {
            width: 100
            height: 100
            color: "red"
            anchors.top: parent.top
            anchors.right: parent.right
        }

        //----------------------------------
        // draggingMouse
        // mouse event handling for opening/closing the drawer
        // with slide or click events
        //----------------------------------
        MouseArea
        {
            id: pagingMouse
            anchors.fill: rectPages
            drag.target: rectPages
            drag.axis: Drag.XAxis
            drag.maximumX: 0
            drag.minimumX: -rootWindow.width

            property int startX: 0

            onPressed:
            {
                startX = rectPages.x;
            }

            onReleased:
            {
                var endX = rectPages.x;

                console.log("x start/stop = " + startX + ", " + endX);

                if (endX < startX)
                {
                    console.log("show RIGHT page");
                    animPageSwitch.switchToRightPage(endX, -240);

                }
                else if (endX > startX)
                {
                    console.log("show LEFT page");
                    animPageSwitch.switchToLeftPage(endX, 0);
                }
                else
                {
                    // do nothing the page was just clicked
                }
            }



        /*
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
            */

        } // ~MouseArea

        //----------------------------------
        // animOpenCloseDrawe
        // Animation to open or close the drawer
        //----------------------------------
        NumberAnimation on x
        {
            id: animPageSwitch
            from: 0
            to: 0
            duration: rootWindow.maxEasingDuration
            easing.type: Easing.Linear
            running: false

            // switch to the left page
            function switchToLeftPage(startX, endX)
            {
                switchPage(startX, endX, true);
            }

            // switch to the right page
            function switchToRightPage(startX, endX)
            {
                switchPage(startX, endX, false);
            }

            // set the animation end points, and duration and start the animation
            function switchPage(startX, endX, isClosing)
            {
                this.from = startX;
                this.to = endX;

                if (!isClosing)
                {
                    var dur = rootWindow.maxEasingDuration * (rectPages.width - startX) / rectPages.width;
                    console.log("easing duration = " + dur);
                    this.duration = dur;

                }
                else
                {
                    var dur2 = rootWindow.maxEasingDuration * startX / rectPages.width;
                    console.log("easing duration = " + dur2);
                    this.duration = dur2;
                }

                this.start();
            }
        } // ~NumberAnimation

    }


    //----------------------------------
    // RoomDrawer
    // slidable drawer to switch between rooms
    //----------------------------------
    RoomDrawer
    {
        id: roomDrawer
        objectName: "roomDrawer"
        visible: false
        width: rootWindow.width
        height: rootWindow.height
        baseColor: rootWindow.drawerColor
        fontColor: rootWindow.drawerFontColor
        buttonClickFn: buttonClick
        x: 0
        y: maxDrawerY

        //----------------------------------
        // local properties
        //----------------------------------
        readonly property int gridItemWd: 65
        readonly property int gridItemSpacing: 20

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

        } // ~MouseArea

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
        } // ~NumberAnimation


        //----------------------------------
        // gridRooms
        // grid of the rooms
        //----------------------------------
        Grid
        {
            id: gridRooms
            objectName: "gridRooms"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100 // (roomDrawer.height - gridRooms.height - txtDrawerTitle.height - roomDrawer.drawerTitleTopMargin)/2
            spacing: roomDrawer.gridItemSpacing
            columns: 1
            rows: 3

            SuperButton { title: "";  color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf4b8"; buttonClickFn: rootWindow.buttonClick; width: roomDrawer.gridItemWd; height: width }
            SuperButton { title: "";  color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf26c"; buttonClickFn: rootWindow.buttonClick; width: roomDrawer.gridItemWd; height: width }
            SuperButton { title: "";  color: colorDkBlue; fontColor: colorLightBlue; fontHighlightColor: colorDkBlue; highlightColor: colorLightBlue; icon: "\uf013"; buttonClickFn: rootWindow.buttonClick; width: roomDrawer.gridItemWd; height: width }
        } //~gridRooms
    } //~RoomDrawer
}
