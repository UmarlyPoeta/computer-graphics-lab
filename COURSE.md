# Kurs OpenGL: Od zera do grafiki na ekranie (plus bonus SDDM)

Witaj! Ten kurs ma jedno zadanie: nauczyć Cię podstaw nowoczesnego OpenGL (wersja Core Profile, 3.3+), tak abyś rozumiał, co robi każda linijka kodu w Twoim projekcie.

Uczymy się poprzez praktykę. Każde z laboratoriów (Lab 1, Lab 2, Lab 3) w Twoim repozytorium uczy innych zagadnień. Będziemy przez nie przechodzić po kolei.

---

## Moduł 1: Środowisko i Okno (Lab 1)

W nowoczesnym OpenGL, samo API nie potrafi stworzyć okna ani odebrać wciśnięcia klawisza. Do tego potrzebujemy zewnętrznej biblioteki. W tym projekcie używamy **GLFW**. 
Kolejnym problemem jest to, że funkcje OpenGL są specyficzne dla sterowników karty graficznej. Aby ich używać w C++, musimy załadować je w czasie działania programu. Do tego służy **GLAD**.

### 🛠️ Zadanie 1 (Lab 1 / exercise)
Otwórz plik `lab1/exercise/main_exercise.cpp`.

Aby użyć GLFW, musisz je najpierw zainicjalizować. Kod zazwyczaj wygląda tak:
```cpp
if (!glfwInit()) {
    std::cout << "Nie udalo sie zainicjalizowac GLFW!" << std::endl;
    return -1;
}
```
Na koniec programu (przed `return 0`), musisz posprzątać po GLFW:
```cpp
glfwTerminate();
```

**Twoje zadanie:**
Użyj funkcji `glfwGetVersionString()`, aby wydrukować wersję GLFW na ekran.
Spróbuj skompilować ten plik i sprawdzić, czy działa. 

---

## Moduł 2: Trójkąt i Podstawy Potoku Renderowania (Lab 2)

Zanim coś narysujemy, musimy zrozumieć **Potok Renderowania (Rendering Pipeline)**. 
Twoja karta graficzna (GPU) jest maszyną, która bierze współrzędne w przestrzeni 3D i przetwarza je na piksele na płaskim ekranie 2D. 

Programista w nowoczesnym OpenGL musi napisać małe programy (tzw. **Shadery**), które uruchamiają się na GPU w różnych etapach tego potoku.
Dwa najważniejsze shadery to:
1. **Vertex Shader** (Shader Wierzchołków) - dla każdego punktu 3D, który mu podasz, przetwarza jego pozycję.
2. **Fragment Shader** (Shader Fragmentów/Pikseli) - decyduje, jaki kolor ma mieć dany piksel na ekranie (np. na czerwono).

### Magazyn danych: VBO i VAO

Aby narysować coś na karcie, nie możemy wysyłać punktów z procesora (CPU) do GPU punkt po punkcie, co klatkę. To byłoby zbyt wolne. Zamiast tego pakujemy dane w paczki i wysyłamy do pamięci GPU raz.

- **VBO (Vertex Buffer Object)** - To po prostu bufor (tablica) w pamięci karty graficznej. Służy do trzymania Twoich wierzchołków (np. `float vertices[] = { ... };`).
- **VAO (Vertex Array Object)** - To obiekt "pamiętający", jak OpenGL ma interpretować dane z VBO. Mówi GPU: "Z tego VBO weź pierwsze 3 floaty i potraktuj je jako koordynaty X, Y, Z". 

### 🛠️ Zadanie 2 (Lab 2)
W Lab 2 będziemy tworzyć pierwsze VAO/VBO i shadery. Spójrz na plik `lab2/exercise/main_exercise.cpp` i spróbuj zaimplementować inicjalizację okna (już wiesz jak) + ładowanie GLAD. 

Kroki po zainicjalizowaniu GLFW do stworzenia okna:
```cpp
// Ustawiamy, że chcemy OpenGL 3.3 Core Profile
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Tworzymy okno (Szerokość, Wysokość, Tytuł, Monitor (fullscreen), Współdzielenie)
GLFWwindow* window = glfwCreateWindow(800, 600, "Moj Pierwszy Trojkat", NULL, NULL);
if (window == NULL) {
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // Ważne! Bez tego nie podepniemy kontekstu OpenGL
```
Po `glfwMakeContextCurrent` musisz załadować wskaźniki OpenGL używając GLAD:
```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1; // Błąd ładowania GLAD
}
```

---

## Dodatek: Naprawa SDDM na laptopie

SDDM (Simple Desktop Display Manager) to ekran logowania (tzw. display manager) używany często w środowiskach KDE Plasma. Jeśli zawiesza się lub wyświetla czarny ekran, oto kompleksowy przewodnik jak to naprawić.

### Krok 1: Przejdź do konsoli TTY
Jeśli ekran jest czarny, wciśnij kombinację `Ctrl + Alt + F2` (lub F3, F4...). To powinno wywołać czarną konsolę tekstową. Zaloguj się tam swoim użytkownikiem i hasłem.

### Krok 2: Sprawdź logi (Dlaczego nie działa?)
Wpisz:
```bash
journalctl -u sddm -n 50 --no-pager
```
lub
```bash
cat /var/log/Xorg.0.log | grep EE
```
To powie Ci, czy problem dotyczy sterowników graficznych (częsty przypadek np. dla kart NVIDIA).

### Krok 3: Typowe naprawy

**A. Rekonfiguracja lub reset pliku konfiguracyjnego SDDM**
Wygeneruj czysty plik konfiguracyjny (wymaga root / sudo):
```bash
sudo sddm --example-config | sudo tee /etc/sddm.conf
```
Zrestartuj usługę: `sudo systemctl restart sddm`

**B. Problemy z uprawnieniami (bardzo częste)**
Czasami SDDM gubi uprawnienia do katalogu domowego X11. Spróbuj zmienić właściciela dla logów X:
```bash
sudo chown -R sddm:sddm /var/lib/sddm
```

**C. Przełączenie na z X11 na Wayland (lub odwrotnie)**
SDDM czasami gryzie się z domyślną sesją. Możesz zmusić go do działania z X11. 
Otwórz plik (np. `sudo nano /etc/sddm.conf` lub folder `/etc/sddm.conf.d/`) i znajdź sekcję `[Wayland]`. Jeśli jest problem, spróbuj upewnić się, że sekcja `[X11]` działa poprawnie.

**D. Całkowity reset i awaryjny Display Manager (LightDM)**
Jeśli SDDM jest kompletnie zepsuty, awaryjnie zainstaluj `lightdm` (jeśli potrzebujesz graficznego logowania "na teraz"):
```bash
sudo apt install lightdm    # (Dla Ubuntu/Debian)
# W trakcie instalacji wybierz lightdm. 
# Aby zrestartować logowanie:
sudo systemctl restart lightdm
```

---
*Czytasz ten plik w terminalu/edytorze tekstu. Podążaj za modułami i daj znać w czacie, gdy zrobisz zadanie!*
