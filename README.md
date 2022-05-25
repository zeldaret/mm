# Legend of Zelda: Majora's Mask (US) 1.0

[![Build Status][jenkins-badge]][jenkins] [![Decompilation Progress][progress-badge]][progress] [![Contributors][contributors-badge]][contributors] [![Discord Channel][discord-badge]][discord]

[jenkins]: https://jenkins.deco.mp/job/MM/job/master
[jenkins-badge]: https://img.shields.io/jenkins/build?jobUrl=https%3A%2F%2Fjenkins.deco.mp%2Fjob%2FMM%2Fjob%2Fmaster

[progress]: https://zelda64.dev/games/mm
[progress-badge]: https://img.shields.io/endpoint?url=https://zelda64.dev/assets/csv/progress-mm-shield.json

[contributors]: https://github.com/zeldaret/mm/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/zeldaret/mm

[discord]: https://discord.zelda64.dev
[discord-badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF

```diff
- WARNING! -

The ROM this repository builds while has a matching checksum cannot be 'shifted' due
to hardcoded pointers which have yet to be dumped. Thus this repository is currently
in an experimental and research phase and cannot currently be used traditionally as a
source code base for general changes.
```

This is a WIP **decompilation** of ***The Legend of Zelda: Majora's Mask***. The purpose of the project is to recreate a source code base for the game from scratch, using information found inside the game along with static and/or dynamic analysis. **It is not producing a PC port.** For more information you can get in touch with the team on our [Discord server](https://discord.zelda64.dev).

The only build currently supported is N64 US, but other versions are planned to be supported.

It currently builds the following ROM:
* mm.us.rev1.rom.z64 `md5: 2a0a8acb61538235bc1094d297fb6556`

**This repo does not include any assets or assembly code necessary for compiling the ROM. A prior copy of the game is required to extract the required assets.**

Please refer to the following for more information:

- [Website](https://zelda64.dev/)
- [Discord](https://discord.zelda64.dev/)
- [How to Contribute](CONTRIBUTING.md)


## Installation

### Windows

For Windows 10, install WSL and a distribution by following this
[Windows Subsystem for Linux Installation Guide](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
We recommend using Debian or Ubuntu 20.04 Linux distributions.


### MacOS

Preparation is covered in a [separate document](docs/BUILDING_MACOS.md).


### Linux (Native or under WSL / VM)

#### 1. Install build dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* binutils-mips-linux-gnu
* python3
* pip3
* libpng-dev

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential binutils-mips-linux-gnu python3 python3-pip libpng-dev
```

#### 2. Clone the repository

Create your own fork of the repository at `https://github.com/zeldaret/mm`. Then clone your fork where you wish to have the project, with the command:

```bash
git clone https://github.com/<YOUR_USERNAME>/mm.git
```

This will copy the GitHub repository contents into a new folder in the current directory called `mm`. Change into this directory before doing anything else:

```bash
cd mm
```

#### 3. Install python dependencies

The build process has a few python packages required that are located in `requirements.txt`.

To install them simply run in a terminal:

```bash
python3 -m pip install -r requirements.txt
```

#### 4. Prepare a base ROM

Copy your ROM to inside the root of this new project directory, and rename the file of the baserom to reflect the version of ROM you are using. ex: `baserom.mm.us.rev1.z64`

#### 5. Make and Build the ROM

To start the extraction/build process, run the following command:

```bash
make init
```

This will extract all the individual files in the ROM into a newly created baserom folder, as well as decompress the compressed files in a newly created decomp folder. This will create the build folders as well as a new folder with the ASM as well as containing the disassemblies of nearly all the files containing code.

This make target will also build the ROM. If all goes well, a new ROM called "mm.us.rev1.rom.z64" should be built and the following text should be printed:

```bash
mm.us.rev1.rom.z64: OK
```

If you instead see the following:

```bash
mm.us.rev1.rom.z64: FAILED
md5sum: WARNING: 1 computed checksum did NOT match
```

This means that something is wrong with the ROM's contents. Either the baserom files are incorrect due to a bad ROM, or some of the code is not matching.

Running `make init` will also make the `./expected` directory and copy all of the files there, which will be useful when running the diff script. The diff script is useful in decompiling functions and can be ran with this command: `./tools/asm-differ/diff.py -wmo3 <insert_function_here>`

**Note**: to speed up the build, you can pass `-jN` to `make setup` and `make`, where N is the number of threads to use in the build, e.g. `make -j4`. The generally-accepted wisdom is to use the number of virtual cores your computer has, which is the output of `nproc` (which should be installed as part of `coreutils`). 
The disadvantage that the ordering of the terminal output is scrambled, so for debugging it is best to stick to one thread (i.e. not pass `-jN`).
(`-j` also exists, which uses unlimited jobs, but is generally slower.)


## Contributing

All contributions are welcome. This is a group effort, and even small contributions can make a difference.
Some tasks also don't require much knowledge to get started.

Please note that is is our strict policy that *Anyone who wishes to contribute to the OOT or MM projects **must not have accessed leaked source code at any point in time** for Nintendo 64 SDK, iQue player SDK, libultra, Ocarina of Time, Majora's Mask, Animal Crossing/Animal Forest, or any other game that shares the same game engine or significant portions of code to a Zelda 64 game or any other console similar to the Nintendo 64.*

Most discussions happen on our [Discord Server](https://discord.zelda64.dev), where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.

For more information on getting started, see our [Contributing Guide](CONTRIBUTING.md) and our [Code Review Guidelines](REVIEWING.md) to see what code quality guidelines we follow.


## FAQ

### Q: Why does MM use transient assembly?
A: It is the view of the MM project leads that transient asm is safer than storing the disassembly in the repo. We feel like the C code is more transformative than a straight disassembly.