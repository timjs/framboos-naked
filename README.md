# FramboOS

## Prepare

### Ubuntu

0. Be sure you're on Ubuntu 22.04 LTS or higher:
   ```sh
   lsb_release -a
   ```
   otherwise do a release upgrade:
   ```sh
   > sudo apt update
   > sudo do-release-upgrade
   ```
1. Update Apt and install dependencies:
   ```sh
   > sudo apt update
   > sudo apt install gcc-arm-none-eabi build-essential qemu-system-arm qemu
   ```
2. You should have Qemu version 6 or higher to emulate FramboOS.
   Check this by running:
   ```sh
   > qemu-system-arm --version
   ```

### Mac

1. Install [Homebrew] (this will also install the XCode Developer Tools if not yet installed).
2. Update Brew and install dependencies:
   ```sh
   > brew update
   > brew install gcc-arm-embedded make git qemu
   ```
3. You should have Qemu version 6 or higher to emulate FramboOS.
   Check this by running:
   ```sh
   > qemu-system-arm --version
   ```

[Homebrew]: https://brew.sh

### Windows

1. Make sure your Windows installation is up to date.
2. Install [WSL] using PowerShell:
   ```sh
   > wsl --install
   ```
   ...or make sure you're on the latest [WSL] by running in PowerShell:
   ```sh
   > wsl --update
   ```
3. Open the WSL shell and follow the instructions for Ubuntu above.

[WSL]: https://docs.microsoft.com/en-us/windows/wsl/install

#### Unsupported machine type `raspi2b`

When you're using [WSL] it could be you'll get a significant older version of Qemu which does not recognise `raspi2b` as a virtualisation target.
If you get the error:
```
qemu-system-arm: -M raspi2b: unsupported machine type 'raspi2b'
```
Please make sure you're using Qemu 6 or higher!

#### Gtk initialisation failed

When you're Windows install is not completely up to date, you'll get a [WSL] version which is too old.
If you get the error:
```
Unable to init server: Could not connect: Connection refused
gtk initialisation failed
```
Make sure that:
1. You installed [KB5020030] by going to "Settings" > "Update & Security" > "Windows Update". In the "Optional updates available" area, you’ll find the link to download and install the update.
2. Run using PowerShell:
   ```sh
   > wsl --update
   ```
3. Reboot your machine.

See also this [AskUbuntu question](https://askubuntu.com/questions/1389908/running-gui-apps-under-wsl/1389923#1389923).

[KB5020030]: https://support.microsoft.com/en-gb/topic/november-15-2022-kb5020030-os-builds-19042-2311-19043-2311-19044-2311-and-19045-2311-preview-237a9048-f853-4e29-a3a2-62efdbea95e2


## Build

1. `cd` into `build/`.
2. Run `make build` to build.

## Run

### Run in QEMU

1. `cd` into `build/`,
2. Run `make run`

**Note:** `make run` will also build your project, so normally you only need to invoke `make run`

### Run on real hardware

1. Prepare an SD card using the 'Raspberry Pi Imager': https://www.raspberrypi.com/software/
2. Replace 'kernel7.img' with 'build/kernel7.img'
3. Insert the SD card into the Raspberry Pi and power it up.

**Note:** You'll need to run this on a Raspberry Pi 2B.

## Code

If you're using VSCode, you should install some extensions:

* https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd
* https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools
* https://marketplace.visualstudio.com/items?itemName=webfreak.debug

This will enable error and warning squiggles and debugging support (Press F5).

When first running, you may need to update the compilation cache: Press `Control+Shift+P`, then choose `Makefile: Clean configure` in the menu that appears.