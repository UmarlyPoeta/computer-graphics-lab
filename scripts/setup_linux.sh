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
    sudo dnf groupinstall -y "C Development Tools and Libraries"
    sudo dnf install -y cmake git gcc-c++ python3-pip

    echo "==> Instalacja zależności OpenGL, GLFW (dla Wayland/Hyprland)..."
    # glfw-wayland-devel zapewni paczkę kompilującą natywnie dla Wayland
    sudo dnf install -y glfw-devel glfw-wayland-devel mesa-libGL-devel mesa-libEGL-devel wayland-devel libxkbcommon-devel libglvnd-devel
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
    # Dodajemy argument --break-system-packages dla nowszych Pythonów (jak Fedora 42), jeśli to konieczne
    pip3 install glad --quiet --break-system-packages || pip3 install glad --quiet
    
    python3 -c "
import glad.main as g
import sys
sys.argv = ['glad','--api','gl:core=3.3','--out-path','$GLAD_DIR','c']
g.main()
"
    echo "==> GLAD wygenerowany w $GLAD_DIR"
else
    echo "⚠️  pip3 nie znalezione. Pobierz GLAD ręcznie z https://glad.dav1d.de/"
    echo "    Docelowa lokalizacja: $GLAD_DIR"
fi

echo ""
echo "✅ Gotowe! Możesz teraz zbudować projekt:"
echo "   mkdir build && cd build && cmake .. && make -j\$(nproc)"
