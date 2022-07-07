FROM ubuntu:21.10 as build
ENV TZ=UTC

LABEL Cammoguy <jpburnett@gwu.edu>

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    apt-get update && apt-get install -y \
    make \
    build-essential \
    binutils-mips-linux-gnu \
    pkg-config \
    python3 \
    python3-pip \
    git \
    wget \
    unzip \
    clang-tidy \
    clang-format \
    libpng-dev && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

COPY requirements.txt requirements.txt

RUN python3 -m pip install --no-cache-dir -r requirements.txt

ENV LANG C.UTF-8

RUN mkdir /mm

WORKDIR /mm

ENTRYPOINT ["/bin/bash", "-c"]
# CMD ["/bin/sh", "-c", \
    # "echo 'usage:\n  docker run --rm --mount type=bind,source=\"$(pwd)\",destination=/mm mm make init -j$(nproc)'"]