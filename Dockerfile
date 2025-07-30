# Base image
FROM ubuntu:22.04

ENV TZ=UTC
ENV LANG=C.UTF-8

# Set timezone
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install build dependencies
RUN apt-get update && apt-get install -y \
    make \
    git \
    build-essential \
    binutils-mips-linux-gnu \
    curl \
    python3 \
    python3-pip \
    python3-venv \
    libpng-dev \
    libxml2-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory to project
WORKDIR /

# Optional: mark directory safe for git is that needed
RUN git config --global --add safe.directory /mm
# future after wget rom
RUN git clone https://github.com/zeldaret/mm.git

# remove dependancies
# add volume for rom endpoint
WORKDIR /mm/baseroms/n64-us
COPY ./baseroms/n64-us .

WORKDIR /mm/build/n64-us
COPY ./build/n64-us/mm-n64-us.z64 .

WORKDIR /mm
RUN pip install -r requirements.txt
RUN make init

# Default entry (you may override in mcp config)
ENTRYPOINT ["/usr/bin/env", "bash"]
