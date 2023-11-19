# solidUtility Installation Guide

The latest released version of _solidUtility_ can be found on github at:

https://github.com/SolidFuel/ChanTool/releases/latest

There will be a few files available to help with install.
Below are instructions for each plaform.

## Windows (64 bit)

### Installer
The easiest way to install on windows is to use the included installer.
Download the file `solidUtility-VX.X.X-win64-install.exe`, where X.X.X will 
be the release number.

**Note** Chrome browser will block the download with a warning about it
not being "commonly downloaded". Either use another browser or click through
the warning to download anyway.

### VST3 zip

The zip file `solidUtility-VX.X.X-win64-vst3.zip` contains the VST3 file. Unzip
the archive and move the `solidUtility.vst3` file to the `C:\Program Files\Common Files\VST3`
directory.

**Note** Chrome browser will block the download with a warning about it
not being "commonly downloaded". Either use another browser or click through
the warning to download anyway.

## Linux

### .deb package file

The available `.deb` package is only for the `amd64` architecture.

Download the `solidutility_X.X.X_linux-amd64.deb` file. Install using

```
sudo apt install ./solidutility_X.X.X_linux-amd64.deb
```

This will place the vst into the `/usr/lib/vst3` directory.

### VST3 zip

_Note_ The release builds only work on x86_64 (amd64) architecture.

Unzip the file solidUtility-Vx.x.x-linux-amd64.zip. Place the resulting 
`solidUtility.vst3` directory into `~/.vst3`

This can also be placed in `/usr/local/lib/vst3` for system-wide use. You will
need superuser privileges to do so.
