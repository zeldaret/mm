Useful Tips and Tricks With Git 
=================================

Git is the distributed version control system of choice for this project. It will be the main way you will be able to get the latest updates to the project and contribute your own if you so choose.

When it comes to Git, there are different ways that you can do commands: command line or a Graphical User Interface(GUI). The GUI that will be used is within VS Code, or on the web browser. Where possible, both styles will be shown.


## Making a New Branch

When developing in a large project such as this one, it is a good idea to use branches. Branches in git are a pointer to a snapshot of your changes. When you want to add in a new actor or even make your own custome changes, you will want to make a new branch. This makes it harder for unstable code to get merged into the main code, it also provides the ability to clean up your own code before merging it into the main branch.

To create a new branch on the command line there are a couple of different ways:

- The first way is creating a branch first then navigating to the branch
  ``` 
  git checkout <branch-name>
  ```
  This will create a branch, but will not put you in that branch. To navigate into the branch you will need to "checkout" the branch by entering
  ```
  git checkout <branch-name>
  ```
- An alternative way to checkout to a new branch is by the following command:
    ```
    git checkout -b <branch-name>
    ```
    This will create a new branch from whatever branch you were on

<mark>IMPORTANT</mark> - When making new branches it is recommended to do this off of the master/main branch

## Remote Repositories

When you fork a repository you created your own copy of the code base. If you want to contribute or pull in any updates to the codebase, you will need to add a remote repository.

To add a new upstream repository that will be synced with your fork:
```
git remote add upstream https://github.com/zeldaret/mm.git
```

## Merging and Rebasing

If you have a remote repository setup, you can pull and merge in updates to the repository. In this project we use merging as to preserve the history of the repository, so the focus will be on how to merge instead of rebasing.

1. Syncing a fork from command line
    
    From your terminal navigate to the repository and make sure you are in the master branch then run 
    ```
    git fetch upstream
    ```
    this will fetch all the upstream changes. To merge them in run
    ```
    git merge upstream/master
    ```

2. Syncing from the Web UI

    - On GitHub, navigate to the main page of the forked repository that you want to sync with the upstream repository.
    - Select the Fetch upstream drop-down.
    - Review the details about the commits from the upstream repository, then click Fetch and merge

    If the changes from the upstream repository cause conflicts, GitHub will prompt you to create a pull request to resolve the conflicts. This can be done in VS Code or the command line. 