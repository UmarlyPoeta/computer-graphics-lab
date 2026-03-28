#!/usr/bin/env bash
# setup_linux.sh — instaluje zależności OpenGL/GLFW/GLAD (wspiera Fedorę 42 z Wayland/Hyprland oraz Ubuntu/Debian)

set -e

# Funkcja wykrywająca dystrybucję
OS_ID=$(cat /etc/os-release | grep -E '^ID=' | cut -d '=' -f 2 | tr -d '"')

if [ "$OS_ID" == "fedora" ]; then
    echo "==> Wykryto system Fedora ($OS_ID)."
    echo "==> Aktualizacja pakietów DNF..."
    sudo dnf upgrade -y --refresh

    echo "==> Instalacja narzędzi budowania (CMake, GCC, Git)..."
    sudo dnf group install -y "C Development Tools and Libraries" || sudo dnf install -y @development-tools
    sudo dnf install -y cmake git gcc-c++ python3-pip

    echo "==> Instalacja zależności OpenGL, GLFW (dla Wayland/Hyprland)..."
    # glfw-devel zazwyczaj zawiera już obsługę Wayland w nowych wersjach Fedory, więc usuwamy wymóg osobnego glfw-wayland-devel
    sudo dnf install -y glfw-devel mesa-libGL-devel mesa-libEGL-devel wayland-devel libxkbcommon-devel libglvnd-devel
elif [ "$OS_ID" == "ubuntu" ] || [ "$OS_ID" == "debian" ]; then
    echo "==> Wykryto system Debian/Ubuntu."
    echo "==> Aktualizacja listy pakietów..."
    sudo apt-get update -qq

    echo "==> Instalacja narzędzi budowania..."
    sudo apt-get install -y build-essential cmake git python3-pip

    echo "==> Instalacja zależności OpenGL, GLFW i Wayland..."
    sudo apt-get install -y libgl1-mesa-dev libglfw3-dev libglfw3 libwayland-dev libxkbcommon-dev
else
    echo "⚠️  Nie rozpoznano wspieranego systemu (wykryto: $OS_ID). Spróbuj zainstalować zależności manualnie."
fi

echo "==> Pobieranie GLAD (OpenGL 3.3 Core)..."
GLAD_DIR="$(dirname "$0")/../deps/GLAD"
mkdir -p "$GLAD_DIR"

if command -v pip3 &>/dev/null; then
    pip3 install glad2 --quiet --break-system-packages --user || pip3 install glad2 --quiet --user

    # glad2 tworzy komendę 'glad'
    if command -v ~/.local/bin/glad &>/dev/null; then
        ~/.local/bin/glad --api gl:core=3.3 --out-path "$GLAD_DIR" c
    elif command -v glad &>/dev/null; then
        glad --api gl:core=3.3 --out-path "$GLAD_DIR" c
    else
        python3 -m glad --api gl:core=3.3 --out-path "$GLAD_DIR" c
    fi
    echo "==> GLAD wygenerowany w $GLAD_DIR"
else
    echo "⚠️  pip3 nie znalezione. Pobierz GLAD ręcznie z https://glad.dav1d.de/"
    echo "    Docelowa lokalizacja: $GLAD_DIR"
fi

echo ""
echo "✅ Gotowe! Możesz teraz zbudować projekt:"
echo "   mkdir build && cd build && cmake .. && make -j\$(nproc)"
