# Contesto del progetto Trace-E

> **Documento di riferimento.** Questo file, insieme a `PROJECT_STATUS.md`, `TECHNICAL_DECISIONS.md` e `TODO.md`, costituisce la fonte di verità documentale del progetto. In caso di modifica significativa a firmware, hardware, configurazione o decisioni, aggiornare i documenti interessati nello stesso lavoro. Separare sempre i fatti verificati dalle ipotesi e segnare le informazioni mancanti come **Da verificare**. Non inserire credenziali, password o segreti.

## Scopo e stato delle informazioni

Il repository contiene il firmware di Trace-E, un robot con otto servi, display TFT e controllo tramite rete locale. Questo documento descrive quanto risulta dal codice e dalla configurazione presenti nel repository; non certifica prove effettuate sul robot fisico. Le caratteristiche non deducibili dai file sono indicate come **Da verificare**.

## Hardware

- **Scheda indicata dalla configurazione:** AZ-Delivery DevKit V4.
- **Microcontrollore indicato dal firmware:** ESP32-WROOM-32.
- **Servi:** otto canali PWM, configurati a 50 Hz; impulsi configurati nell'intervallo 732–2929 µs e angoli limitati a 0–180°.
- **Display:** TFT ST7735, risoluzione logica 160×128 in orientamento landscape.
- **Scheda SD:** MicroSD su SPI, con CS separato dal display.
- **Alimentazione, modello dei servi, modello esatto del display/SD e cablaggio verificato:** **Da verificare** sul dispositivo.

### Mappatura pin riportata nel firmware

| Funzione | GPIO |
|---|---:|
| Servi R1, R2, L1, L2 | 13, 12, 14, 27 |
| Servi R4, R3, L3, L4 | 26, 25, 33, 32 |
| TFT CS / RST / DC | 17 / 16 / 4 |
| SPI SCK / MOSI / MISO | 18 / 23 / 19 |
| SD CS | 5 |

SCK e MOSI sono condivisi tra display e SD. Il firmware inizializza il bus SPI con MISO sul GPIO 19 e gestisce separatamente le linee CS.

## Architettura software

- **Build system:** PlatformIO.
- **Piattaforma:** `espressif32`.
- **Board ID:** `az-delivery-devkit-v4`.
- **Framework:** Arduino.
- **Monitor seriale:** 115200 baud.
- **Ambienti:** `az-delivery-devkit-v4` per il caricamento standard e `az-delivery-devkit-v4-ota` per OTA via `espota`.

Il programma principale è `src/Trace-E-firmware-main.ino`. È un firmware monolitico che coordina inizializzazione hardware, rete, server, comandi, servi, animazioni e SD. `loop()` serve DNS e HTTP, gestisce OTA e aggiornamento Wi-Fi, aggiorna le animazioni e avvia la sequenza associata al comando corrente. Alcune sequenze di movimento contengono attese; `delayWithFace()` continua a servire rete, OTA e animazione durante le attese.

### Componenti funzionali

- **Movimento:** `src/movement-sequences.h` definisce nomi dei servi e sequenze per pose, locomozione e gesti. Il firmware instrada comandi quali avanti/indietro, svolta, riposo, postura e pose espressive.
- **Volto TFT:** `src/face-bitmaps-tft.h` contiene bitmap monocromatiche incorporate e l'elenco `FACE_LIST`. Il firmware anima i frame e sceglie il colore in base al nome dell'espressione.
- **Volti su SD:** i frame sono cercati sotto `/faces` come `<nome>_<indice>.bin` (con fallback `<nome>.bin`). Un frame è di 2560 byte, coerente con 160×128 pixel a 1 bit. L'interfaccia espone elenco, caricamento e cancellazione.
- **Interfaccia web:** `src/captive-portal.h` incorpora HTML/CSS/JavaScript serviti dal firmware. Il server HTTP usa la porta 80; il DNS wildcard supporta il captive portal.
- **Wi-Fi:** il firmware avvia un access point e può anche connettersi a una rete esterna. Sono presenti scansione e provisioning runtime; il codice imposta `WiFi.persistent(false)` e indica che le credenziali fornite dal provisioning runtime sono session-only.
- **mDNS e OTA:** il nome host del dispositivo è annunciato via mDNS quando disponibile. ArduinoOTA viene avviato quando il collegamento alla rete esterna è attivo.
- **Debug seriale:** è presente un parser di comandi seriali per diagnostica e controllo.

## API HTTP individuate

Le route registrate nel firmware includono:

| Endpoint | Uso indicato dal codice |
|---|---|
| `/` | Interfaccia web |
| `/cmd` | Comandi dalla pagina web |
| `/getSettings`, `/setSettings` | Lettura e aggiornamento impostazioni |
| `/api/status`, `/api/command` | Stato e controllo via API |
| `/api/wifi/scan`, `/api/wifi/connect`, `/api/wifi/status` | Scansione, provisioning e stato Wi-Fi |
| `/api/sd/list` | Elenco dei file SD |
| `/api/sd/upload` | Caricamento di file sulla SD |
| `/api/sd/delete` | Cancellazione di file dalla SD |

Schema completo dei parametri, payload, codici di risposta e limiti di sicurezza: **Da verificare** prima di trattare l'API come stabile.

## Librerie e strumenti

Dipendenze dichiarate in `platformio.ini`:

- `madhephaestus/ESP32Servo` per i servi;
- `adafruit/Adafruit GFX Library` per le primitive grafiche;
- `adafruit/Adafruit ST7735 and ST7789 Library` per il display.

Sono inoltre usate API Arduino/ESP32 per Wi-Fi, OTA, HTTP, DNS, mDNS, SPI e SD. `lib/ESP32Servo` contiene una copia locale della libreria; la provenienza e l'eventuale rapporto con la dipendenza gestita da PlatformIO sono **Da verificare**.

Gli script in `scripts/` esportano bitmap verso file binari, convertono immagini in formato monocromatico e preparano l'autenticazione per l'upload OTA. Non documentare né copiare in questi file o nei documenti valori segreti.

## Struttura del repository

| Percorso | Ruolo osservato |
|---|---|
| `platformio.ini` | Piattaforma, board, framework, dipendenze e ambienti |
| `src/Trace-E-firmware-main.ino` | Applicazione firmware e coordinamento dei componenti |
| `src/movement-sequences.h` | Mappatura logica servi e pose |
| `src/face-bitmaps-tft.h` | Bitmap TFT incorporate e lista dei volti attiva |
| `src/face-bitmaps.h` | Ulteriore header bitmap; il firmware principale include la variante TFT. Relazione/manutenzione: **Da verificare** |
| `src/captive-portal.h` | Contenuto dell'interfaccia web incorporata |
| `src/secret.h` | Configurazione riservata; non leggere o riportare i valori |
| `lib/ESP32Servo` | Libreria locale ESP32Servo |
| `scripts/` | Utility Python e script PlatformIO per OTA |
| `sdcard_faces/` | Destinazione prevista per i frame delle facce esportati |
| `include/`, `test/` | Presentano README segnaposto; test di progetto non individuati |
| `.pio/`, `.vscode/` | Directory di ambiente/build e configurazione IDE |

## Protocollo di manutenzione della documentazione

Questi quattro documenti sono il riferimento condiviso per ChatGPT e Codex. Quando una sessione introduce una modifica significativa o concorda una decisione:

1. aggiornare `PROJECT_CONTEXT.md` se cambia architettura, configurazione o struttura;
2. aggiornare `PROJECT_STATUS.md` e `TODO.md` se cambia lo stato o il piano;
3. aggiungere una voce a `TECHNICAL_DECISIONS.md` per le decisioni concordate, con data, motivazione e alternative solo se effettivamente discusse;
4. non trasformare deduzioni in decisioni approvate e non colmare lacune con supposizioni;
5. non inserire credenziali o segreti.

