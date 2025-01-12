FROM ubuntu:24.04 AS build

ENV TZ=UTC
ENV LANG=C.UTF-8

# Install Required Dependencies
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    apt-get update && apt-get install -y \
    curl \
    build-essential \
    binutils-mips-linux-gnu \
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
    libpng-dev && \
    # Add source for practicerom-dev install
    curl https://practicerom.com/public/packages/debian/pgp.pub | apt-key add - && \ 
    echo deb http://practicerom.com/public/packages/debian staging main >/etc/apt/sources.list.d/practicerom.list && \
    apt-get update && \
    apt-get install -y \
    practicerom-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /mm
RUN git config --global --add safe.directory /mm

ENTRYPOINT ["/bin/bash", "-c"]
