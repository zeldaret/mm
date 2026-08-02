FROM ubuntu:24.04 AS build

ENV TZ=UTC
ENV LANG=C.UTF-8

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install Required Dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    binutils-mips-linux-gnu \
    gcc-mips-linux-gnu \
    pkg-config \
    python3 \
    python3-pip \
    python3-venv \
    git \
    wget \
    unzip \
    vbindiff \
    vim \
    clang-tidy-14 \
    clang-format-14 \
    libpng-dev \
    curl

# Add source for practicerom-dev install

RUN curl -O https://practicerom.com/public/packages/debian/dists/stable/practicerom-repository_latest_$(dpkg --print-architecture).deb && \
dpkg -i practicerom-repository_latest_$(dpkg --print-architecture).deb && \
apt update

# Post dependencies cleanup
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /mm
RUN git config --global --add safe.directory /mm

ENTRYPOINT ["/usr/bin/env", "bash", "-c"]
