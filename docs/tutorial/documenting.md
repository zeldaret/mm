# Documenting

Up: [Contents](contents.md)
Previous: [Data](data.md)

Decompilation is only the first step: since the point of this project is to understand the game better than ever before, the code needs documentation. In this document, we will go through the basic stuff that it's good to do for any actor: we will not try to understand every single thing the actor does in full detail, but try to name the functions and variables usefully for a full documentation pass later to take advantage of.

It is helpful to document the functions and variables in the actor before you Pull Request it. The aim is to provide code that is sufficiently clear to be self-documenting, but it is worth leaving a comment on anything you find obscure or confusing. (Pull Request reviews will let you know if you are leaving too many comments.) Useful things to do documentation-wise:

- Name all (or most) of the functions.
- Name all the variables in the actor struct.
- Create enums for params, and any other numbers that would benefit from that sort of clarity.

You can test things using the practice rom for a retail version (watches and memory view is especially helpful), as well as the generated rom with Project 64 and something like Spectrum.

If you want to use `diff.py` after renaming anything, particularly functions, remember to rerun `make diff-init` so it can use the correct symbols.

Finally, *if you are not sure what something does, either ask or leave it unnamed: it will be less confusing later if things are unnamed than if they are wrongly named*

## EnRecepgirl

The worst part of documentation is finding somewhere to start.



Next: [The merging process](merging.md)