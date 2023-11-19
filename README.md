# solidUtility

Versatile VST3 Channel Utility for Digital Audio Workstations

![Utility UI](docs/utility-ui.png)

## Using

See the [User Manual](docs/USER_MANUAL.md).

## Installing

Please see the [Installation Guide](docs/INSTALLATION_GUIDE.md)

## Building

Build should work for Windows and Linux. There is tooling for MacOS, but I don't
think it works.

```sh
git clone https://github.com/SolidFuel/ChanTool.git
cd ChanTool
cmake -S. -Bbuild
cmake --build build
```

## Technology

- [JUCE](https://juce.com/)

## License/Copyright

ChanTool - Simple DAW Channel Utility (C) 2023 Sulid Fuel

This program is free software: you can redistribute it and/or modify it under
the terms of the **GNU General Public License** as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.

See [the license file](LICENSE) for more details.
