# js2xbox

Simple user-space utility to map RG351P input joypad to a virtual Xbox 360 controller; Try to solve the key adaptation problem of RG351P in Batocera.linux and android.

## Building

Just download this repository and invoke `make` (`make release` for optimized build). This project does not depend on any library, only a recent kernel and compiler (c++11) are needed.

## Running

### All commands

```
js2xbox 0.2

Usage: ./js2xbox [options]

Create a new virtual Xbox 360 pad (or other joypad models)
from an existing joypad device (now only PS3)

Options can be:

-h,--help                 Print this screen and quit

-l,--list-pads            Lists all the Joypads supported, both
                          in input and output virtual target

--print-info e            Prints the technical capabilities/info of
                          the selected input Joypad and quit; the e
                          parameter should be the absolute path to the
                          event device (i.e. /dev/input/event22)

--silent                  Do not output any log

-t,--target-pad p         Specify which target pad (p) to use; see names
                          using -l/--list-pads option
```

### Sample usage

```
./js2xbox
```

## License

```
	js2xbox (C) 2017 E. Oriani, ema <AT> fastwebnet <DOT> it

	This file is part of js2xbox.

	js2xbox is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	js2xbox is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with js2xbox.  If not, see <http://www.gnu.org/licenses/>.
```

## Credits
The original code source:
- [js2xbox](https://github.com/Emanem/js2xbox)
