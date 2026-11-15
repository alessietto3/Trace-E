# Registro decisioni tecniche

Questo registro distingue le **decisioni documentate** dalle **scelte dedotte dal codice**. Una scelta dedotta descrive lo stato osservato, ma non implica che sia stata discussa o approvata. Le alternative sono riportate solo quando risultano da commenti o decisioni esplicite; altrimenti sono indicate come non documentate.

## Decisioni e scelte osservate

| ID | Data | Stato | Decisione o scelta | Motivazione documentata | Alternative / note |
|---|---|---|---|---|---|
| TD-001 | Non documentata | Dedotta dalla configurazione | Usare PlatformIO con piattaforma `espressif32`, board `az-delivery-devkit-v4` e framework Arduino. | Configurazione presente in `platformio.ini`. | Motivazione storica e alternative considerate: non documentate. |
| TD-002 | Non documentata | Dedotta dal firmware | Usare otto servi con GPIO dedicati sul setup ESP32-WROOM-32. | Pinout e inizializzazione espliciti nel firmware. | Validazione elettrica e alternative di driver PWM: da verificare/non documentate. |
| TD-003 | Non documentata | Dedotta dal firmware | Condividere SPI SCK/MOSI tra TFT e MicroSD, mantenendo CS distinti. | Commento e inizializzazione SPI nel firmware. | Motivazione progettuale e alternative considerate: non documentate. |
| TD-004 | Non documentata | Dedotta dal firmware | Integrare le bitmap dei volti nel firmware e supportare frame aggiuntivi dalla SD. | Include della variante TFT e caricamento dei file da `/faces`. | Motivazione per il fallback incorporato: non documentata. |
| TD-005 | Non documentata | Dedotta dalla configurazione | Mantenere un ambiente PlatformIO per upload standard e uno per OTA. | Secondo environment esteso dal primo e configurato con protocollo OTA. | Criteri di scelta e alternative: non documentati. |
| TD-006 | Non documentata | Dedotta dal firmware | Avviare un access point e consentire anche la connessione station; il provisioning runtime è impostato come session-only tramite `WiFi.persistent(false)`. | Commenti nel firmware sulla non persistenza delle credenziali Wi-Fi runtime; codice di fallback e provisioning. | Politica di sicurezza complessiva e alternative: da verificare. Non registrare valori di credenziali. |

## Decisioni future

Aggiungere una voce quando una decisione viene effettivamente concordata. Modello:

| ID | Data | Stato | Decisione | Motivazione | Alternative considerate e motivo dello scarto |
|---|---|---|---|---|---|
| TD-XXX | AAAA-MM-GG | Approvata / proposta / superata | … | … | … |

