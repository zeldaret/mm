# systray

This directory contains a Go application that shows a system tray, which the Python code interacts with.

It is a fork of https://github.com/felixhao28/systray-portable.

To build it:

- install Go
- if on Linux, install dependencies: `libgtk-3-dev`, `libappindicator3-dev`
- run `go build`

If on Windows, this needs to be done *outside* of WSL.
