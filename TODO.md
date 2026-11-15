# Attività da completare

Priorità riferite a riduzione del rischio e verificabilità. Le attività non implicano modifiche autorizzate al firmware; richiedono una decisione separata quando comportano cambi di codice o configurazione.

## P1 — Verifiche fondamentali

- [ ] Eseguire e registrare una build PlatformIO dell'ambiente standard.
- [ ] Eseguire e registrare una build PlatformIO dell'ambiente OTA senza esporre segreti nei log condivisi.
- [ ] Collaudare in modo incrementale i servi: corrispondenza dei canali, direzione, limiti, subtrim e stabilità dell'alimentazione.
- [ ] Verificare TFT e MicroSD sul cablaggio reale, incluso il bus SPI condiviso.
- [ ] Provare access point, captive portal, connessione station, provisioning runtime e fallback AP-only.
- [ ] Provare OTA su rete controllata e documentare prerequisiti e recupero in caso di aggiornamento fallito.

## P2 — Chiarire l'interfaccia e la manutenzione

- [ ] Documentare payload, parametri, risposte e comportamento di errore degli endpoint HTTP/API.
- [ ] Definire convenzione e validazioni per nome/dimensione dei frame caricati sulla SD.
- [ ] Chiarire se `src/face-bitmaps.h` è mantenuto, legacy o destinato a un altro firmware; allineare la documentazione dopo la decisione.
- [ ] Chiarire provenienza e ruolo della copia locale `lib/ESP32Servo` rispetto alla dipendenza PlatformIO.
- [ ] Verificare quali comandi seriali sono supportati e creare un riferimento d'uso aggiornato.

## P3 — Evoluzione

- [ ] Valutare una suddivisione del firmware monolitico in moduli, definendo prima confini e criteri senza alterare il comportamento.
- [ ] Valutare test automatici o controlli statici adatti al progetto; distinguere test eseguibili su host da prove su scheda.
- [ ] Aggiungere una distinta hardware verificata (modelli, alimentazione, cablaggio) quando disponibile.

## Regole di aggiornamento

- Aggiornare questa lista quando un'attività viene iniziata, completata, ridefinita o bloccata.
- Collegare le decisioni risultanti a `TECHNICAL_DECISIONS.md` e aggiornare `PROJECT_STATUS.md` quando cambia lo stato verificato.
- Non segnare come completato un collaudo solo perché la funzione è presente nel sorgente.
