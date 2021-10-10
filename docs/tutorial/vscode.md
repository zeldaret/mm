# VSCode

A lot of people on this project use VSCode as their coding environment, and there are a number of useful plugins available to make work more efficient:

- c/c++ intellisense
- clang-format
- hexinspector (hover on numbers for float and other info)
- numbermonger (hex to decimal and vice versa)
- ~~bracket pair colorizer 2~~ (now obsolete due to VSCode's built-in bracket colouring)
- better mips support



You will probably also find it helpful to watch Fig's video, although it was not meant to be an actual introduction. But it does show various useful features of VSCode, quite apart from the decompilation aspect.

Useful stuff to know:

- Ctrl + Alt + Up/Down (on Windows, on Linux it's Ctrl + Shift + Up/Down or Shift + Alt + Up/Down) gives multicursors across consecutive lines. If you want several cursors in a more diverse arrangement, middle clicking works, at least on Windows.
- Alt + Up/Down moves lines up/down.
- Shift + Alt + Up/Down (Linux: Ctrl + Shift + Alt + Up/Down) copies lines up/down.

- Make use of VSCode's search/search-and-replace features. 
    - Ctrl + Click goes to a definition.
    - Ctrl + F for search in current file
    - Ctrl + H for replace in current file
    - Ctrl + Shift + F for search in all files
    - Ctrl + Shift + H for replace in all files
    - F2 for Rename symbol

Many of VS Code's other shortcuts can be found on [its getting started page](https://code.visualstudio.com/docs/getstarted/keybindings), which also has links to OS-specific PDFs.

## C/C++ configuration

Add the following to the `.vscode/c_cpp_properties.json` file to make VSCode better able to understand the structure of the repository.

```json
{
    "configurations": [
        {
            "name": "Linux",
            "compilerPath": "${default}", // "", maybe?
            "compilerArgs": [
                "-m32",
                "-nostdinc++"
            ],
            "intelliSenseMode": "${default}",
            "includePath": [
                "${workspaceFolder}/**",
                "src",
                "assets",
                "build",
                "include"
            ],
            "defines": [
                "_LANGUAGE_C"
            ],
            "cStandard": "gnu89",
            "cppStandard": "${default}"
        }
    ],
    "version": 4
}
```

## Settings

Add the following to (or create) the `.vscode/settings.json` file for VSCode to search the gitignored asset and assembly files by default:

```json
{
    "search.useIgnoreFiles": false,
    "search.exclude": {
        "**/.git": true,
        "baserom/**": true,
        "build/**": true,
        "expected/**": true,
        "nonmatchings/**": true,
    },
}
```
