import QtQuick 2.0

Item
{
    id: superButton
    //----------------------------------
    // local properties
    //----------------------------------
    property string color: "red"
    property var buttonClickFn: undefined
    property int buttonId: -1

    //----------------------------------
    // dummy Rectangle
    // this provides the content of the button
    //----------------------------------
    Rectangle
    {
        color: parent.color
        anchors.fill: parent
        border.color: "white"
        border.width: 0

        MouseArea
        {
            anchors.fill: parent

            onPressed:
            {
                // TODO add highlight action
                parent.border.width = 1;
            }

            onReleased:
            {
                // TODO remove highlight action
                parent.border.width = 0;

                if (superButton.buttonClickFn != undefined)
                {
                    superButton.buttonClickFn(superButton.buttonId);
                }
            }
        }
    }
}
