FROM ubuntu:22.04 as build
ENV TZ=UTC

# Install Required Dependencies
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    apt-get update && apt-get install -y \
    curl \
    build-essential \
    binutils-mips-linux-gnu \
    pkg-config \
    python3 \
    python3-pip \
    git \
    wget \
    unzip \
    vbindiff \
    vim \
    clang-tidy-14 \
    clang-format-14 \
    libpng-dev && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# Install practicerom
RUN curl https://practicerom.com/public/packages/debian/pgp.pub | \
    apt-key add - && echo deb http://practicerom.com/public/packages/debian staging main >/etc/apt/sources.list.d/practicerom.list && apt update

RUN apt-get install -y practicerom-dev

COPY requirements.txt requirements.txt

RUN python3 -m pip install --no-cache-dir -r requirements.txt

ENV LANG C.UTF-8

RUN mkdir /mm

WORKDIR /mm

RUN git config --global --add safe.directory /mm

ENTRYPOINT ["/bin/bash", "-c"]
