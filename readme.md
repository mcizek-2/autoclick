# ***Autoclick*** 

This simple program simulates left button mouse clicks
on Linux systems running Xorg. It clicks 100 ms and pauses whenever a
right button is pressed.

## Dependencies:
To install this software you need the gcc compiler and the X11 development libraries. In Ubuntu 20.04 the corresponding package is: libx11-dev.

##Installation:
(Tested on Ubuntu 20.04) 

* Clone the project in your home
folder. 
* Open the terminal in the same folder as the project and run the
make command. 
* Run the command sudo make install.

## Usage: 
To start the program run the command autoclick 

Once the software
starts, it clicks every 100ms. You can pause the clicking by keeping the
right mouse button pressed. To end the clicking, run the command
autoclick.

The recommended usage is to bind this command to some key. I
personally use this together with a corsair gaming mouse and launch
it on a special key press using the ckb-next program. 

## Cleaning up:
In case the software crashes or gets interrupted, you need
to run the command: rm ~/.local/tmp/aclick to cleanup after in in order
to launch it again.

## Uninstalling:
Open the terminal in the folder with the source code and
run the command: sudo make uninstall. 

Alternatively run the command:
sudo rm /usr/local/bin/autoclick
