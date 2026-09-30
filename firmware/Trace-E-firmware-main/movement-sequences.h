#pragma once

#include <Arduino.h>

enum ServoName : uint8_t {
  R1 = 0, 
  R2 = 1,
  L1 = 2,
  L2 = 3,
  R4 = 4,
  R3 = 5,
  L3 = 6,
  L4 = 7
};

const String ServoNames[]={"R1","R2","L1","L2","R4","R3","L3","L4"};

inline int servoNameToIndex(const String& servo) {
  if (servo == "L1") return L1;
  if (servo == "L2") return L2;
  if (servo == "L3") return L3;
  if (servo == "L4") return L4;
  if (servo == "R1") return R1;
  if (servo == "R2") return R2;
  if (servo == "R3") return R3;
  if (servo == "R4") return R4;
  return -1;
}

enum FaceAnimMode : uint8_t {
  FACE_ANIM_LOOP = 0,
  FACE_ANIM_ONCE = 1,
  FACE_ANIM_BOOMERANG = 2
};

// External globals and helpers used by movement/pose sequences
extern int frameDelay;
extern int walkCycles;
extern String currentCommand;

extern void setServoAngle(uint8_t channel, int angle);
extern void setFace(const String& faceName);
extern void setFaceMode(FaceAnimMode mode);
extern void setFaceWithMode(const String& faceName, FaceAnimMode mode);
extern void delayWithFace(unsigned long ms);
extern void enterIdle();
extern bool pressingCheck(String cmd, int ms);

// Pose/animation prototypes
void runRestPose();
void runStandPose(int face = 1);
void runWavePose();
void runDancePose();
void runSwimPose();
void runPointPose();
void runPushupPose();
void runBowPose();
void runCutePose();
void runFreakyPose();
void runWormPose();
void runShakePose();
void runShrugPose();
void runDeadPose();
void runCrabPose();
void runWalkPose();
void runWalkBackward();
void runTurnLeft();
void runTurnRight();

// ====== POSES ======
inline void runRestPose() { 
  Serial.println(F("REST")); 
  setFaceWithMode("rest", FACE_ANIM_BOOMERANG); 
  for (int i = 0; i < 8; i++) setServoAngle(i, 90); 
}

inline void runStandPose(int face) { 
  Serial.println(F("STAND")); 
  if (face == 1) setFaceWithMode("stand", FACE_ANIM_ONCE); 
  setServoAngle(R1, 135); 
  setServoAngle(R2, 45); 
  setServoAngle(L1, 45); 
  setServoAngle(L2, 135); 
  setServoAngle(R4, 0); 
  setServoAngle(R3, 180); 
  setServoAngle(L3, 0); 
  setServoAngle(L4, 180); 
  if (face == 1) enterIdle();
}

inline void runWavePose() { 
  Serial.println(F("WAVE")); 
  setFaceWithMode("wave", FACE_ANIM_ONCE); 
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(R4, 80); setServoAngle(L3, 180); 
  setServoAngle(L2, 90); setServoAngle(R1, 100); 
  delayWithFace(200);
  setServoAngle(L3, 180); 
  delayWithFace(300); 
  for (int i = 0; i < 4; i++) { 
    setServoAngle(L3, 180); delayWithFace(300); 
    setServoAngle(L3, 100); delayWithFace(300); 
  } 
  runStandPose(1); 
  if (currentCommand == "wave") currentCommand = "";
}

inline void runDancePose() { 
  Serial.println(F("DANCE")); 
  setFaceWithMode("dance", FACE_ANIM_LOOP); 
  setServoAngle(R1, 90); setServoAngle(R2, 90); 
  setServoAngle(L1, 90); setServoAngle(L2, 90); 
  setServoAngle(R4, 160); setServoAngle(R3, 160); 
  setServoAngle(L3, 10); setServoAngle(L4, 10); 
  delayWithFace(300); 
  for (int i = 0; i < 5; i++) { 
    setServoAngle(R4, 115); setServoAngle(R3, 115); 
    setServoAngle(L3, 10); setServoAngle(L4, 10); 
    delayWithFace(300); 
    setServoAngle(R4, 160); setServoAngle(R3, 160); 
    setServoAngle(L3, 65); setServoAngle(L4, 65); 
    delayWithFace(300); 
  } 
  runStandPose(1); 
  if (currentCommand == "dance") currentCommand = "";
}

inline void runSwimPose() { 
  Serial.println(F("SWIM")); 
  setFaceWithMode("swim", FACE_ANIM_ONCE); 
  for (int i = 0; i < 8; i++) setServoAngle(i, 90); 
  for (int i = 0; i < 4; i++) { 
    setServoAngle(R1, 135); setServoAngle(R2, 45); 
    setServoAngle(L1, 45); setServoAngle(L2, 135); 
    delayWithFace(400); 
    setServoAngle(R1, 90); setServoAngle(R2, 90); 
    setServoAngle(L1, 90); setServoAngle(L2, 90); 
    delayWithFace(400); 
  } 
  runStandPose(1); 
  if (currentCommand == "swim") currentCommand = "";
}

inline void runPointPose() { 
  Serial.println(F("POINT")); 
  setFaceWithMode("point", FACE_ANIM_BOOMERANG); 
  setServoAngle(L2, 90); setServoAngle(R1, 135); 
  setServoAngle(R2, 100); setServoAngle(L4, 180); 
  setServoAngle(L1, 25); setServoAngle(L3, 145);
  setServoAngle(R4, 80); setServoAngle(R3, 170); 
  delayWithFace(2000); 
  runStandPose(1); 
  if (currentCommand == "point") currentCommand = "";
}

inline void runPushupPose() {
  Serial.println(F("PUSHUP"));
  setFaceWithMode("pushup", FACE_ANIM_ONCE);
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delayWithFace(500);
  for (int i = 0; i < 4; i++) {
    setServoAngle(L3, 0);
    setServoAngle(R3, 180);
    delayWithFace(600);
    setServoAngle(L3, 90);
    setServoAngle(R3, 90);
    delayWithFace(500);
  }
  runStandPose(1);
  if (currentCommand == "pushup") currentCommand = "";
}

inline void runBowPose() {
  Serial.println(F("BOW"));
  setFaceWithMode("bow", FACE_ANIM_ONCE);
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 0);
  setServoAngle(R3, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 0);
  setServoAngle(L4, 180);
  delayWithFace(600);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delayWithFace(3000);
  runStandPose(1);
  if (currentCommand == "bow") currentCommand = "";
}

inline void runCutePose() {
  Serial.println(F("CUTE"));
  setFaceWithMode("cute", FACE_ANIM_ONCE);
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L2, 160);
  setServoAngle(R2, 20);
  setServoAngle(R4, 180);
  setServoAngle(L4, 0);

  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 180);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 5; i++) {
    setServoAngle(R4, 180);
    setServoAngle(L4, 45);
    delayWithFace(300);
    setServoAngle(R4, 135);
    setServoAngle(L4, 0);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "cute") currentCommand = "";
}

inline void runFreakyPose() {
  Serial.println(F("FREAKY"));
  setFaceWithMode("freaky", FACE_ANIM_ONCE);
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 90);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 3; i++) {
    setServoAngle(R3, 25);
    delayWithFace(400);
    setServoAngle(R3, 0);
    delayWithFace(400);
  }
  runStandPose(1);
  if (currentCommand == "freaky") currentCommand = "";
}

inline void runWormPose() {
  Serial.println(F("WORM"));
  setFaceWithMode("worm", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 180); setServoAngle(R2, 0); setServoAngle(L1, 0); setServoAngle(L2, 180);
  setServoAngle(R4, 90); setServoAngle(R3, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delayWithFace(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R3, 45); setServoAngle(L3, 135); setServoAngle(R4, 45); setServoAngle(L4, 135);
    delayWithFace(300);
    setServoAngle(R3, 135); setServoAngle(L3, 45); setServoAngle(R4, 135); setServoAngle(L4, 45);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "worm") currentCommand = "";
}

inline void runShakePose() {
  Serial.println(F("SHAKE"));
  setFaceWithMode("shake", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 135); setServoAngle(L1, 45); setServoAngle(L3, 90); setServoAngle(R3, 90);
  setServoAngle(L2, 90); setServoAngle(R2, 90);
  delayWithFace(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(L4, 135);
    delayWithFace(300);
    setServoAngle(R4, 0); setServoAngle(L4, 180);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "shake") currentCommand = "";
}

inline void runShrugPose() {
  Serial.println(F("SHRUG"));
  runStandPose(0);
  setFaceWithMode("dead", FACE_ANIM_ONCE);
  delayWithFace(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delayWithFace(1000);
  setFaceWithMode("shrug", FACE_ANIM_ONCE);
  setServoAngle(R3, 0); setServoAngle(R4, 180); setServoAngle(L3, 180); setServoAngle(L4, 0);
  delayWithFace(1500);
  runStandPose(1);
  if (currentCommand == "shrug") currentCommand = "";
}

inline void runDeadPose() {
  Serial.println(F("DEAD"));
  runStandPose(0);
  setFaceWithMode("dead", FACE_ANIM_BOOMERANG);
  delayWithFace(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  if (currentCommand == "dead") currentCommand = "";
}

inline void runCrabPose() {
  Serial.println(F("CRAB"));
  setFaceWithMode("crab", FACE_ANIM_ONCE);
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 90); setServoAngle(R2, 90); setServoAngle(L1, 90); setServoAngle(L2, 90);
  setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(R3, 135); setServoAngle(L3, 0); setServoAngle(L4, 180);
    delayWithFace(300);
    setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
    delayWithFace(300);
  }
  runStandPose(1);
  if (currentCommand == "crab") currentCommand = "";
}

// --- MOVEMENT ANIMATIONS ---
// Robust 2-phase diagonal trot gait optimized for low-friction/plastic feet
inline void runWalkPose() {
  Serial.println(F("WALK FWD"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  
  for (int i = 0; i < walkCycles; i++) {
    // --- Fase 1: Coppia A (R1/R3 + L2/L4) sollevata, Coppia B (L1/L3 + R2/R4) a terra ---
    // 1. Solleva Coppia A da terra per evitare trascinamenti
    setServoAngle(R3, 120); 
    setServoAngle(L4, 120);
    delayWithFace(frameDelay);
    
    // 2. Coppia A avanza in aria, Coppia B spinge indietro a terra (avanzamento)
    setServoAngle(R1, 160); 
    setServoAngle(L2, 110);
    setServoAngle(L1, 70);  
    setServoAngle(R2, 20);
    delayWithFace(frameDelay);
    
    // 3. Appoggia saldamente Coppia A a terra
    setServoAngle(R3, 180); 
    setServoAngle(L4, 180);
    delayWithFace(frameDelay);
    
    if (currentCommand != "forward") break;
    
    // --- Fase 2: Coppia B (L1/L3 + R2/R4) sollevata, Coppia A (R1/R3 + L2/L4) a terra ---
    // 4. Solleva Coppia B da terra
    setServoAngle(L3, 60);  
    setServoAngle(R4, 60);
    delayWithFace(frameDelay);
    
    // 5. Coppia B avanza in aria, Coppia A spinge indietro a terra (avanzamento)
    setServoAngle(L1, 20);  
    setServoAngle(R2, 70);
    setServoAngle(R1, 110); 
    setServoAngle(L2, 160);
    delayWithFace(frameDelay);
    
    // 6. Appoggia saldamente Coppia B a terra
    setServoAngle(L3, 0);   
    setServoAngle(R4, 0);
    delayWithFace(frameDelay);
    
    if (currentCommand != "forward") break;
  }
  
  runStandPose(1);
}

// Logic for walking backward with balanced diagonal trot
inline void runWalkBackward() {
  Serial.println(F("WALK BACK"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  
  for (int i = 0; i < walkCycles; i++) {
    // --- Fase 1: Coppia A sollevata, Coppia B a terra ---
    // 1. Solleva Coppia A
    setServoAngle(R3, 120); 
    setServoAngle(L4, 120);
    delayWithFace(frameDelay);
    
    // 2. Coppia A arretra in aria, Coppia B spinge in avanti a terra (arretramento)
    setServoAngle(R1, 110); 
    setServoAngle(L2, 160);
    setServoAngle(L1, 20);  
    setServoAngle(R2, 70);
    delayWithFace(frameDelay);
    
    // 3. Appoggia Coppia A a terra
    setServoAngle(R3, 180); 
    setServoAngle(L4, 180);
    delayWithFace(frameDelay);
    
    if (currentCommand != "backward") break;
    
    // --- Fase 2: Coppia B sollevata, Coppia A a terra ---
    // 4. Solleva Coppia B
    setServoAngle(L3, 60);  
    setServoAngle(R4, 60);
    delayWithFace(frameDelay);
    
    // 5. Coppia B arretra in aria, Coppia A spinge in avanti a terra (arretramento)
    setServoAngle(L1, 70);  
    setServoAngle(R2, 20);
    setServoAngle(R1, 160); 
    setServoAngle(L2, 110);
    delayWithFace(frameDelay);
    
    // 6. Appoggia Coppia B a terra
    setServoAngle(L3, 0);   
    setServoAngle(R4, 0);
    delayWithFace(frameDelay);
    
    if (currentCommand != "backward") break;
  }
  
  runStandPose(1);
}

// Balanced turn left logic
inline void runTurnLeft() {
  Serial.println(F("TURN LEFT"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  
  for (int i = 0; i < walkCycles; i++) {
    // --- Fase 1: Coppia A sollevata ---
    setServoAngle(R3, 120); 
    setServoAngle(L4, 120);
    delayWithFace(frameDelay);
    
    // R1 avanti in aria, L2 indietro in aria; L1 avanti a terra, R2 indietro a terra
    setServoAngle(R1, 160); 
    setServoAngle(L2, 160);
    setServoAngle(L1, 20);  
    setServoAngle(R2, 20);
    delayWithFace(frameDelay);
    
    setServoAngle(R3, 180); 
    setServoAngle(L4, 180);
    delayWithFace(frameDelay);
    
    if (currentCommand != "left") break;
    
    // --- Fase 2: Coppia B sollevata ---
    setServoAngle(L3, 60);  
    setServoAngle(R4, 60);
    delayWithFace(frameDelay);
    
    // R2 avanti in aria, L1 indietro in aria; R1 indietro a terra, L2 avanti a terra
    setServoAngle(R2, 70);  
    setServoAngle(L1, 70);
    setServoAngle(R1, 110); 
    setServoAngle(L2, 110);
    delayWithFace(frameDelay);
    
    setServoAngle(L3, 0);   
    setServoAngle(R4, 0);
    delayWithFace(frameDelay);
    
    if (currentCommand != "left") break;
  }
  
  runStandPose(1);
}

// Balanced turn right logic
inline void runTurnRight() {
  Serial.println(F("TURN RIGHT"));
  setFaceWithMode("walk", FACE_ANIM_ONCE);
  
  for (int i = 0; i < walkCycles; i++) {
    // --- Fase 1: Coppia A sollevata ---
    setServoAngle(R3, 120); 
    setServoAngle(L4, 120);
    delayWithFace(frameDelay);
    
    // R1 indietro in aria, L2 avanti in aria; L1 indietro a terra, R2 avanti a terra
    setServoAngle(R1, 110); 
    setServoAngle(L2, 110);
    setServoAngle(L1, 70);  
    setServoAngle(R2, 70);
    delayWithFace(frameDelay);
    
    setServoAngle(R3, 180); 
    setServoAngle(L4, 180);
    delayWithFace(frameDelay);
    
    if (currentCommand != "right") break;
    
    // --- Fase 2: Coppia B sollevata ---
    setServoAngle(L3, 60);  
    setServoAngle(R4, 60);
    delayWithFace(frameDelay);
    
    // R2 indietro in aria, L1 avanti in aria; R1 avanti a terra, L2 indietro a terra
    setServoAngle(R2, 20);  
    setServoAngle(L1, 20);
    setServoAngle(R1, 160); 
    setServoAngle(L2, 160);
    delayWithFace(frameDelay);
    
    setServoAngle(L3, 0);   
    setServoAngle(R4, 0);
    delayWithFace(frameDelay);
    
    if (currentCommand != "right") break;
  }
  
  runStandPose(1);
}
