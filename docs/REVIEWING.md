# Reviewing Pull Requests to the Majora's Mask Decompilation Project

Thanks for helping us reverse engineer *The Legend of Zelda: Majora's Mask*!
We encourage all contributors to participate in code review: this is your codebase too!
Every review submitted helps us keep code quality high and code merged in more quickly.

This document is meant to be a set of tips and guidelines for reviewers of pull requests to the project.
For general information about the project, see [our readme](https://github.com/zeldaret/mm/blob/main/README.md).

Most discussions happen on our [Discord Server](https://discord.zelda64.dev) where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.

Other links are available in the [CONTRIBUTING.md](CONTRIBUTING.md)

## Getting Started

### What should I know to take part in the review process?

You should first famiiarise yourself with our [Contributing guide](CONTRIBUTING.md) and [Style guide](STYLE.md). It is also recommended that you have already successfully submitted a merged pull request to understand how the process works before submitting a review.

## Pull Requests (PRs)

### How to review a Pull Request

- When reviewing a PR it is suggested that you follow the checklist outlined in this section.
- You are not required to go through *every* item in the checklist. It is meant as a guide; if you have only one thing you want to mention, that's fine too.
- Once the PR author has addressed all of your comments, you should add a review with approval to the PR to signify to the project leads that this PR has been through peer review.
- If someone does not address your comments and expresses that a different way is better than yours, look for feedback from other contributors (we encourage discussing this sort of thing in Discord, since long GitHub conversations get hard to read). The project leads will have final say in these situations. All decisions are generally guided by a consensus of contributors.

### Reviewer Checklist

- [ ] Jenkins build is successful.
  - [ ] `make` builds a matching ROM.
  - [ ] `format.py` was run.
  - [ ] `spec` contains correct relocation files.
  - [ ] Any new compiler warnings that were added are required for matching. Ensure there is good reason if the warnings files have changed.
- [ ] Files with `NON_MATCHING` functions have equivalent behaviour.
- [ ] `code` and `boot` segment files should be documented as much as possible. Overlays with documentation should be as complete as is reasonable.
  - [ ] Overlays should have macros to define access to parameters if the parameter uses bitwise access. The params should have an enum when it makes sense.
- [ ] Comments and variables have correct spelling.
- [ ] The following should be declared in an Actor header file. There should be nothing else in the Actor header file.
  - [ ] Main Actor struct
  - [ ] Extern'd initVar data.
  - [ ] Types used in the actor struct. Specific example would be actionFunc typedefs.
  - [ ] Param field macros and/or enums.
  - [ ] For any other additional `enum`/`struct`/`define`/`function`/`global`, there needs to be evidence it is needed in another file.
- [ ] New variables and functions should follow standard naming conventions.
  - [ ] Constants are converted to whichever looks best in context: hexadecimal, decimal, or float
    - [ ] Rotation angles should always be in hexadecimal
    - [ ] Colour values should always be in decimal.
  - [ ] Functions, structs, unions, enums, and typedefs are `TitleCase` (`DmRavine`)
    - [ ] Functions within a system separate the system from the function's own subname with an underscore (`DmRavine_Init`)
  - [ ] Variable names are `camelCase` (`actionFunc`)
    - [ ] Global variables start with `g` (`gSaveContext`)
    - [ ] Static global variables start with `s` (`sSphereInit`)
  - [ ] Macros and enum constants are `SCREAMING_SNAKE_CASE` (`DM_RAVINE_STATE_ACTIVE`)
  - [ ] Trailing commas in array and struct definitions chosen to make it look best (see e.g. `EnJcMatoDamageTable`)

etc.
