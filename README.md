# Legend of Zelda: Majora's Mask (U) 1.0

This is a decompilation of Legend of Zelda: Majora's Mask (U) 1.0

It builds the following ROM:
* rom.z64 `md5: 2a0a8acb61538235bc1094d297fb6556`

# Installation

## Step 1:

If you're running Windows 10, [install WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10). If you're running an older version of Windows, install a Linux VM. If you're already running a Linux OS, you're good to go.

## Step 2:

Using sudo apt-get, install the following packages:

```
make
git
binutils-mips-linux-gnu
python3
```

## Step 2:
Download build_tools.zip from the Releases section and extract it to the tools folder.

## Step 3:

Open up your .bashrc file (~/.bashrc), scroll to the bottom, and add the following, replacing `/path/to/qemu-mips` with the location the qemu-mips you extracted from the build tools:

```
export QEMU_IRIX="/path/to/qemu-mips"
export MIPS_BINUTILS_PREFIX=mips-linux-gnu-
```

Save and close/reopen your terminal window.

## Step 4:
Make a fork of the main repository https://github.com/Rozelette/Majora-Unmasked.git and clone your fork.

## Step 5:

Navigate to the Majora-Unmasked folder you just cloned. Type the following commands:

```
git submodule update --init --recursive
pip install -r requirements.txt
```

## Step 6:

You will need to acquire a copy of the ROM. The md5 of this ROM should be `2a0a8acb61538235bc1094d297fb6556`.

Once this has been done, type, replacing `<ROM>` with the name of your ROM:
```
./tools/extract_baserom.py <ROM>
```

This will extract all the individual files in the ROM into a newly created baserom folder, as well as decompress the compressed files in a newly created decomp folder.

Next, type:
```
make disasm
```

This will create the build folders as well as a newly created asm folder containing the disassemblies of nearly all the files containing code.

## Step 7:

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
