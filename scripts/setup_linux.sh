#!/usr/bin/env bash
# setup_linux.sh — instaluje zależności OpenGL/GLFW/GLAD na Ubuntu/Debian

set -e

echo "==> Aktualizacja listy pakietów..."
sudo apt-get update -qq

echo "==> Instalacja narzędzi budowania..."
sudo apt-get install -y build-essential cmake git

echo "==> Instalacja OpenGL i GLFW..."
sudo apt-get install -y libgl1-mesa-dev libglfw3-dev libglfw3

echo "==> Pobieranie GLAD (OpenGL 3.3 Core) z GitHub..."
GLAD_DIR="$(dirname "$0")/../deps/GLAD"
mkdir -p "$GLAD_DIR"

# Używamy gotowego snapshotu GLAD z repozytorium Dav1d
if command -v pip3 &>/dev/null; then
    pip3 install glad --quiet
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
