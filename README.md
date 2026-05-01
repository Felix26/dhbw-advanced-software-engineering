# dhbw-advanced-software-engineering

Ein Statistik-Tool für den Check-In-Service Träwelling.

## Voraussetzungen

- CMake 3.17 oder neuer
- Ein C++20-kompatibler Compiler (z.B. GCC, Clang, MSVC)
- Optional: `ninja` als Buildsystem

## Build-Prozess

Bevorzugt wird das mitgelieferte Skript verwendet, das zuerst die Unit-Tests baut und ausführt und danach die Anwendung erstellt.

Windows:

```powershell
.\compile.bat
```

Linux:

```bash
./compile.sh
```

Die Projekterstellung kann alternativ auch direkt mit CMake erfolgen. Beispiel für eine Build-Umgebung im Terminal:

```powershell
mkdir -p build
cd build
cmake -G Ninja ..
cmake --build .
```

Wenn `ninja` nicht installiert ist, kann alternativ ein anderer Generator verwendet werden:

```powershell
cmake ..
cmake --build .
```

### Optionen

- `BUILD_APP=ON` baut die Hauptanwendung
- `BUILD_TESTS=ON` baut die Unit-Tests

## Ausführen

Wenn die Anwendung mit dem Compile-Skript gebaut wird, liegt sie danach im Hauptverzeichnis und kann direkt gestartet werden. Ansonsten muss in das build-Verzeichnis navigiert werden.

```powershell
./dhbw-advanced-software-engineering(.exe)
```

Beim Start muss als Parameter ein Ordner mit Haltestellendaten sowie den auszuwertenden Daten liegen. Die Haltestellendaten sowie ein Beispiel von auszuwertenden Daten liegen in data/ ab, der zum Start genutzt werden kann.

```powershell
./dhbw-advanced-software-engineering(.exe) data
```

## Tests

Die Tests werden über CTest ausgeführt. Beispiel:

```powershell
cd build
ctest --output-on-failure
```

Alternativ kann ein einzelner Test direkt gestartet werden:

```powershell
cd build
.\stationRepository_test.exe
```

Für die Testabdeckung kann `gcovr` verwendet werden, muss ggf. installiert werden:

```powershell
gcovr -r . --filter src/ --filter include/
```

## Projektstruktur

- `src/` - Implementierung der Logik und der Anwendungsdatei
- `include/` - Header-Dateien und Schnittstellen
- `tests/` - Unit-Tests
- `data/` - Beispieldaten und Hilfsdateien
- `external/json/` - eingebettete JSON-Bibliothek nlohmann::json
- `build/`, `build_application/`, `build_tests/` - erzeugte Builds

## Lizenzen

- nlohmann::json (external/json/json.hpp)  
  MIT License  
  https://github.com/nlohmann/json/blob/develop/LICENSE.MIT

- ZHV-Daten (data/zHV.csv)  
  © DELFI e.V. – Nutzung gemäß ZHV-Nutzungsbedingungen  
  Technischer Betreiber: WVI  
  Quelle: Zentrales Haltestellenverzeichnis (ZHV)

- OpenStreetMap (data/germanyBoundary.h)  
  © OpenStreetMap contributors  
  ODbL 1.0  
  https://www.openstreetmap.org/copyright  
  Daten wurden verarbeitet und vereinfacht

