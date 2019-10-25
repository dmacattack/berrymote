### Parts
* 2.8" 320x240 Capacitive touchscreen (https://www.adafruit.com/product/2423)
* Raspberry Pi Zero W ( https://www.adafruit.com/product/3400 )
* microSD Card (8GB minimum)
* Raspbian image compatible with Adafruit's PiTFT software (I used March 12, 2018 https://downloads.raspberrypi.org/raspbian/images/raspbian-2018-03-14 )
* Ubuntu dev pc (Tested 16.04 LTS & 18.04)
* 2x20 header (optional) or just solder the Pi to the display directly

### PiTFT Setup
* write the rasbian image to the sd card
```bash
sudo dd if=raspbian.img of=/dev/sdc bs=4M conv=fsync
```
* add your wifi credentials & ssh access
** add wpa_supplicant.conf to the boot partition as explained here https://www.raspberrypi-spy.co.uk/2017/04/manually-setting-up-pi-wifi-using-wpa_supplicant-conf/
** add empty file called ssh on the boot partition
* plug in SD card and boot the image, and let any setup occur
* follow the adafruit instructions for the installer script here https://learn.adafruit.com/adafruit-2-8-pitft-capacitive-touch/easy-install-2
```bash
cd ~
wget https://raw.githubusercontent.com/adafruit/Raspberry-Pi-Installer-Scripts/master/adafruit-pitft.sh
chmod +x adafruit-pitft.sh
sudo ./adafruit-pitft.sh
```
** 2.8" capacitive display
** 90 degrees portrait
** console ? No
** HDMI mirror? No
** reboot ? yes
* After rebooting, test the display with :
cat /dev/urandom > /dev/fb1
* You can also test the touchscreen using evtest https://learn.adafruit.com/adafruit-2-8-pitft-capacitive-touch/capacitive-touchscreen

### Qt Setup
I followed mline's instructions here ( https://www.raspberrypi.org/forums/viewtopic.php?t=204529 ), with minor changes to the correct build version/etc & to disable "icu" see below. To summarize:

#### Prepare the Pi
Edit sources list in /etc/apt/sources.list and uncomment the deb-src line
```bash
sudo nano /etc/apt/sources.list
```
Update 
```bash
sudo apt-get update
sudo apt-get dist-upgrade
sudo reboot

sudo rpi-update
sudo reboot
```
Install dependencies
```bash
sudo apt-get build-dep qt4-x11
sudo apt-get build-dep libqt5gui5
sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0
```

#### Prepare the Host
Install dependencies
```bash
sudo apt-get install git bison python gperf
```
Install QtCreator & install 5.9.7 SDK

Create Folder
```bash
sudo mkdir /opt/qt5pi
sudo chown 1000:1000 /opt/qt5pi
cd /opt/qt5pi
```

Clone toolchain
```bash
git clone https://github.com/raspberrypi/tools
```

Add Toolchain to your path locally
export PATH=$PATH:/opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin

or add it to ~/.bashrc & resync bashrc
```bash
source ~/.bashrc
```

Get Qt sources & extract (mline used 5.7.1, which was some time ago. I am using 5.9.7)
```bash
wget https://download.qt.io/official_releases/qt/5.9/5.9.7/single/qt-everywhere-opensource-src-5.9.7.tar.xz
tar xf qt-everywhere-opensource-src-5.9.7.tar.xz
```
Create hf configuration
```bash
cd qt-everywhere-opensource-src-5.9.7/qtbase/mkspecs
cp -R linux-arm-gnueabi-g++ linux-arm-gnueabihf-g++ 
sed -i -e 's/arm-linux-gnueabi-/arm-linux-gnueabihf-/g' linux-arm-gnueabihf-g++/qmake.conf
cd -
```
Get Pi sysroot to your PC
```bash
cd /opt/qt5pi
mkdir sysroot sysroot/usr sysroot/opt
rsync -avz pi@<raspberry pi ipAddress>:/lib sysroot
rsync -avz pi@<raspberry pi ipAddress>:/usr/include sysroot/usr
rsync -avz pi@<raspberry pi ipAddress>:/usr/lib sysroot/usr
rsync -avz pi@<raspberry pi ipAddress>:/opt/vc sysroot/opt
```

This will take a while. If you get Permission issue with vnc, don't worry its not used. OR you can change its permission (chmod 777) & resync.

Create correct symlinks to "missing" libraries
```bash
mv sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0 sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0_backup
ln -s sysroot/opt/vc/lib/libEGL.so sysroot/usr/lib/arm-linux-gnueabihf/libEGL.so.1.0.0

mv sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0 sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0_backup
ln -s sysroot/opt/vc/lib/libGLESv2.so sysroot/usr/lib/arm-linux-gnueabihf/libGLESv2.so.2.0.0

ln -s sysroot/opt/vc/lib/libEGL.so sysroot/opt/vc/lib/libEGL.so.1
ln -s sysroot/opt/vc/lib/libGLESv2.so sysroot/opt/vc/lib/libGLESv2.so.2
```

Convert absolute symlinks into relative symlinks
```bash
wget https://raw.githubusercontent.com/riscv/riscv-poky/master/scripts/sysroot-relativelinks.py
chmod +x sysroot-relativelinks.py
python sysroot-relativelinks.py sysroot
```
Configure the build
With 5.9.7 I had a build error (undefined reference to `__cxa_throw_bad_array_new_length@CXXABI_1.3.8'.), which can be resolved by adding -no-icu to the configure command below
```bash
mkdir qt5build
cd qt5build
../qt-everywhere-opensource-src-5.9.7/configure -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=arm-linux-gnueabihf- -sysroot /opt/qt5pi/sysroot -prefix /usr/local/qt5pi -opensource -confirm-license -skip qtwebengine -skip qtscript -nomake examples -make libs -v -no-icu
```

This will take a while.
the device can be configured to different Pi's. I'm using a Pi Zero W
Raspberry Pi 1 (+ Zero and Zero W): -device linux-rasp-pi-g++
Raspberry Pi 2: -device linux-rasp-pi2-g++
Raspberry Pi 3: -device linux-rpi3-g++
Raspberry Pi 3 with VC4 driver: -device linux-rpi3-vc4-g++

If the configure script cannot find the arm-linux-gnueabihf-g++ (due to conflicts or other) update the command to the full path:
```bash
../qt-everywhere-opensource-src-5.9.7/configure -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=/opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf- -sysroot /opt/qt5pi/sysroot -prefix /usr/local/qt5pi -opensource -confirm-license -skip qtwebengine -skip qtscript -nomake examples -make libs -v -no-icu
```

Make 
```bash
make 
make install
```
This will take even longer. multi-core builds can be executed with make -jX (X = # of cores)

Upload to Pi
```bash
cd /opt/qt5pi
rsync -avz sysroot/usr/local/qt5pi pi@<raspberry pi ipAddress>:/usr/local
```
#### Qt Creator Configuration
* Open Qt Creator
* Tools > Options > Devices > Add
  * Generic Linux Device
  * Host name, ssh key (optional), username, password, etc
* Tools > Build&Run > Debuggers > Add
  * Edit name and path ( /opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gdb )
* Tools > Compilers > Add > GCC > C
  * Edit name and path ( /opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc )
* Tools > Compilers > Add > GCC > C++
  * Edit name and path ( /opt/qt5pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ )
* Tools->Qt Versions->Add
  * Choose /opt/qt5pi/sysroot/usr/local/qt5pi/bin/qmake
* Tools->Kits->Add
  * Edit name
  * Device type: Generic Linux Device
  * Device: Choose prior created raspberry pi device
  * Sysroot: Choose /opt/qt5pi/sysroot
  * C and C++: Choose prior created raspberry pi compilers
  * Debugger: Choose prior created raspberry pi debugger
  * Qt version: Choose prior created raspberry pi qt version

You should be ready to build and deploy Qt applications to the device. By default, the system uses EGLFS for displaying UI, but to be explicit you can launch a UI app as such:
QT_QPA_EGLFS_FB=/dev/fb1 /home/pi/berrymote -platform egfls &

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
