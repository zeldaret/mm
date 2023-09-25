# Introduction to git for decomp

`git` is a version control system: it allows you to keep different versions of files at the same time. It does this using a tree system:

- A *repository* is directory containing files managed by git. 
- A repository has one or more *branches*. A branch can be thought of as a pointer to a specific commit.
- A *commit* is one set of changes, the most basic "unit" when working with git. The key point about git is that it is possible to have several commits based on the same one
- A *remote* is another copy of the same repository, usually on another computer or the Internet.

For example,

```bash
Remote
---o---o---o---o

Local
             main
               v
---o---o---o---o
            \
             o---o
                 ^
                 A
```

Each `o` is a commit. The lines show the commit that each commit was based on: we can see in the local there is one commit with two commits based on it. The local has two branches, `main` and `A`, and they currently both point to the commits furthest along their respective chains.

Throughout this guide, stuff in `SCREAMING_SNAKE_CASE` represents fields for you to fill in with the appropriate text, e.g. FILE should be replaced with a particular filename.

## Setting up git

If you are on an ordinary Linux distribution (i.e. not Arch or similar) or WSL, you probably already have git installed, and if not, can get it by running `sudo apt install git` in a terminal window.

git commits are signed with the committer's name and email (if you don't want an actual email address attached to it, GitHub will generate a fake one for you). To set these up for any repository you work on, run

```bash
git config --global user.name "NAME"
git config --global user.email "EMAIL_ADDRESS"
```

(omitting `--global` will set these only for the repository in the current folder).

To make a new repository in a directory:

```bash
git init
```

The repository is considered to have the same name as the directory in which it lives.

The default branch is set to be called `main`. If you want to call it something else, do

```bash
git init -b DEFAULT_BRANCH_NAME
```

Usually when working on decomp you will instead be cloning a repository from GitHub, though.

## Cloning a repository from GitHub

```bash
git clone REMOTE_URL
```

This will clone the repository associated with that URL into a subdirectory of the one you are currently in, with a name based on the repository name. For example,

```bash
git clone git@github.com:zeldaret/mm.git
```

will clone the MM repository into the subdirectory `mm`.

git will automatically name the original remote as `origin`, so for decomp you probably want to use a different name so your own fork on GitHub is `origin`. You can do this:

```bash
git clone -o REMOTE_NAME REMOTE_URL
```

so

```bash
git clone -o upstream git@github.com:zeldaret/mm.git
```

## Configuring remotes

View all remotes associated to this repository. Each remote has a name and an address.

```bash
git remote -v
```

Rename remote `OLD` to `NEW`

```bash
git remote rename OLD NEW
```

Add a new remote

```bash
git remote add NAME URL
```

For example, a typical workflow to get a repository from GitHub is to fork it, then

```bash
git clone -o upstream git@github.com:zeldaret/mm.git
cd mm
git add git@github.com:yourgithubaccount/mm.git
```

## Managing branches

You should always work on a branch, to retain a clean copy of the repository that you know works on the main/main branch, and to enable you to switch between unrelated work easily.

To list the branches you currently have:

```bash
git branch
```

To make a new branch:

```bash
git branch NEW_BRANCH_NAME
```

To change branch:

```bash
git checkout BRANCH_NAME
```

To make a new branch and change to it in one command:

```bash
git checkout -b NEW_BRANCH_NAME
```

To delete a branch (e.g. if definitely no longer needed)

```bash
git branch -d BRANCH_NAME
```

## Committing

To make git remember your changes, you need to make a commit. Ordinarily a commit applies to only files that are *staged*.

To add files to staging:

```bash
git add FILES
```

To commit staged files:

```bash
git commit
```

This will open a text editor to write a commit message. It is generally expected that commit messages are informative and short. If you want to write the commit message in the terminal instead,

```bash
git commit -m "COMMIT_MESSAGE"
```

To unstage a file (but keep the changes)

```bash
git reset FILE
```

(To unstage everything, `git reset`)

To revert a file to its state at the last commit:

```bash
git reset --hard FILE
```

## Merging and Rebasing

Having worked separately on a branch A, you often want to incorporate changes from branch B into branch A. Considering the tree/commit structure, there are two possible ways to do this:

- Stick the two branches back together at their current commits. This is called *merging* B into A: diagrammatically,

```bash
---o---o---o---o A
    \
     o---o---o B
```

to

```bash
---o---o---o---o---m A
    \             /
     o-----o-----o B
```

where `m` is a *merge commit*.

- Go back to the common ancestor of A and B, take all the commits on A since then, and attempt to apply them to the tip of B. This is called *rebasing* A on B.

```bash
---o---o---o---o A
    \
     o---o---o B
```

to

```bash
---o
    \
     o---o---o---o---o---o A
             ^
             B
```

(Notice that in neither case is B itself destroyed.)

Both have advantages and disadvantages.

- Merging is conceptually simpler, but generates an additional commit.
- Rebasing results in cleaner history and is usually easier to do because there are fewer changes in each commit, but makes it much harder to follow what has changed between commits before and after: *you should not rebase a branch other people are looking at* (e.g. in GitHub reviews, but also in other collaboration).

If you realise you have made a mistake while still merging, you can run

```bash
git merge --abort
```

or

```bash
git rebase --abort
```

as appropriate to stop attempting to merge/rebase.

As such, if you only want to learn one of these, learn merging.

### Conflict resolution

If the two branches have both touched the same or nearby lines, git will not know which you want to keep. It will therefore pause the merge/rebase and tell you to decide. You will find a section of the file that looks like this:

```bash
<<<<<<< A
Some code
=======
Some other code
>>>>>>> B
```

from which you should pick one (or combine parts of both as appropriate), then delete the rest. (You definitely do not want the git artefacts left in!)

Notice also that the changes are applied in opposite ways in each case: merging B into A, the incoming changes are from B, whereas when rebasing, they come from A. *This means the conflict resolution in one is in the opposite order from the other.*

## Keeping up to date with remotes

To update git's information about remotes:

```bash
git fetch REMOTE_NAME
```

Not specifying `REMOTE_NAME` will fetch from the remote with the branch that tracks the current one.

To fetch a remote branch's changes and merge them into the current branch:

```bash
git pull REMOTE_NAME BRANCH_NAME
```

To fetch and rebase the current branch on a remote branch:

```bash
git pull --rebase REMOTE_NAME BRANCH_NAME
```

It's generally better to use fetch and then merge/rebase separately, though, at least until you're more experienced with git.

To update a remote with changes from the current branch:

```bash
git push
```

To send changes ignoring any changes to the remote branch since local and remote went out of sync,

```bash
git push --force
```

To push a new branch to a remote and set up a branch that *tracks* it on there, you need to specify which remote to push it to:

```bash
git branch -u REMOTE_NAME
```

## Stashing

You may want to store your current changes without actually committing thhem, for example if you're halfway through something but want new changes from a remote. Running

```bash
git stash
```

will save changes to a "stash" that can be applied later, even to a different branch, with

```bash
git stash apply
```

which keeps the stash, or

```bash
git stash pop
```

which applies, and deletes it if application was successful.

You can also name and delete stashes and so on.

## Repository information

To get general information about what branch you are on, staged and modified files:

```bash
git status
```

This will also indicate any files with merge conflicts.

To see a line-by-line description of the changes currently made:

```bash
git diff
```

(you can also diff 2 branches or 2 commits)

git's most general and powerful information command is `log`, which is far too extensive to cover here.

## GitHub

Things are a little different on GitHub compared to working locally.

To make your own copy of a repository, click `Fork`.

Most repositories do not let people push to them directly. Instead, you make a Pull Request (PR) for merging your branch into one of theirs: this also allows other people to review your work. A Pull Request cannot be merged unless it has no conflicting files. We also use a continuous integration system called Jenkins to ensure that the branch's files are correctly formatted, the it builds the rom correctly, and produces no new warnings; this will usually automatically run whenever you push new changes.

*A branch used for a PR is a public branch, so do not rebase it.* Apart from the usual problems with other people looking at your changes, it will detach all the GitHub review comments from where they are in the code.

It is possible to fix merge conflicts on GitHub, but not recommended. GitHub can do a few other git-related things, but most of the time it's just simpler to do it locally.

### Fetch and Merge

To fetch and merge on GitHub, navigate to your personal fork of the repository `(e.g. github.com/<username>/mm)`. On this page there is a bar that will state whether or not the repository is up to date or not. If it is not up to date it will inform what is different. On the right side of that bar there is a drop down menu labeled "Fetch upstream", you can click this and there will be a button to "Fetch and Merge". Once this is done a `git pull` can be done locally to get all the new changes.

### Code Reviews

GitHub has the ability to review changes in a pull request one file at a time. When reviewing, you can review specific changes or comment on the file overall. To start a review:

- Go to the repository and click "Pull Requests"

- Click on a pull request to review

On the conversation tab you can leave general comments and reply to any other comments that have been made.

On the "Files changed" tab you will see the files changed in the pull request. You can change the format of the diff view in this tab by clicking the gear and choosing the unified or split view.

To leave a comment, hover over the line of code where you'd like to add a comment, and click the blue "+" icon. To comment on a block of multiple lines, click and drag the range of lines you wish to comment, then click the blue icon.

Optionally, to suggest a specific change to the line(s) , click the `+/-` icon then edit the text within the suggestion block.

Once finished, click the "Review changes" and type a comment summarizing proposed changes and comments.

### Giving credit to others

If you want to credit other people who have contributed to a PR you have made, you can use the "Co-authored-by"

```bash
NORMAL_COMMIT_MESSAGE

Co-authored-by: GITHUB_USERNAME <GITHUB_EMAIL>
```

Note the blank line and the `<>` around the email. More information on precisely how to do this can be found in GitHub's own docs: <https://docs.github.com/en/pull-requests/committing-changes-to-your-project/creating-and-editing-commits/creating-a-commit-with-multiple-authors>

## More information

This guide has only covered the basics that are required to work with git on a decomp repository. For more information

- Run a command with `--help`
- Ask in Discord
- consult a reference such as https://git-scm.com/docs or https://www.atlassian.com/git/tutorials

*Always ask or research before doing anything drastic, git is sophisticated enough that usually it has a way to resolve problems itself*
