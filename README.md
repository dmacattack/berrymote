
### SDK/Image Setup
I followed the instructions here mostly to get the SDK setup, with minor changes to the correct build version/etc
https://www.raspberrypi.org/forums/viewtopic.php?t=204529

### IDE Setup
Download Qt Creator and install the SDK for Qt v5.9.7 

### App Build instructions
* Clone the project
* import the project into Qt Creator
* set the build directory
* build using IDE

### Config file
Everything is allocated on the screen from the config file 'berrymote.json' because I don't want to implement an on screen keyboard. Plus its a raspberry pi, chances are you're already configuring things. Also it trims down the code & UI needed for configuring.

The structure of the config file starts with an array of rooms in the format:
* name (string title used for the room)
* icon (the unicode character can be selected from https://fontawesome.com/icons?d=gallery )
  * superButtons (object array)
    * name (string name for the button)
    * icon (the unicode character can be selected from https://fontawesome.com/icons?d=gallery )
    * type (string command type, eg: ir, ip, etc)
    * commands (string of commands, the format of which is dependent on the command type)
    
Example:
```javascript
"rooms":
[
  {
    "name": "TV Room",
    "icon": "\uf26c",
    "superButtons":
    [
      {
        "name": "power",
        "icon": "\uf1eb",
        "type": "ir",
        "cmd" : [ "10101011010" ]
      },
      {
        "name": "Fire TV",
        "icon": "\uf06d",
        "type": "ip",
        "cmd" : [ "10101011010" ]
      }
    ]
  },
      ...
```
