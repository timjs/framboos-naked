# FramboOS

## Prepare

### Ubuntu
* Install dependencies:
```sh
> sudo apt update
> sudo apt install gcc-arm-none-eabi build-essential qemu-system-arm qemu
```

### Mac
1. Install [Homebrew] (this will also install the XCode Developer Tools if not yet installed)
2. Install dependencies:
   ```sh
   > brew update
   > brew install gcc-arm-embedded make git qemu
   ```

[Homebrew]: https://brew.sh

### Windows
* Install [WSL]
* Open the WSL shell and follow the instructions for Ubuntu above

**Note**
When you're using [WSL] it could be you'll get a significant older version of Qemu which does not recognise `raspi2b` as a virtualisation target.
If you get the error
```
qemu-system-arm: -M raspi2b: unsupported machine type 'raspi2b'
```
change the `TARGET` variable at the top of `build/Makefile` from `raspi2b` to `raspi2` and try again.

[WSL]: https://docs.microsoft.com/en-us/windows/wsl/install

## Build

* `cd` into `build/`
* Run `make build` to build

## Run

* To run in QEMU:
    - `cd` into `build/`,
    - Run `make run`
    - **Note:** `make run` will also build your project, so normally you only need to invoke `make run`
* To run on real hardware:
    - Prepare an SD card using the 'Raspberry Pi Imager': https://www.raspberrypi.com/software/
    - Replace 'kernel7.img' with 'build/kernel7.img'
    - Insert the SD card into the Raspberry Pi and power it up.
    - **Note:** You'll need to run this on a Raspberry Pi 2B.

## Code

If you're using VSCode, you should install some extensions:

* https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd
* https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools
* https://marketplace.visualstudio.com/items?itemName=webfreak.debug

This will enable error and warning squiggles and debugging support (Press F5).

When first running, you may need to update the compilation cache: Press `Control+Shift+P`, then choose `Makefile: Clean configure` in the menu that appears.