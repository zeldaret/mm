Reviewing Pull Requests to the Majora's Mask Decompilation Project
=======================================================

Thanks for helping us reverse engineer *The Legend of Zelda: Majora's Mask* for the N64! 
We invite all contributors to participate in our code review program. Every review submitted helps us keep code quality high and code merged in more quickly.

This document is meant to be a set of tips and guidelines for reviewers of pull requests to the project.
For general information about the project, see [our readme](https://github.com/zeldaret/mm/blob/master/README.md).

Most discussions happen on our [Discord Server](https://discord.zelda64.dev) where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.

Useful Links
------------

- [Discord](https://discord.zelda64.dev/) - Primary discussion platform.
- [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation) - We use this to track decompilation progress, not GitHub Issues.

- [Contributing guide](https://github.com/zeldaret/mm/blob/master/CONTRIBUTING.md) - Instructions for contributors.
- [Installation guide](https://github.com/zeldaret/mm/blob/master/README.md#installation) - Instructions for getting this repository set up and built on your machine.

- [Zelda 64 Reverse Engineering Website](https://zelda64.dev/) - Our homepage, with links to other resources.
- [Introduction to OOT decomp](https://github.com/zeldaret/oot/blob/master/docs/tutorial/contents.md) - A very detailed tutorial on how to get started with decomp. For OOT, but largely applicable to MM as well.
- The `#resources` channel on the Discord contains many more links

Getting Started
---------------

### What should I know to take part in the review process?

You should first get yourself familiar with our [Contributing guide](https://github.com/zeldaret/mm/blob/master/CONTRIBUTING.md). It is also recommended that you have already successfully submitted a merged pull request to understand how the process works before submitting a review.

Pull Requests (PRs)
------------

### How to review a Pull Request

- When reviewing a PR it is suggested that you follow the checklist outlined in this section.
- You are not required to check for all of the items in the checklist. It is meant as a guide.
- Once the PR author has addressed all of your comments, you should add a comment with approval to the PR to signify to the project leads that this PR has been through peer review.
- If someone does not address your comments and expresses that a different way is better than yours, look for feedback from other contributors. The project lead will have final say in these situations. All decisions will generally be guided by a consensus of contributors.

### Reviewer Checklist
- [ ] Jenkins build is successful.
   - [ ] `make` builds a matching ROM.
   - [ ] Any new compiler warnings that were added are required for matching. Ensure there is good reason if the warnings files have changed. `./tools/warnings_count/warnings_build_current.txt` and `./tools/warnings_count/warnings_setup_current.txt`
- [ ] Files with NON_MATCHING functions have equivalent behaviour. (This will only be reviewed once we have shiftability since equivalence testing is easiest in game)
- [ ] `code` and `boot` segment files should be documented as much as possible. Overlays with documentation should be complete.
   - [ ] Overlays with documentation should have macros to define access to parameters if the parameter uses bitwise access. The params should have an enum when it makes sense.
- [ ] `format.sh` was run.
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
	  - [ ] "Methods" for objects separate the system from the verb with an underscore (`DmRavine_Init`)
   - [ ] Variable names are `camelCase` (`actionFunc`)
	  - [ ] Global variables start with `g` (`gSaveContext`)
	  - [ ] Static global variables start with `s` (`sSphereInit`)
   - [ ] Macros and enum constants are `SCREAMING_SNAKE_CASE` (`DM_RAVINE_STATE_ACTIVE`)
   - [ ] Trailing commas in array and struct definitions (see `EnJcMatoDamageTable`)
