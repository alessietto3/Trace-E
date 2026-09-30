#pragma once

#include <Arduino.h>

// ======================================================================
// --- WEB INTERFACE HTML ---
// ======================================================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Trace-E Robot Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <meta charset="UTF-8">
  <style>
    :root {
      --content-color: #ff8c42;
      --content-color-dark: #e67a30;
      --content-color-darker: #cc6b29;
      --content-color-glow: rgba(255, 140, 66, 0.35);
      --card-bg: rgba(26, 32, 44, 0.85);
      --card-border: rgba(255, 255, 255, 0.1);
    }
    
    * {
      box-sizing: border-box;
      user-select: none;
      -webkit-user-select: none;
      -webkit-touch-callout: none;
    }
    
    body { 
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; 
      text-align: center; 
      background: radial-gradient(circle at top, #1a233a, #0b0f19 80%);
      color: #f1f5f9; 
      touch-action: manipulation; 
      margin: 0;
      padding: 12px;
      min-height: 100vh;
    }
    
    .header-bar {
      display: flex;
      justify-content: space-between;
      align-items: center;
      max-width: 960px;
      margin: 0 auto 12px auto;
      padding: 0 4px;
    }

    h2 { 
      margin: 0;
      color: #fff;
      font-size: 22px;
      font-weight: 700;
      letter-spacing: -0.5px;
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .badge-status {
      font-size: 11px;
      padding: 4px 10px;
      border-radius: 999px;
      background: rgba(46, 204, 113, 0.15);
      border: 1px solid rgba(46, 204, 113, 0.4);
      color: #2ecc71;
      font-weight: 600;
      display: inline-flex;
      align-items: center;
      gap: 6px;
    }
    .badge-status::before {
      content: '';
      width: 6px;
      height: 6px;
      background: #2ecc71;
      border-radius: 50%;
      box-shadow: 0 0 6px #2ecc71;
    }

    /* Mode Banner & Category Tabs */
    .mode-container {
      max-width: 960px;
      margin: 0 auto 14px auto;
      background: rgba(20, 26, 38, 0.7);
      border: 1px solid var(--card-border);
      border-radius: 14px;
      padding: 8px 12px;
      display: flex;
      flex-wrap: wrap;
      justify-content: space-between;
      align-items: center;
      gap: 8px;
    }

    .mode-label {
      font-size: 12px;
      font-weight: 600;
      color: #94a3b8;
    }

    .mode-btn-group {
      display: inline-flex;
      background: rgba(10, 14, 23, 0.8);
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 10px;
      padding: 3px;
      gap: 3px;
    }

    .btn-mode {
      background: transparent;
      border: none;
      color: #94a3b8;
      padding: 6px 12px;
      font-size: 12px;
      font-weight: 600;
      border-radius: 7px;
      cursor: pointer;
      box-shadow: none;
      transition: all 0.2s ease;
    }
    .btn-mode.active {
      background: linear-gradient(135deg, var(--content-color), var(--content-color-dark));
      color: #fff;
      box-shadow: 0 2px 8px var(--content-color-glow);
    }

    /* Command Queue & Live Status */
    .status-bar {
      max-width: 960px;
      margin: 0 auto 14px auto;
      font-size: 12px;
      color: #94a3b8;
      background: rgba(15, 23, 42, 0.6);
      border: 1px solid rgba(255, 255, 255, 0.05);
      border-radius: 10px;
      padding: 6px 12px;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    .command-queue.full {
      color: #ff6b6b;
      font-weight: bold;
    }
    
    /* Layout Columns */
    .sections-container {
      display: grid;
      grid-template-columns: 1fr;
      gap: 14px;
      max-width: 960px;
      margin: 0 auto;
    }
    
    @media (min-width: 860px) {
      .sections-container {
        grid-template-columns: 320px 1fr;
        align-items: start;
      }
    }
    
    .section {
      background: var(--card-bg);
      border: 1px solid var(--card-border);
      border-radius: 16px;
      padding: 14px;
      box-shadow: 0 8px 24px rgba(0,0,0,0.35);
      backdrop-filter: blur(10px);
    }
    
    .section-title {
      font-size: 13px;
      font-weight: 700;
      color: var(--content-color);
      margin: 0 0 12px 0;
      text-transform: uppercase;
      letter-spacing: 0.8px;
      display: flex;
      align-items: center;
      justify-content: space-between;
    }

    /* Category Filter Tabs */
    .cat-tabs {
      display: flex;
      gap: 4px;
      background: rgba(10, 14, 23, 0.8);
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 8px;
      padding: 2px;
    }
    .btn-cat {
      background: transparent;
      border: none;
      color: #94a3b8;
      padding: 4px 8px;
      font-size: 11px;
      font-weight: 600;
      border-radius: 6px;
      cursor: pointer;
      box-shadow: none;
      transition: all 0.2s;
    }
    .btn-cat.active {
      background: var(--content-color);
      color: #fff;
    }
    
    /* D-Pad Controls */
    .dpad-container { 
      display: flex; 
      flex-direction: column;
      align-items: center;
      gap: 12px;
      width: 100%;
    }
    .dpad { 
      display: grid; 
      grid-template-columns: repeat(3, 1fr); 
      grid-template-rows: repeat(2, 1fr); 
      gap: 8px;
      width: 100%;
      max-width: 260px;
      aspect-ratio: 3 / 2;
    }
    .dpad button { 
      font-size: 28px; 
      background: linear-gradient(145deg, #2a3447, #1e2536);
      border: 1px solid rgba(255,255,255,0.12);
      color: #f8fafc;
      border-radius: 12px;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: 0 4px 10px rgba(0,0,0,0.3);
      transition: all 0.1s ease;
    }
    .dpad button:active {
      background: linear-gradient(145deg, var(--content-color), var(--content-color-dark));
      border-color: var(--content-color);
      box-shadow: 0 2px 6px var(--content-color-glow);
      transform: translateY(2px);
    }
    .spacer { 
      visibility: hidden; 
    }
    
    /* STOP ALL Button */
    .btn-stop-all { 
      background: linear-gradient(145deg, #ef4444, #dc2626);
      width: 100%; 
      font-size: 14px; 
      font-weight: 800;
      padding: 14px; 
      box-shadow: 0 4px 14px rgba(239, 68, 68, 0.4);
      border: 1px solid #f87171;
      border-radius: 12px;
      color: #fff;
      text-transform: uppercase;
      letter-spacing: 1.5px;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 6px;
      transition: all 0.1s;
    }
    .btn-stop-all:active { 
      background: linear-gradient(145deg, #dc2626, #b91c1c);
      transform: translateY(2px); 
    }

    /* Beautiful Action / Expression Cards Grid */
    .actions-grid { 
      display: grid; 
      grid-template-columns: repeat(2, 1fr); 
      gap: 8px; 
      max-height: 520px;
      overflow-y: auto;
      padding-right: 2px;
    }
    @media (min-width: 600px) {
      .actions-grid {
        grid-template-columns: repeat(3, 1fr);
      }
    }

    .btn-action-card {
      background: linear-gradient(145deg, #1e293b, #151d2e);
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 12px;
      padding: 8px 10px;
      display: flex;
      align-items: center;
      gap: 10px;
      cursor: pointer;
      text-align: left;
      color: #f1f5f9;
      box-shadow: 0 3px 8px rgba(0,0,0,0.2);
      transition: all 0.15s ease;
      position: relative;
      overflow: hidden;
    }
    .btn-action-card:hover {
      background: linear-gradient(145deg, #283548, #1b2438);
      border-color: rgba(255, 140, 66, 0.4);
      transform: translateY(-1px);
    }
    .btn-action-card:active {
      background: linear-gradient(145deg, var(--content-color-dark), var(--content-color-darker));
      border-color: var(--content-color);
      box-shadow: 0 2px 6px var(--content-color-glow);
      transform: translateY(1px);
    }
    
    .card-icon {
      font-size: 24px;
      line-height: 1;
      width: 38px;
      height: 38px;
      min-width: 38px;
      display: flex;
      align-items: center;
      justify-content: center;
      background: rgba(0, 0, 0, 0.25);
      border: 1px solid rgba(255, 255, 255, 0.06);
      border-radius: 10px;
    }
    
    .card-info {
      flex: 1;
      overflow: hidden;
    }
    .card-title {
      font-size: 13px;
      font-weight: 700;
      color: #f8fafc;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
    }
    .card-desc {
      font-size: 10px;
      color: #94a3b8;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
      margin-top: 1px;
    }

    /* Talk Mode & Extra Controls */
    .toggle-row {
      display: flex;
      justify-content: space-between;
      align-items: center;
      background: rgba(15, 23, 42, 0.5);
      border: 1px solid rgba(255, 255, 255, 0.05);
      border-radius: 10px;
      padding: 8px 12px;
      margin-top: 10px;
      font-size: 12px;
      color: #cbd5e1;
    }
    .switch {
      position: relative;
      display: inline-block;
      width: 36px;
      height: 20px;
    }
    .switch input { opacity: 0; width: 0; height: 0; }
    .slider-switch {
      position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
      background-color: #334155;
      transition: .2s;
      border-radius: 20px;
    }
    .slider-switch:before {
      position: absolute; content: ""; height: 14px; width: 14px; left: 3px; bottom: 3px;
      background-color: white;
      transition: .2s;
      border-radius: 50%;
    }
    input:checked + .slider-switch { background-color: var(--content-color); }
    input:checked + .slider-switch:before { transform: translateX(16px); }

    /* System / Utility Buttons */
    .btn-sys {
      background: linear-gradient(145deg, #2a3447, #1e2536);
      border: 1px solid rgba(255, 255, 255, 0.08);
      color: #f1f5f9;
      font-size: 12px;
      font-weight: 600;
      padding: 9px 12px;
      border-radius: 10px;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 6px;
      width: 100%;
      transition: all 0.15s;
    }
    .btn-sys:active {
      transform: translateY(1px);
    }
    
    /* Gamepad Status */
    .gamepad-status {
      font-size: 11px;
      padding: 6px 10px;
      border-radius: 8px;
      border: 1px solid #475569;
      color: #94a3b8;
      background: rgba(15, 23, 42, 0.8);
      display: inline-block;
      width: 100%;
      box-sizing: border-box;
      margin-top: 8px;
    }
    .gamepad-status.connected {
      border-color: #2ecc71;
      color: #2ecc71;
      background: rgba(46, 204, 113, 0.1);
    }

    /* Modal Panels */
    .settings-panel { 
      display: none; 
      position: fixed; 
      top: 0; 
      left: 0; 
      width: 100%; 
      height: 100%; 
      background: rgba(0,0,0,0.85); 
      z-index: 100; 
      backdrop-filter: blur(8px);
      overflow-y: auto;
      padding: 16px;
      box-sizing: border-box;
    }
    .settings-content { 
      background: linear-gradient(145deg, #1e293b, #0f172a);
      border: 1px solid rgba(255, 255, 255, 0.12); 
      max-width: 420px; 
      margin: 20px auto; 
      padding: 20px; 
      border-radius: 18px; 
      text-align: left; 
      box-shadow: 0 16px 40px rgba(0,0,0,0.7); 
    }
    .settings-content h3 { 
      color: var(--content-color); 
      margin-top: 0; 
      text-align: center;
      font-size: 20px;
    }
    .settings-section {
      margin: 16px 0;
      padding: 12px;
      background: rgba(0,0,0,0.25);
      border: 1px solid rgba(255,255,255,0.05);
      border-radius: 10px;
    }
    .settings-section h4 {
      color: var(--content-color);
      margin: 0 0 10px 0;
      font-size: 12px;
      text-transform: uppercase;
      letter-spacing: 0.8px;
    }
    .settings-content label { 
      display: block; 
      margin-top: 10px; 
      font-weight: 500; 
      color: #94a3b8;
      font-size: 12px;
    }
    .settings-content input, 
    .settings-content select { 
      width: 100%; 
      padding: 8px 10px; 
      margin-top: 4px; 
      background: #0f172a; 
      color: #fff; 
      border: 1px solid #334155; 
      border-radius: 8px; 
      box-sizing: border-box;
      font-size: 13px;
    }
    .btn-save { 
      background: linear-gradient(145deg, #22c55e, #16a34a);
      width: 100%; 
      margin-top: 20px; 
      color: #fff; 
      border: none;
      padding: 12px;
      border-radius: 10px;
      font-weight: 700;
      cursor: pointer;
    }
    .btn-close { 
      background: linear-gradient(145deg, #ef4444, #dc2626);
      width: 100%; 
      margin-top: 8px; 
      color: #fff; 
      border: none;
      padding: 10px;
      border-radius: 10px;
      font-weight: 600;
      cursor: pointer;
    }

    /* Slider styling in manual control */
    .motor-slider { margin: 10px 0; }
    .motor-slider label { display: flex; justify-content: space-between; font-size: 11px; color: #94a3b8; margin-bottom: 3px; }
    .motor-slider input[type="range"] { width: 100%; height: 5px; background: #334155; border-radius: 4px; outline: none; -webkit-appearance: none; }
    .motor-slider input[type="range"]::-webkit-slider-thumb { -webkit-appearance: none; width: 16px; height: 16px; background: var(--content-color); border-radius: 50%; cursor: pointer; }
    .lock-indicator { font-size: 11px; color: #f87171; text-align: center; margin-top: 4px; display: none; }
    .lock-indicator.active { display: block; }

    /* Custom Scrollbars */
    ::-webkit-scrollbar { width: 5px; height: 5px; }
    ::-webkit-scrollbar-thumb { background: rgba(255,255,255,0.15); border-radius: 10px; }
  </style>
</head>
<body>

  <!-- Header -->
  <div class="header-bar">
    <h2><span>🤖</span> Trace-E</h2>
    <div class="badge-status">ESP32 Online</div>
  </div>

  <!-- Mode Selector Banner -->
  <div class="mode-container">
    <div class="mode-label">Azione Tasti:</div>
    <div class="mode-btn-group">
      <button id="modeBtnCombo" class="btn-mode active" onclick="setExecMode('combo')">✨ Faccia + Movimento</button>
      <button id="modeBtnFace" class="btn-mode" onclick="setExecMode('face_only')">📺 Solo Faccia</button>
      <button id="modeBtnMotion" class="btn-mode" onclick="setExecMode('motion_only')">🦾 Solo Movimento</button>
    </div>
  </div>

  <!-- Live Status & Command Queue -->
  <div class="status-bar">
    <div id="liveFeedback">Pronto. Tocca un pulsante per interagire!</div>
    <div id="queueStatus" class="command-queue">Coda: 0/3</div>
  </div>
  
  <div class="sections-container">
    
    <!-- LEFT: Movement D-Pad & System Card -->
    <div style="display: flex; flex-direction: column; gap: 14px;">
      
      <!-- Movement D-Pad -->
      <div class="section">
        <div class="section-title">
          <span>🎮 Movimento Continuo</span>
          <span style="font-size:10px; color:#94a3b8; text-transform:none;">Trot Gait</span>
        </div>
        <div class="dpad-container">
          <div class="dpad">
            <div class="spacer"></div>
            <button onmousedown="move('forward')" onmouseup="stop()" ontouchstart="move('forward')" ontouchend="stop()">▲</button>
            <div class="spacer"></div>
            
            <button onmousedown="move('left')" onmouseup="stop()" ontouchstart="move('left')" ontouchend="stop()">◀</button>
            <button onmousedown="move('backward')" onmouseup="stop()" ontouchstart="move('backward')" ontouchend="stop()">▼</button>
            <button onmousedown="move('right')" onmouseup="stop()" ontouchstart="move('right')" ontouchend="stop()">▶</button>
          </div>
          <button class="btn-stop-all" onclick="stop()">🛑 STOP EMERGENZA</button>
        </div>
      </div>

      <!-- System & Talk Mode Card -->
      <div class="section">
        <div class="section-title">
          <span>⚙️ Sistema & Opzioni</span>
        </div>

        <div class="toggle-row">
          <span>Animazione Bocca Parlante</span>
          <label class="switch">
            <input type="checkbox" id="talkModeToggle" onchange="toggleTalkMode()">
            <span class="slider-switch"></span>
          </label>
        </div>

        <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 8px; margin-top: 10px;">
          <button class="btn-sys" onclick="openSettings()">⚙️ Impostazioni</button>
          <button class="btn-sys" onclick="openSdManager()">📁 MicroSD Face</button>
        </div>

        <div id="gamepadStatus" class="gamepad-status">Gamepad disconnesso</div>
      </div>

    </div>

    <!-- RIGHT: Unified Expressive Actions Grid -->
    <div class="section">
      <div class="section-title">
        <span>🎭 Azioni & Espressioni Robot</span>
        <div class="cat-tabs">
          <button class="btn-cat active" onclick="filterCat('all')">Tutti</button>
          <button class="btn-cat" onclick="filterCat('emozioni')">Emozioni</button>
          <button class="btn-cat" onclick="filterCat('coreografie')">Ballo/Mov</button>
          <button class="btn-cat" onclick="filterCat('posture')">Posture</button>
        </div>
      </div>

      <div class="actions-grid">
        
        <!-- Postures -->
        <button class="btn-action-card" data-cat="posture" onclick="execAction('Riposo (Rest)', 'rest', 'rest')">
          <div class="card-icon">😴</div>
          <div class="card-info">
            <div class="card-title">Riposo</div>
            <div class="card-desc">Faccia sleep + Posa 90°</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="posture" onclick="execAction('In Piedi (Stand)', 'stand', 'stand')">
          <div class="card-icon">🤖</div>
          <div class="card-info">
            <div class="card-title">In Piedi</div>
            <div class="card-desc">Faccia stand + Postura</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="posture" onclick="execAction('Inchino (Bow)', 'bow', 'bow')">
          <div class="card-icon">🙇</div>
          <div class="card-info">
            <div class="card-title">Inchino</div>
            <div class="card-desc">Faccia bow + Inclinazione</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="posture" onclick="execAction('K.O. / Dead', 'dead', 'dead')">
          <div class="card-icon">💀</div>
          <div class="card-info">
            <div class="card-title">K.O. / Dead</div>
            <div class="card-desc">Faccia dead + Collasso</div>
          </div>
        </button>

        <!-- Coreografie & Movimenti -->
        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Saluto (Wave)', 'wave', 'wave')">
          <div class="card-icon">👋</div>
          <div class="card-info">
            <div class="card-title">Saluto</div>
            <div class="card-desc">Faccia wave + Zampa</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Balla (Dance)', 'dance', 'dance')">
          <div class="card-icon">💃</div>
          <div class="card-info">
            <div class="card-title">Ballo</div>
            <div class="card-desc">Faccia dance + Ritmo</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Nuoto (Swim)', 'swim', 'swim')">
          <div class="card-icon">🏊</div>
          <div class="card-info">
            <div class="card-title">Nuoto</div>
            <div class="card-desc">Faccia swim + Bracciate</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Indica (Point)', 'point', 'point')">
          <div class="card-icon">👉</div>
          <div class="card-info">
            <div class="card-title">Indica</div>
            <div class="card-desc">Faccia point + Zampa alta</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Flessioni (Pushup)', 'pushup', 'pushup')">
          <div class="card-icon">💪</div>
          <div class="card-info">
            <div class="card-title">Flessioni</div>
            <div class="card-desc">Faccia pushup + Movimento</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Verme (Worm)', 'worm', 'worm')">
          <div class="card-icon">🐛</div>
          <div class="card-info">
            <div class="card-title">Verme</div>
            <div class="card-desc">Ondulazione totale</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Scuotiti (Shake)', 'shake', 'shake')">
          <div class="card-icon">📳</div>
          <div class="card-info">
            <div class="card-title">Scuotiti</div>
            <div class="card-desc">Vibrazione zampe</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="coreografie" onclick="execAction('Granchio (Crab)', 'crab', 'crab')">
          <div class="card-icon">🦀</div>
          <div class="card-info">
            <div class="card-title">Granchio</div>
            <div class="card-desc">Passo laterale</div>
          </div>
        </button>

        <!-- Emozioni -->
        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Carino (Cute)', 'cute', 'cute')">
          <div class="card-icon">✨</div>
          <div class="card-info">
            <div class="card-title">Carino</div>
            <div class="card-desc">Faccia cute + Wiggle</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Freaky / Matto', 'freaky', 'freaky')">
          <div class="card-icon">🌀</div>
          <div class="card-info">
            <div class="card-title">Freaky</div>
            <div class="card-desc">Faccia freaky + Scatto</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Spallucce (Shrug)', 'confused', 'shrug')">
          <div class="card-icon">🤷</div>
          <div class="card-info">
            <div class="card-title">Spallucce</div>
            <div class="card-desc">Faccia confusa + Shrug</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Felice (Happy)', 'happy', 'happy')">
          <div class="card-icon">😊</div>
          <div class="card-info">
            <div class="card-title">Felice</div>
            <div class="card-desc">Faccia happy + Balletto</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Amore (Love)', 'love', 'love')">
          <div class="card-icon">❤️</div>
          <div class="card-info">
            <div class="card-title">Amore</div>
            <div class="card-desc">Cuori + Cuoricino motion</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Arrabbiato (Angry)', 'angry', 'angry')">
          <div class="card-icon">😡</div>
          <div class="card-info">
            <div class="card-title">Arrabbiato</div>
            <div class="card-desc">Faccia angry + Stomp zampe</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Triste (Sad)', 'sad', 'sad')">
          <div class="card-icon">😢</div>
          <div class="card-info">
            <div class="card-title">Triste</div>
            <div class="card-desc">Faccia sad + Abbassamento</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Sorpreso (Surprised)', 'surprised', 'surprised')">
          <div class="card-icon">😮</div>
          <div class="card-info">
            <div class="card-title">Sorpreso</div>
            <div class="card-desc">Scatto indietro</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Eccitato (Excited)', 'excited', 'excited')">
          <div class="card-icon">🤩</div>
          <div class="card-info">
            <div class="card-title">Eccitato</div>
            <div class="card-desc">Danza rapida felice</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Pensieroso', 'thinking', 'point')">
          <div class="card-icon">🤔</div>
          <div class="card-info">
            <div class="card-title">Pensieroso</div>
            <div class="card-desc">Faccia thinking + Tilt</div>
          </div>
        </button>

        <button class="btn-action-card" data-cat="emozioni" onclick="execAction('Occhiolino (Blink)', 'idle_blink', 'stand')">
          <div class="card-icon">👁️</div>
          <div class="card-info">
            <div class="card-title">Blink</div>
            <div class="card-desc">Ammicco occhi</div>
          </div>
        </button>

      </div>
    </div>

  </div>

  <!-- Settings Panel -->
  <div id="settingsPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Impostazioni</h3>
      
      <div class="settings-section">
        <h4>Parametri Animazione</h4>
        <label>Frame Delay (ms):</label>
        <input type="number" id="frameDelay" min="1" max="1000" step="1">
        <label>Cicli Passo (Walk Cycles):</label>
        <input type="number" id="walkCycles" min="1" max="50" step="1">
      </div>

      <div class="settings-section">
        <h4>Parametri Motori</h4>
        <label>Ritardo Corrente Motori (ms):</label>
        <input type="number" id="motorCurrentDelay" min="0" max="500" step="1">
        <label>Velocità Motori:</label>
        <select id="motorSpeed">
          <option value="slow">Lenta</option>
          <option value="medium" selected>Media</option>
          <option value="fast">Veloce</option>
        </select>
      </div>

      <div class="settings-section">
        <h4>Tema & Colore Accent</h4>
        <label>Colore Interfaccia:</label>
        <select id="themeColor" onchange="onThemeSelectChange()">
          <option value="#ff8c42">Arancione Trace-E</option>
          <option value="#38bdf8">Ciano Tech</option>
          <option value="#22c55e">Verde Emerald</option>
          <option value="#ef4444">Rosso Energico</option>
          <option value="#a855f7">Viola Neon</option>
          <option value="#eab308">Giallo Cyber</option>
          <option value="#ec4899">Rosa Magenta</option>
          <option value="custom">Personalizzato</option>
        </select>
        <input type="color" id="customColor" value="#ff8c42" style="margin-top: 6px; display: none;">
      </div>

      <div class="settings-section">
        <h4>Connessione WiFi (Stazione)</h4>
        <div id="wifiStatus" style="font-size:12px; color:#cbd5e1; margin-bottom:8px;">Controllo...</div>
        <label>Rete WiFi:</label>
        <select id="wifiSsid">
          <option value="">— Clicca 'Cerca Reti' —</option>
        </select>
        <label style="margin-top:8px; display:flex; align-items:center; gap:6px;">
          <input type="checkbox" id="wifiManual" style="width:auto;" onchange="toggleManualSsid()">
          Inserisci nome manualmente (rete nascosta)
        </label>
        <input type="text" id="wifiSsidManual" placeholder="Nome rete SSID" style="display:none;">
        <label>Password WiFi:</label>
        <input type="password" id="wifiPass" placeholder="Password di rete">
        <div style="display:grid; grid-template-columns:1fr 1fr; gap:6px; margin-top:10px;">
          <button class="btn-sys" onclick="scanWifi()">📡 Cerca Reti</button>
          <button class="btn-sys" style="background:linear-gradient(145deg, #22c55e, #16a34a);" onclick="connectWifi()">Connetti</button>
        </div>
        <div id="wifiResult" style="font-size:12px; margin-top:8px; min-height:16px;"></div>
      </div>

      <button class="btn-sys" style="margin-top: 10px;" onclick="openMotorControl()">🎛️ Controllo Manuale Singoli Motori</button>

      <button class="btn-save" onclick="saveSettings()">Salva Impostazioni</button>
      <button class="btn-close" onclick="closeSettings()">Chiudi</button>
    </div>
  </div>

  <!-- Manual Motor Control Panel -->
  <div id="motorControlPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Controllo Manuale Motori</h3>
      <div class="lock-indicator" id="lockIndicator">Bloccato durante animazioni in corso</div>
      
      <div class="settings-section">
        <div class="motor-slider"><label><span>S0 R1 (Anca Ant Dx)</span><span id="m1val">90&deg;</span></label><input type="range" id="motor1" min="0" max="180" value="90" oninput="updateMotor(1, this.value)"></div>
        <div class="motor-slider"><label><span>S1 R2 (Anca Post Dx)</span><span id="m2val">90&deg;</span></label><input type="range" id="motor2" min="0" max="180" value="90" oninput="updateMotor(2, this.value)"></div>
        <div class="motor-slider"><label><span>S2 L1 (Anca Ant Sx)</span><span id="m3val">90&deg;</span></label><input type="range" id="motor3" min="0" max="180" value="90" oninput="updateMotor(3, this.value)"></div>
        <div class="motor-slider"><label><span>S3 L2 (Anca Post Sx)</span><span id="m4val">90&deg;</span></label><input type="range" id="motor4" min="0" max="180" value="90" oninput="updateMotor(4, this.value)"></div>
        <div class="motor-slider"><label><span>S4 R4 (Gamba Post Dx)</span><span id="m5val">90&deg;</span></label><input type="range" id="motor5" min="0" max="180" value="90" oninput="updateMotor(5, this.value)"></div>
        <div class="motor-slider"><label><span>S5 R3 (Gamba Ant Dx)</span><span id="m6val">90&deg;</span></label><input type="range" id="motor6" min="0" max="180" value="90" oninput="updateMotor(6, this.value)"></div>
        <div class="motor-slider"><label><span>S6 L3 (Gamba Ant Sx)</span><span id="m7val">90&deg;</span></label><input type="range" id="motor7" min="0" max="180" value="90" oninput="updateMotor(7, this.value)"></div>
        <div class="motor-slider"><label><span>S7 L4 (Gamba Post Sx)</span><span id="m8val">90&deg;</span></label><input type="range" id="motor8" min="0" max="180" value="90" oninput="updateMotor(8, this.value)"></div>
      </div>

      <button class="btn-close" onclick="closeMotorControl()">Chiudi</button>
    </div>
  </div>

  <!-- MicroSD Face Manager Panel -->
  <div id="sdManagerPanel" class="settings-panel">
    <div class="settings-content">
      <h3>MicroSD Face Manager</h3>
      
      <div class="settings-section">
        <h4>Carica Faccia (.bin)</h4>
        <p style="font-size:11px; color:#94a3b8; margin:0 0 8px 0;">Seleziona un file binario 160x128 (es. <code>happy_0.bin</code>):</p>
        <input type="file" id="faceFileInput" accept=".bin" style="color:#fff; margin-bottom:8px; width:100%;">
        <button class="btn-sys" style="background:linear-gradient(145deg, #38bdf8, #0284c7);" onclick="uploadFaceFile()">Carica su MicroSD</button>
        <div id="uploadStatus" style="font-size:12px; margin-top:6px; min-height:16px;"></div>
      </div>

      <div class="settings-section">
        <h4>Facce su MicroSD (/faces)</h4>
        <div id="sdFilesList" style="font-size:12px; max-height:180px; overflow-y:auto; margin-bottom:8px; border:1px solid #334155; border-radius:8px; padding:6px; background:rgba(0,0,0,0.3);">
          Caricamento...
        </div>
        <button class="btn-sys" onclick="loadSdFiles()">Aggiorna Elenco</button>
      </div>

      <button class="btn-close" onclick="closeSdManager()">Chiudi</button>
    </div>
  </div>

<script>
// State management
let commandQueue = 0;
const MAX_COMMANDS = 3;
let motorsLocked = false;
let currentExecMode = 'combo'; // 'combo', 'face_only', 'motion_only'
let talkModeActive = false;

document.addEventListener('DOMContentLoaded', () => {
  loadTheme();
});

function setExecMode(mode) {
  currentExecMode = mode;
  document.getElementById('modeBtnCombo').classList.toggle('active', mode === 'combo');
  document.getElementById('modeBtnFace').classList.toggle('active', mode === 'face_only');
  document.getElementById('modeBtnMotion').classList.toggle('active', mode === 'motion_only');
  
  const desc = mode === 'combo' ? 'Faccia + Movimento Sincronizzati' : (mode === 'face_only' ? 'Solo Display Faccia' : 'Solo Movimento Servo');
  showLiveFeedback('Modalità impostata: ' + desc);
}

function filterCat(cat) {
  const tabs = document.querySelectorAll('.btn-cat');
  tabs.forEach(t => t.classList.remove('active'));
  event.target.classList.add('active');

  const cards = document.querySelectorAll('.btn-action-card');
  cards.forEach(card => {
    if (cat === 'all' || card.getAttribute('data-cat') === cat) {
      card.style.display = 'flex';
    } else {
      card.style.display = 'none';
    }
  });
}

function showLiveFeedback(msg) {
  const el = document.getElementById('liveFeedback');
  if (el) el.textContent = msg;
}

function updateQueueStatus() {
  const queueEl = document.getElementById('queueStatus');
  queueEl.textContent = `Coda: ${commandQueue}/${MAX_COMMANDS}`;
  if (commandQueue >= MAX_COMMANDS) queueEl.classList.add('full');
  else queueEl.classList.remove('full');
}

function canSendCommand() {
  return commandQueue < MAX_COMMANDS;
}

function incrementQueue() {
  commandQueue++;
  updateQueueStatus();
  setTimeout(() => {
    if (commandQueue > 0) commandQueue--;
    updateQueueStatus();
  }, 1000);
}

function lockMotors(duration = 3000) {
  motorsLocked = true;
  const ind = document.getElementById('lockIndicator');
  if (ind) ind.classList.add('active');
  for (let i = 1; i <= 8; i++) {
    const slider = document.getElementById('motor' + i);
    if (slider) slider.disabled = true;
  }
  setTimeout(() => {
    motorsLocked = false;
    if (ind) ind.classList.remove('active');
    for (let i = 1; i <= 8; i++) {
      const slider = document.getElementById('motor' + i);
      if (slider) slider.disabled = false;
    }
  }, duration);
}

function move(dir) { 
  if (!canSendCommand()) return;
  incrementQueue();
  showLiveFeedback('Movimento: ' + dir);
  fetch('/cmd?go=' + dir).catch(console.log); 
}

function stop() { 
  commandQueue = 0;
  updateQueueStatus();
  showLiveFeedback('STOP / Riposo');
  fetch('/cmd?stop=1').catch(console.log); 
}

function toggleTalkMode() {
  const toggle = document.getElementById('talkModeToggle');
  talkModeActive = toggle ? toggle.checked : false;
  showLiveFeedback(talkModeActive ? 'Talk Mode ATTIVATO (bocca animata)' : 'Talk Mode DISATTIVATO');
}

// Unified Action Trigger (Face + Pose or Selected Mode)
function execAction(title, faceName, poseName) {
  if (!canSendCommand()) return;
  incrementQueue();

  let targetFace = faceName;
  if (talkModeActive) {
    const talkSupported = ['happy', 'sad', 'angry', 'surprised', 'sleepy', 'love', 'excited', 'confused', 'thinking'];
    if (talkSupported.includes(faceName)) {
      targetFace = 'talk_' + faceName;
    }
  }

  if (currentExecMode === 'combo') {
    lockMotors(3000);
    showLiveFeedback(`✨ Azione: ${title}`);
    fetch('/cmd?pose=' + poseName).catch(console.log);
  } else if (currentExecMode === 'face_only') {
    showLiveFeedback(`📺 Faccia: ${title}`);
    fetch('/cmd?face=' + targetFace).catch(console.log);
  } else {
    lockMotors(3000);
    showLiveFeedback(`🦾 Movimento: ${title}`);
    fetch('/cmd?pose=' + poseName).catch(console.log);
  }
}

function pose(name) { 
  execAction(name, name, name);
}

function faceBtn(name) {
  execAction(name, name, name);
}

function updateMotor(motorNum, value) {
  if (motorsLocked) return;
  document.getElementById('m' + motorNum + 'val').textContent = value + '\u00B0';
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?motor=' + motorNum + '&value=' + value).catch(console.log);
}

// Settings and Wifi Logic
function openSettings() {
  loadWifiStatus();
  fetch('/getSettings').then(r => r.json()).then(data => {
    document.getElementById('frameDelay').value = data.frameDelay || 100;
    document.getElementById('walkCycles').value = data.walkCycles || 10;
    document.getElementById('motorCurrentDelay').value = data.motorCurrentDelay || 20;
    document.getElementById('motorSpeed').value = data.motorSpeed || 'medium';
    
    const savedColor = localStorage.getItem('themeColor') || '#ff8c42';
    const colorSelect = document.getElementById('themeColor');
    const customColorInput = document.getElementById('customColor');
    
    let found = false;
    for (let opt of colorSelect.options) {
      if (opt.value === savedColor) {
        colorSelect.value = savedColor;
        found = true;
        break;
      }
    }
    if (!found) {
      colorSelect.value = 'custom';
      customColorInput.value = savedColor;
      customColorInput.style.display = 'block';
    } else {
      customColorInput.style.display = 'none';
    }
    document.getElementById('settingsPanel').style.display = 'block';
  }).catch(() => {
    document.getElementById('settingsPanel').style.display = 'block';
  });
}

function closeSettings() {
  document.getElementById('settingsPanel').style.display = 'none';
}

function onThemeSelectChange() {
  const colorSelect = document.getElementById('themeColor');
  const customColorInput = document.getElementById('customColor');
  if (colorSelect.value === 'custom') {
    customColorInput.style.display = 'block';
  } else {
    customColorInput.style.display = 'none';
    applyTheme(colorSelect.value);
  }
}

function saveSettings() {
  const frameDelay = document.getElementById('frameDelay').value;
  const walkCycles = document.getElementById('walkCycles').value;
  const motorCurrentDelay = document.getElementById('motorCurrentDelay').value;
  const motorSpeed = document.getElementById('motorSpeed').value;
  
  const colorSelect = document.getElementById('themeColor');
  const color = colorSelect.value === 'custom' ? document.getElementById('customColor').value : colorSelect.value;
  
  localStorage.setItem('themeColor', color);
  applyTheme(color);
  
  fetch('/setSettings', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: `frameDelay=${frameDelay}&walkCycles=${walkCycles}&motorCurrentDelay=${motorCurrentDelay}&motorSpeed=${motorSpeed}`
  }).then(() => {
    closeSettings();
    showLiveFeedback('Impostazioni salvate con successo!');
  }).catch(console.log);
}

function applyTheme(color) {
  const root = document.documentElement;
  root.style.setProperty('--content-color', color);
  const rgb = hexToRgb(color);
  if (rgb) {
    const dark = `rgb(${Math.max(0, rgb.r - 20)}, ${Math.max(0, rgb.g - 20)}, ${Math.max(0, rgb.b - 20)})`;
    const darker = `rgb(${Math.max(0, rgb.r - 40)}, ${Math.max(0, rgb.g - 40)}, ${Math.max(0, rgb.b - 40)})`;
    const glow = `rgba(${rgb.r}, ${rgb.g}, ${rgb.b}, 0.35)`;
    root.style.setProperty('--content-color-dark', dark);
    root.style.setProperty('--content-color-darker', darker);
    root.style.setProperty('--content-color-glow', glow);
  }
}

function loadTheme() {
  const savedColor = localStorage.getItem('themeColor');
  if (savedColor) applyTheme(savedColor);
}

function hexToRgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

function openMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'block';
}

function closeMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'none';
}

// MicroSD Manager
function openSdManager() {
  document.getElementById('sdManagerPanel').style.display = 'block';
  loadSdFiles();
}

function closeSdManager() {
  document.getElementById('sdManagerPanel').style.display = 'none';
}

function loadSdFiles() {
  const list = document.getElementById('sdFilesList');
  list.innerHTML = '<span style="color:#aaa">Caricamento elenco file...</span>';
  fetch('/api/sd/list').then(r => r.json()).then(data => {
    if (!data.ready) {
      list.innerHTML = '<span style="color:#ff6b6b">Scheda MicroSD non rilevata o non pronta!</span>';
      return;
    }
    if (!data.files || data.files.length === 0) {
      list.innerHTML = '<span style="color:#aaa">Nessun file presente nella cartella /faces</span>';
      return;
    }
    let html = '<table style="width:100%; border-collapse:collapse; font-size:12px;">';
    data.files.forEach(f => {
      let baseName = f.name.replace(/\.bin$/i, '').replace(/_\d+$/, '');
      html += `<tr style="border-bottom:1px solid #333;">
        <td style="color:#fff; padding:6px 2px;">${f.name}</td>
        <td style="text-align:right; padding:6px 2px; white-space:nowrap;">
          <button style="padding:4px 8px; font-size:11px; margin-right:4px;" title="Anteprima sul robot" onclick="faceBtn('${baseName}')">👁️</button>
          <button style="padding:4px 8px; font-size:11px; background:#ef4444;" title="Elimina file" onclick="deleteSdFile('${f.name}')">🗑️</button>
        </td>
      </tr>`;
    });
    html += '</table>';
    list.innerHTML = html;
  }).catch(err => {
    list.innerHTML = '<span style="color:#ff6b6b">Errore di comunicazione con il robot</span>';
  });
}

function uploadFaceFile() {
  const input = document.getElementById('faceFileInput');
  const status = document.getElementById('uploadStatus');
  if (!input.files || input.files.length === 0) {
    status.innerHTML = '<span style="color:#ff6b6b">Seleziona un file prima!</span>';
    return;
  }
  const file = input.files[0];
  const formData = new FormData();
  formData.append('file', file, file.name);
  status.innerHTML = '<span style="color:#ff8c42">Caricamento in corso...</span>';
  fetch('/api/sd/upload', {
    method: 'POST',
    body: formData
  }).then(r => r.json()).then(d => {
    status.innerHTML = '<span style="color:#2ecc71">Caricato con successo!</span>';
    input.value = '';
    loadSdFiles();
  }).catch(e => {
    status.innerHTML = '<span style="color:#ff6b6b">Errore durante il caricamento</span>';
  });
}

function deleteSdFile(fname) {
  if (!confirm('Vuoi eliminare ' + fname + ' dalla MicroSD?')) return;
  fetch('/api/sd/delete?file=' + encodeURIComponent(fname), { method: 'POST' })
    .then(r => r.json())
    .then(() => loadSdFiles())
    .catch(e => alert('Errore eliminazione file'));
}

// WiFi Configuration Logic
function toggleManualSsid() {
  const manual = document.getElementById('wifiManual').checked;
  document.getElementById('wifiSsidManual').style.display = manual ? 'block' : 'none';
  document.getElementById('wifiSsid').style.display = manual ? 'none' : 'block';
}

function loadWifiStatus() {
  fetch('/api/wifi/status').then(r => r.json()).then(d => {
    const el = document.getElementById('wifiStatus');
    if (d.connected) {
      el.innerHTML = `Connesso a: <b>${d.ssid}</b> (IP: ${d.ip})`;
    } else {
      el.textContent = 'Modalità AP attiva (non connesso a router WiFi).';
    }
  }).catch(console.log);
}

function scanWifi() {
  const sel = document.getElementById('wifiSsid');
  sel.innerHTML = '<option>Scansione in corso...</option>';
  pollWifiScan(0);
}

function pollWifiScan(attempt) {
  fetch('/api/wifi/scan').then(r => r.json()).then(data => {
    if (data.scanning) {
      if (attempt < 15) setTimeout(() => pollWifiScan(attempt + 1), 600);
      return;
    }
    const sel = document.getElementById('wifiSsid');
    sel.innerHTML = '';
    if (!data.length) {
      sel.innerHTML = '<option value="">Nessuna rete trovata</option>';
      return;
    }
    data.forEach(net => {
      const opt = document.createElement('option');
      opt.value = net.ssid;
      opt.textContent = `${net.ssid} (${net.rssi} dBm)${net.secure ? ' 🔒' : ''}`;
      sel.appendChild(opt);
    });
  }).catch(console.log);
}

function connectWifi() {
  const manual = document.getElementById('wifiManual').checked;
  const ssid = manual ? document.getElementById('wifiSsidManual').value : document.getElementById('wifiSsid').value;
  const pass = document.getElementById('wifiPass').value;
  const res = document.getElementById('wifiResult');
  
  if (!ssid) {
    res.textContent = 'Seleziona o scrivi un SSID prima!';
    return;
  }
  res.textContent = 'Connessione in corso...';
  
  fetch('/api/wifi/connect', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: `ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(pass)}`
  }).then(r => r.json()).then(d => {
    if (d.success) pollWifiConnect(0);
    else res.textContent = 'Errore: ' + (d.error || 'Impossibile avviare');
  }).catch(() => {
    pollWifiConnect(0);
  });
}

function pollWifiConnect(attempt) {
  const res = document.getElementById('wifiResult');
  fetch('/api/wifi/status').then(r => r.json()).then(d => {
    if (d.connected) {
      res.innerHTML = `<span style="color:#2ecc71">Connesso con successo! IP: ${d.ip}</span>`;
      loadWifiStatus();
      return;
    }
    if (d.connecting) {
      if (attempt < 25) setTimeout(() => pollWifiConnect(attempt + 1), 1000);
      else res.textContent = 'Tentativo in corso... Riapri impostazioni tra poco.';
      return;
    }
    res.textContent = 'Fallito: ' + (d.lastError || 'Impossibile connettersi');
  }).catch(() => {
    if (attempt < 25) setTimeout(() => pollWifiConnect(attempt + 1), 1000);
    else res.textContent = 'Connessione persa con il robot. Riconnettiti alla sua rete WiFi.';
  });
}

// Gamepad Management
let activeGamepadIndex = null;
let gamepadPollId = null;
let lastButtonStates = [];
let lastAxisDir = { x: 0, y: 0 };
const axisThreshold = 0.5;
const pollIntervalMs = 80;

const buttonBindings = {
  0: () => pose('stand'),   // A / Cross
  1: () => pose('wave'),    // B / Circle
  2: () => pose('dance'),   // X / Square
  3: () => pose('swim'),    // Y / Triangle
  4: () => pose('point'),   // LB / L1
  5: () => pose('pushup'),  // RB / R1
  6: () => pose('bow'),     // LT / L2
  7: () => pose('shake'),   // RT / R2
  8: () => stop(),          // Back / Share
  9: () => pose('rest'),    // Start / Options
  10: () => pose('cute'),   // L3
  11: () => pose('freaky'), // R3
  12: () => move('forward'),// D-pad up
  13: () => move('backward'),// D-pad down
  14: () => move('left'),   // D-pad left
  15: () => move('right'),  // D-pad right
  16: () => stop(),         // Home / PS
  17: () => pose('worm')    // Touchpad / extra
};

const buttonReleaseStop = new Set([12, 13, 14, 15]);

function updateGamepadStatus(connected) {
  const status = document.getElementById('gamepadStatus');
  if (!status) return;
  if (connected) {
    status.textContent = '🎮 Gamepad Connesso';
    status.classList.add('connected');
  } else {
    status.textContent = 'Gamepad disconnesso';
    status.classList.remove('connected');
  }
}

function handleButtonChange(index, pressed) {
  if (pressed) {
    const action = buttonBindings[index];
    if (action) action();
  } else if (buttonReleaseStop.has(index)) {
    stop();
  }
}

function getAxisDirection(x, y) {
  if (Math.abs(x) < axisThreshold && Math.abs(y) < axisThreshold) return { x: 0, y: 0 };
  if (Math.abs(x) > Math.abs(y)) return { x: x > 0 ? 1 : -1, y: 0 };
  return { x: 0, y: y > 0 ? 1 : -1 };
}

function applyAxisDirection(dir) {
  if (dir.x === 1) move('right');
  else if (dir.x === -1) move('left');
  else if (dir.y === 1) move('backward');
  else if (dir.y === -1) move('forward');
  else stop();
}

function pollGamepad() {
  const pads = navigator.getGamepads ? navigator.getGamepads() : [];
  const pad = pads && activeGamepadIndex !== null ? pads[activeGamepadIndex] : null;
  if (!pad) {
    updateGamepadStatus(false);
    return;
  }
  updateGamepadStatus(true);

  if (!lastButtonStates.length) {
    lastButtonStates = pad.buttons.map(b => !b.pressed);
  }
  pad.buttons.forEach((btn, i) => {
    const pressed = !btn.pressed;
    if (pressed !== lastButtonStates[i]) {
      handleButtonChange(i, pressed);
      lastButtonStates[i] = pressed;
    }
  });

  const x = pad.axes[0] || 0;
  const y = pad.axes[1] || 0;
  const dir = getAxisDirection(x, y);
  if (dir.x !== lastAxisDir.x || dir.y !== lastAxisDir.y) {
    applyAxisDirection(dir);
    lastAxisDir = dir;
  }
}

window.addEventListener('gamepadconnected', (e) => {
  activeGamepadIndex = e.gamepad.index;
  lastButtonStates = [];
  lastAxisDir = { x: 0, y: 0 };
  updateGamepadStatus(true);
  if (!gamepadPollId) gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
});

window.addEventListener('gamepaddisconnected', (e) => {
  if (activeGamepadIndex === e.gamepad.index) {
    activeGamepadIndex = null;
    lastButtonStates = [];
    lastAxisDir = { x: 0, y: 0 };
    updateGamepadStatus(false);
  }
});

if (navigator.getGamepads) {
  setInterval(() => {
    if (activeGamepadIndex !== null) return;
    const pads = navigator.getGamepads();
    if (!pads) return;
    for (let i = 0; i < pads.length; i++) {
      if (pads[i]) {
        activeGamepadIndex = pads[i].index;
        updateGamepadStatus(true);
        if (!gamepadPollId) gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
        break;
      }
    }
  }, 1000);
}
</script>
</body>
</html>
)rawliteral";
