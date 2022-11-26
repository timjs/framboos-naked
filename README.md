# FramboOS

## Preparation

### Ubuntu
* Install dependencies: `sudo apt install gcc-arm-none-eabi build-essential qemu`

### Mac
1. Install Homebrew [Brew] (this will also install the XCode Developer Tools if not yet installed)
2. Install dependencies: `brew install gcc-arm-embedded make git qemu`

[Brew]: https://brew.sh

## Windows
* Install [WSL]
* Open the WSL shell and follow the instructions for Ubuntu above

[WSL]: https://docs.microsoft.com/en-us/windows/wsl/install

## Building

* `cd` into `build/`
* Run `make build` to build

## Running

* To run in QEMU:
    - `cd` into `build/`,
    - Run `make run`
    - **Note:** `make run` will also build your project, so normally you only need to invoke `make run`
* To run on real hardware:
    - Prepare an SD card using the 'Raspberry Pi Imager': https://www.raspberrypi.com/software/
    - Replace 'kernel7.img' with 'build/kernel7.img'
    - Insert the SD card into the Raspberry Pi and power it up.
    - **Note:** You'll need to run this on a Raspberry Pi 2B.

## VSCode

If you're using VSCode, you should install some extensions:

* https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd
* https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools
* https://marketplace.visualstudio.com/items?itemName=webfreak.debug

This will enable error and warning squiggles and debugging support (Press F5).

When first running, you may need to update the compilation cache: Press `Control+Shift+P`, then choose `Makefile: Clean configure` in the menu that appears.