FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y sudo debianutils gcc=4:9.3.0-1ubuntu2 clang make=4.2.1-1.2 gdb=9.2-0ubuntu1~20.04.2 valgrind=1:3.15.0-1ubuntu9.1 python3 python3-pip python3-dev=3.8.2-0ubuntu2 python3-venv build-essential curl vim nano git zsh git-core openssh-client lsb-release ca-certificates tree bsdmainutils libx11-dev libxext-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN pip3 install attrs==19.3.0 autobahn==17.10.1 automat==0.8.0 blinker==1.4 bottle==0.12.24 c-formatter-42==0.2.7 Cython==0.29.14 norminette==3.3.51 requests==2.22.0 setuptools==45.2.0 wheel==0.34.2 gitpython && \
    rm -rf /root/.cache/pip

RUN sudo echo "root ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN sudo zsh -c "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)"

RUN rm -rf /root/.oh-my-zsh
RUN zsh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh) --unattended"

COPY .zshrc /root/.zshrc

RUN git clone https://github.com/spaceship-prompt/spaceship-prompt.git \
    /root/.oh-my-zsh/custom/themes/spaceship-prompt --depth=1 && \
    ln -s /root/.oh-my-zsh/custom/themes/spaceship-prompt/spaceship.zsh-theme \
    /root/.oh-my-zsh/custom/themes/spaceship.zsh-theme

RUN sudo zsh -c "$(curl --fail --show-error --silent --location https://raw.githubusercontent.com/zdharma-continuum/zinit/HEAD/scripts/install.sh)"

RUN curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg && \
    sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null && \
    sudo apt-get update && \
    sudo apt-get install gh -y

RUN mkdir -p /libftTester && \
    sudo git clone https://github.com/Tripouille/libftTester.git /libftTester

RUN sed -i '4s|.*|LIBFT_PATH = $(PARENT_DIR)/workspace|' /libftTester/Makefile

RUN mkdir -p /workspace /libftTester \
    && chmod -R 777 /workspace /libftTester \
    && chown -R root:root /workspace /libftTester

WORKDIR /workspace

LABEL maintainer="marcio.daniel@msn.com"
LABEL version="1.1"
