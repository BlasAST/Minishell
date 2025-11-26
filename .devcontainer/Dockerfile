FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
	sudo \
	iputils-ping \
    fish \
    gcc \
    g++ \
    make \
    libc-dev \
    git \
    curl \
    clang \
    python3 \
    python3-pip \
    python3-venv \
    python3-tk \
    lsb-release \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir norminette
RUN bash -c "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)"
RUN git clone https://github.com/vfurmane/pipex-tester
# WORKDIR /app
CMD [ "fish" ]
