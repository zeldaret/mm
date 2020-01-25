# Legend of Zelda: Majora's Mask (U) 1.0

This is a decompilation of Legend of Zelda: Majora's Mask (U) 1.0

It builds the following ROM:
* rom.z64 `md5: 2a0a8acb61538235bc1094d297fb6556`

# Installation

## Step 1:

If you're running Windows 10, [install WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10). If you're running an older version of Windows, install a Linux VM. If you're already running a Linux OS, you're good to go.

## Step 2:

Install the following packages:

```
make
git
binutils-mips-linux-gnu
python3
pip3
```

For your convience, you can copy the following:

```
sudo apt-get update
sudo apt-get install make
sudo apt-get install git
sudo apt-get install binutils-mips-linux-gnu
sudo apt-get install python3
sudo apt-get install python3-pip
```

## Step 3:
Download build_tools.zip from the Releases section and extract it to the tools folder. This contains the compilers the decompilation uses, as well as a modified version of Qemu to emulate them on a modern Linux system. The compilers must go into the tools folder. Qemu may be placed wherever you like.

## Step 4:

Open up your .bashrc file (~/.bashrc), scroll to the bottom, and add the following, replacing `/path/to/qemu-mips` with the location the qemu-mips you extracted from the build tools:

```
export QEMU_IRIX="/path/to/qemu-mips"
export MIPS_BINUTILS_PREFIX=mips-linux-gnu-
```

Save and close/reopen your terminal window.

## Step 5:
Make a fork of the main repository https://github.com/n64decomp/majora.git and clone your fork.

## Step 6:

Navigate to the folder you just cloned. Type the following commands:

```
git submodule update --init --recursive
pip3 install -r requirements.txt
```

## Step 7:

You will need to acquire a copy of the ROM. The md5 of this ROM should be `2a0a8acb61538235bc1094d297fb6556`.

Once this has been done, type, replacing `<ROM>` with the name of your ROM:
```
./tools/extract_rom.py <ROM>
```

This will extract all the individual files in the ROM into a newly created baserom folder, as well as decompress the compressed files in a newly created decomp folder.

Next, type:
```
make disasm
```

This will create the build folders as well as a newly created asm folder containing the disassemblies of nearly all the files containing code.

## Step 8:

Type the following:
```
make
```

If all goes well, a ROM rom.z64 should be built and the following text should be printed:

`rom.z64: OK `

If you instead see the following:

```
rom.z64: FAILED
md5sum: WARNING: 1 computed checksum did NOT match
```

This means that something is wrong with the ROM's contents. Either the baserom files are incorrect due to a bad ROM, or some piece of code is not matching.
