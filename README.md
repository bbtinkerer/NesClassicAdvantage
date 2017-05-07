# Nintendo Classic Advantage Controller

By bbtinkerer (<http://bb-tinkerer.blogspot.com/>)

## Description
A Nintendo Advantage inspired controller to use with the NES Classic Edition (<http://www.nintendo.com/nes-classic/>) also known as the Nintendo Mini. This project is based off of the Wii RetroPad Adapter project by Bruno Freitas (<https://github.com/bootsector/wii-retropad-adapter>).

The controller emulates a Nintendo Classic controller but without the X/Y/L/R buttons and analog sticks. The home button allows you to return to the menu screen to save states or change game as opposed to pressing the reset button on the console.

## Configuration

Burn Atmega328P with fuses L:0xE2 H:0xDE E:0xFD.

Other Atmel microcontrollers may be used as long as the microcontroller is able to operate at 3.3V, has at least 2 ADC ports and at least 13 digital I/O ports.

## Usage

Use Atmel Studio 7 to build and flash to your microcontroller. Alternatively, build and flash with your favorite AVR tool chain and programmers.

Pin numbers are according to the Arduino pin numbering.

## Information

### 3D Printed Case

ThingiVerse - <http://www.thingiverse.com/thing:2301267>

### YouTube

Breadboard demonstration - <https://youtu.be/zpsMyRHSjoE>

### Known Issues

If you discover any bugs, feel free to create an issue on GitHub fork and
send a pull request.


## Authors

* bbtinkerer (https://github.com/bbtinkerer/)


## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request


## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.