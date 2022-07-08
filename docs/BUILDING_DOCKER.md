# Building using Docker

## Dependencies

You will need [Docker](https://docs.docker.com/get-docker/) Follow the instructions for your operating system.

## 1. Clone the Repository

You will need to prepare a local version of the project with a copied base ROM (see steps [2](../README.md#2-clone-the-repository) and [4](../README.md#4-prepare-a-base-rom) of the Linux instructions).

## 2. Create the Docker image

From inside your local project, run the following command:

```bash
docker build . -t mm
```

This will build a docker image with the name of `mm`, to verify the image was made you can run the command

```bash
docker image ls
```

and look for `mm` under the "REPOSITORY" column.

## 3. Start the container

To start the container, you can mount your local filesystem into the Docker container and run an interactive bash session.

```bash
docker run -it --rm --mount type=bind,source="$(pwd)",destination=/mm mm /bin/bash
```

- The `-it` flags Keep STDIN open even if not attached to the container and allocates a pseudo-tty terminal.
- The `--rm` flags causes Docker to automatically remove the container when it exits.
- The `--mount` flag allows you to mount volumes and host-directories in a container. By specifying the type to be a bind, we are saying there are files to be mounted from the host machine (the one that runs your docker daemon) onto the container. Source is specifying where we are mounting the files from in this case, we want the `mm` folder created earlier. The $(pwd) sub-command expands to the current working directory. The destination takes as its value the path where the file or directory is mounted in the container. This makes it so that the image should rarely change and will reduce the need to rebuild with any change to the codebase.

## 4. Setup and Build the ROM

Once inside the container, you will need to set the repository as a trusted repository with the following command:

```bash
git config --global --add safe.directory /mm
```

After that continue with step [5. Make and Build the ROM](../README.md#5-make-and-build-the-rom) of the Linux instructions to setup and build the ROM, or run any other command you need.
