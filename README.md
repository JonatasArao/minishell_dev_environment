
# 💻 Docker Environment for C Development

This project leverages Docker to create an isolated environment for C development, with all necessary tools to efficiently compile and test code. Follow the instructions below to set up and manage the Docker environment.

## 🛠️ **Quick Start Guide**

### 🚀 Build and Start the Container
Build and run the container with relevant files and configurations.
```bash
docker run -it --name $(basename "$(pwd)") \
  -v "$(find ~ -maxdepth 1 -type d -name ".ssh"):/root/.ssh" \
  -v "$(find ~ -maxdepth 1 -type f -name ".gitconfig"):/root/.gitconfig" \
  -v "$(pwd)":/workspace \
  -w /workspace \
  marciodanielll/ubuntu-42:1.1 zsh
```

For more Docker commands, visit the [Docker Commands Documentation](https://marciodanielll.github.io/docker_commands/).

### 🧑‍💻 Using GitHub Codespaces

You can also use GitHub Codespaces to develop in a fully configured cloud environment. Follow these steps:

1. Open your repository on GitHub.
2. Click the **Code** button.
3. Select **Open with Codespaces**.
4. If you don't have a codespace already, click **New codespace**.

Your codespace will automatically use the configuration defined in the `.devcontainer/devcontainer.json` file.

For more information, visit the [GitHub Codespaces Documentation](https://docs.github.com/en/codespaces/overview).
