# dactyl-typesafe-firmware
Really rough (but working) firmware for dactyl-typesafe

# getting started
1. wiring should look something like [this](wiring.png)
1. follow the instructions for setting up the arduino IDE from [bluemicro](http://bluemicro.jpconstantineau.com/docs/)
1. copy [this file](https://github.com/mrjohnk/ADNS-9800/blob/0895bcca4f68c114e5c67aa7a46116cc88fb7cb3/Arduino%20Example%20Sketches/ADNS9800_SROM_A4.ino) to `~/Documents/Arduino/libraries/ADNS9800/ADNS9800_SROM_A4.h`or wherever your libraries are ([see here](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#manual-installation))
1. configure ble/usb: set [this](right/ble.h#L5) to `true` if you want full wireless, `false` if you want a usb keyboard (the two halves still communicate wirelessly)
1. generate some uuids for ble services [here](right/constants.h#L7-L9) and [here](left/constants.h#L7-L9) (make sure they match)

# known issues
1. battery reporting doesn't really work
1. in full wireless mode, the battery on the right half will get drained pretty quickly
1. media keys not working in full wireless (needs a fix [here](right/keyboard_dev.cpp#L330-L343) just haven't had a chance yet)
