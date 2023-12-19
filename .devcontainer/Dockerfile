FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN export DEBIAN_FRONTEND=noninteractive \
  && apt update \
  && apt install --no-install-recommends --yes \
    apt-utils \
    build-essential \
    ca-certificates \
    curl \
    dialog \
    git \
    sudo \
    udev \
    unzip \
    usbutils \
    wget \
    # for platformio
    bc \
    build-essential \
    clang \
    curl \
    gcc \
    python3 \
    python3-dev \
    python3-distutils \
    python3-pip \
    python3-setuptools \
    python3-venv \
    srecord \
    xz-utils \
  && apt autoremove --yes \
  && apt clean --yes \
  && rm -rf /var/lib/apt/lists/*

RUN curl -sfL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules -o /etc/udev/rules.d/99-platformio-udev.rules

RUN usermod -a -G dialout "$USERNAME" \
  && usermod -a -G plugdev "$USERNAME"

USER "$USERNAME"
WORKDIR "/home/${USERNAME}"

RUN curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py -o /tmp/get-platformio.py \
  && python3 /tmp/get-platformio.py \
  && mkdir -p "${HOME}/.local/bin" \
  && echo "export PATH=${PATH}:${HOME}/.local/bin/" >> "${HOME}/.bash_profile" \
  && ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio \
  && ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio \
  && ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
