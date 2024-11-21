# FramboOS

FramboOS is a minimal operating system (OS) for [Raspberry Pi 2 Model B](https://www.raspberrypi.com/products/raspberry-pi-2-model-b/).
Actually, it is _very_ minimal.
It has a UART interface for logging and an interface to a frame buffer.
That's really it...

FramboOS can be loaded on a Raspberry Pi, but can also be emulated in [Qemu](https://www.qemu.org), which makes development more convenient.
After booting, the only thing you'll see is a default _checkerboard_ screen.

All other things need to be programmed by yourself!


## Prepare

### Ubuntu

1. Be sure you're on Ubuntu 22.04 LTS or higher:
   ```sh
   lsb_release -a
   ```
   otherwise do a release upgrade:
   ```sh
   sudo apt update
   sudo do-release-upgrade
   ```
2. Update Apt and install dependencies:
   ```sh
   sudo apt update
   sudo apt install gcc-arm-none-eabi build-essential qemu-system-arm qemu
   ```
> [!NOTE]
> On Ubuntu 24.04, the qemu dependency must be omitted.
3. You should have Qemu version 6 or higher to emulate FramboOS.
   Check this by running:
   ```sh
   qemu-system-arm --version
   ```

### Mac

1. Install [Homebrew] (this will also install the XCode Developer Tools if not yet installed).
2. Update Brew and install dependencies:
   ```sh
   brew update
   brew install gcc-arm-embedded make git qemu
   ```
3. You should have Qemu version 6 or higher to emulate FramboOS.
   Check this by running:
   ```sh
   qemu-system-arm --version
   ```

[Homebrew]: https://brew.sh

### Windows

1. Make sure your Windows installation is up to date.
2. Install [WSL] using PowerShell:
   ```sh
   wsl --install
   ```
   ...or make sure you're on the latest [WSL] by running in PowerShell:
   ```sh
   wsl --update
   ```
3. Open the WSL shell and follow the instructions for Ubuntu above.

[WSL]: https://docs.microsoft.com/en-us/windows/wsl/install


## Troubleshoot

#### Unsupported machine type `raspi2b`

When you're using [WSL] it could be you'll get a significantly older version of Qemu which does not recognize `raspi2b` as a virtualization target.
If you get the error:
```
qemu-system-arm: -M raspi2b: unsupported machine type 'raspi2b'
```
Please make sure you're using Qemu 6 or higher!

#### Gtk initialization failed

When you're Windows install is not completely up to date, you'll get a [WSL] version that is too old.
If you get the error:
```
Unable to init server: Could not connect: Connection refused
gtk initialisation failed
```
Make sure that:
1. You installed [KB5020030] by going to "Settings" > "Update & Security" > "Windows Update". In the "Optional updates available" area, you’ll find the link to download and install the update.
2. Run using PowerShell:
   ```sh
   wsl --update
   ```
3. Reboot your machine.

See also this [AskUbuntu question](https://askubuntu.com/questions/1389908/running-gui-apps-under-wsl/1389923#1389923).

[KB5020030]: https://support.microsoft.com/en-gb/topic/november-15-2022-kb5020030-os-builds-19042-2311-19043-2311-19044-2311-and-19045-2311-preview-237a9048-f853-4e29-a3a2-62efdbea95e2


## Download

Download the FramboOS source code from its GitHub page.
Clicking the green "Code" button at the top of the page reveals a couple of options.
You can:

* copy the SSH link and clone the repo with Git on the command line;
* clone the repository with [GitHub Desktop](https://desktop.github.com);
* Download a .zip file and unpack it (discouraged)

> [!CAUTION]
> The preferred way is to use Git instead of a .zip download.
> If, during any moment in time, the FramboOS source code gets updated
> you'll be able to merge the differences with your own work by using Git's tools.

## Build

1. `cd` into `build/`.
2. Run `make build` to build.

## Run

### Run in QEMU

1. `cd` into `build/`,
2. Run `make run`

> [!TIP]
> `make run` will also build your project, so normally you only need to invoke `make run`

### Run on real hardware

1. Prepare an SD card using the 'Raspberry Pi Imager': https://www.raspberrypi.com/software/
2. Replace 'kernel7.img' with 'build/kernel7.img'
3. Insert the SD card into the Raspberry Pi and power it up.

> [!IMPORTANT]
> You'll need to run this on a Raspberry Pi 2B.

## Code

You can use any text editor you like to work on FramboOS.
If you don't know what to choose, we recommend using [VSCode](https://code.visualstudio.com) or its nephew [VSCodium](https://vscodium.com).

1. Install [VSCode](https://code.visualstudio.com) or [VSCodium](https://vscodium.com).
2. To enable error and warning squiggles and debugging support install these extensions:
    * https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd
    * https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools
    * https://marketplace.visualstudio.com/items?itemName=webfreak.debug
3. _After_ running a `make build` in the `build/` directory, you may need to update the compilation cache:
    * Press `Control+Shift+P`, then choose _Makefile: Clean configure_ in the menu that appears.
    * Again press `Control+Shift+P`, and choose _Developer: Reload window_.
