# Stato del progetto Trace-E

> Stato ricavato da un'ispezione statica del repository; non equivale a collaudo su hardware. Ultimo aggiornamento: 2026-11-15.

## Sintesi

Il repository contiene un firmware PlatformIO/Arduino per ESP32-WROOM-32 su AZ-Delivery DevKit V4. Sono implementati controllo di otto servi, animazioni su TFT, access point con captive portal, server web/API, provisioning Wi-Fi, OTA su rete esterna e gestione dei frame su MicroSD. La presenza di codice non dimostra che ogni funzione sia stata provata o funzioni correttamente sul dispositivo.

## Funzionalità riscontrate nel codice

- Configurazione di otto servi e sequenze per locomozione e pose.
- Schermo ST7735 con bitmap incorporate, animazioni e stato inattivo con battito di palpebre.
- Access point, DNS wildcard e pagina web di controllo.
- Modalità station Wi-Fi opzionale, scansione e provisioning runtime.
- Endpoint HTTP per comandi, stato/impostazioni e gestione Wi-Fi.
- Supporto MicroSD per leggere, caricare, elencare e cancellare file delle facce.
- mDNS e ArduinoOTA quando è attiva la connessione a una rete esterna.
- Comandi seriali per diagnostica/controllo.
- Utility locali per convertire/esportare immagini e gestire i parametri di upload OTA.

## Problemi aperti e verifiche mancanti

1. **Build e upload:** esito di una build attuale per entrambi gli ambienti PlatformIO e caricamento su scheda non verificati in questa analisi.
2. **Collaudo hardware:** cablaggio, alimentazione, versi/offset dei servi, temporizzazione del movimento e stabilità durante trasmissioni Wi-Fi da verificare sul robot.
3. **Periferiche SPI:** funzionamento simultaneo o alternato di TFT e SD e compatibilità con le schede/display effettivi da verificare.
4. **Rete e OTA:** fallback AP, captive portal, provisioning, mDNS e aggiornamento OTA da provare sul dispositivo e sulla rete prevista.
5. **API e interfaccia:** schema completo, compatibilità con eventuali client e comportamento in caso di input non validi da documentare/testare.
6. **Bitmap:** `face-bitmaps.h` e `face-bitmaps-tft.h` presentano elenchi diversi; il firmware include la variante TFT. Chiarire se il primo header è obsoleto o mantenuto per un altro target.
7. **Dipendenza ESP32Servo:** verificare se `lib/ESP32Servo` è copia intenzionale, fork o ridondanza rispetto alla dipendenza dichiarata in PlatformIO.
8. **Test automatici:** nella cartella `test/` è presente il README standard; non sono stati individuati test di progetto.
9. **Configurazione riservata:** mantenere i segreti fuori dai documenti e verificare separatamente il processo locale di fornitura delle credenziali senza inserirle in chiaro nei report.

## Prossimi passi

Vedere `TODO.md` per le attività prioritarie. Le prime azioni consigliate sono una build riproducibile degli ambienti e un collaudo incrementale di servi, display, SD e rete.

