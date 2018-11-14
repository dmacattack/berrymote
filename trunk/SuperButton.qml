import QtQuick 2.0

Item
{
    id: superButton

    //----------------------------------
    // local properties
    //----------------------------------
    property string color: "red"
    property string highlightColor: "white"
    property string fontColor: "white"
    property string fontHighlightColor: "black"
    property string icon: ""
    property string title: ""
    property var buttonClickFn: undefined
    property int buttonId: -1
    readonly property int fontSize: 35
    readonly property int titleFontSize: 10

    // fonts
    FontLoader
    {
        id: fontAwesome;
        source: "qrc:/fonts/fontAwesomev5.5.0.otf"
    }

    //----------------------------------
    // btnBase
    // Background of the button
    //----------------------------------
    Rectangle
    {
        id: btnBase
        color: parent.color
        radius: width
        anchors.fill: parent

        Text
        {
            id: txtButton
            anchors.centerIn: parent
            font.family: fontAwesome.name
            font.pointSize: superButton.fontSize
            text: superButton.icon
            color: superButton.fontColor
        }

        MouseArea
        {
            anchors.fill: parent

            onPressed:
            {
                // TODO add highlight action
                txtButton.color = superButton.fontHighlightColor;
                btnBase.color = superButton.highlightColor;
            }

            onReleased:
            {
                // TODO remove highlight action
                txtButton.color = superButton.fontColor;
                btnBase.color = superButton.color;

                if (superButton.buttonClickFn != undefined)
                {
                    superButton.buttonClickFn(superButton.buttonId);
                }
            }
        }
    }

    //----------------------------------
    // txtButtonTitle
    // text of what the button does (eg: ceiling fan)
    //----------------------------------
    Text
    {
        id: txtButtonTitle
        anchors.top: btnBase.bottom
        anchors.horizontalCenter: btnBase.horizontalCenter
        text: superButton.title
        color: fontColor
        font.pointSize: superButton.titleFontSize
    }
}
