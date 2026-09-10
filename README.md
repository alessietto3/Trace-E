# The Sesame Robot Project 
___
![License](https://img.shields.io/badge/License-APACHE2.0-yellow)
![Microcontroller](https://img.shields.io/badge/Microcontroller-ESP32-blue)
![Firmware](https://img.shields.io/badge/Firmware-C%2B%2B-blue?logo=c%2B%2B)
![IDE](https://img.shields.io/badge/IDE-Arduino-00979D?logo=arduino&logoColor=white)
![GitHub stars](https://img.shields.io/github/stars/dorianborian/sesame-robot?style=social)
![GitHub forks](https://img.shields.io/github/forks/dorianborian/sesame-robot?style=social)

<img width="100%" height="728" alt="sesame-cover" src="https://github.com/user-attachments/assets/f0cc6ad0-135b-4515-8750-900f224ed7ae" />

<p align="center">
  <a href="https://www.youtube.com/watch?v=NIgoQVQF_Ng">
    <img src="https://github.com/user-attachments/assets/1663e022-0680-4053-97b4-53e669a6f07d" width="49%" alt="tutorial-button">
  </a>
  <a href="https://discord.gg/XDXkhQd8bC">
    <img src="https://github.com/user-attachments/assets/378fcb48-5b12-4b46-9dcb-452432d49913" width="49%" alt="discord-button">
  </a>
</p>

___

**Greetings, from your new best friend.**

Sesame is an accessible Open-Source robotics project based on the ESP32 microcontroller system, with an emphasis on expression and movement. 
This project is designed for makers and engineers of all skill levels! Sesame offers a dynamic platform designed to start working with walking robots. 
To build a sesame robot, you will need basic soldering skills, $50-60 in hardware components, access to a 3D printer, and a basic understanding of Arduino IDE.

This repository contains the CAD design files, STL files, build and wiring guides, and the base/expanded firmware for the ESP32-based controller. 
There is also some included debugging firmware that may be helpful in getting your Sesame up and running.

## Features

*   **Quadruped Design:** Uses 8 servo motors (2 per leg) to achieve roughly 8 total degrees of freedom.
*   **Emotive Display:** Features a 128x64 OLED screen acting as a reactive face that syncs with movement.
*   **Fully Printable:** Designed entirely for 3D printing in PLA with minimal supports.
*   **Network Connectivity:** Connect to your WiFi network for remote control and API access.
*   **JSON API:** RESTful API for programmatic control from Python, JavaScript, and more.
*   **Conversational Faces:** Expressive emotion library with talk variants for voice assistant projects.
*   **Sesame Studio:** New animation composer software to easily create custom movements.
*   **Sesame Companion App:** Python application for voice control and advanced interactions.
*   **Serial CLI:** Control the robot and trigger animations via a Serial Command Line Interface or the web UI.
*   **Pre-programmed Emotes:** Includes animations for Walking, Waving, Dancing, Pointing, Resting, and more.


## Watch the launch video on YouTube

<a href="https://www.youtube.com/watch?v=1UDsWkcQZhc"><img src="https://github.com/user-attachments/assets/710cb5a6-163e-47e7-a294-5e2d2ab07627" width="70%" alt="thumb-youtube"></a>

___

## Getting Started

Follow these steps to build your own Sesame Robot:

### 1. Gather Parts 
Check the **[Bill of Materials (BOM)](hardware/bom/README.md)** for a complete list of required electronics and hardware.
*   Microcontroller: Lolin S2 Mini (recommended for DIY builds), Sesame Distro Board V3 (Current, pre-flashed, supports Bambu Lab battery), V2 (legacy, USB-only), or ESP32-DevKitC-32E with Distro Board V1 (legacy)
*   Actuators: 8x 180 Degree MG90 Servos
*   Power: 5V 3A source (USB-C PD for S2 Mini and V2 Distro Board, or battery + buck converter; see BOM for the Bambu Lab 14500 7.4V 800mAh Li-ion Battery option)

### 2. Print Parts 
Download the STLs and follow the **[Printing Guide](hardware/printing/README.md)**.
*   Designed for PLA
*   Minimal supports required

### 3. Build & Wire 
Follow the **[Build Guide](docs/build-guide/README.md)** and **[Wiring Guide](docs/wiring-guide/README.md)** to assemble the frame and connect the electronics.

### 4. Flash Firmware 
Upload the code from the **[Firmware Directory](firmware/README.md)**.
*   Requires Arduino IDE
*   Configure WiFi AP settings

### 5. Create Animations 
Use **[Sesame Studio](software/sesame-studio/README.md)** to visually design poses and sequences for your robot.

<img width="100%" height="728" alt="sesame-wakeup-gif" src="https://github.com/user-attachments/assets/a4951195-4253-40a4-a87d-d14fad57ff5f" />

---

## Software & Firmware

### Sesame Studio
Sesame Studio is a standalone desktop application included in `software/sesame-studio/`. It allows you to:
*   Visually pose the robot using a schematic interface.
*   Generate C++ code for servo angles automatically.
*   Sequence frames into complex animations.

[**> Go to Sesame Studio**](software/sesame-studio/README.md)


### Sesame Simulator
The Sesame Simulator, created by Jay Li, is a Rust-based 3D simulation environment for testing Sesame's movements and kinematics in a virtual space. It features:
*   **Physics-based Simulation:** Test walking and balance without hardware.
*   **Web-based Interface:** Run the simulator directly in your browser.
*   **URDF Integration:** Accurate modeling of Sesame's physical properties.

[**> Go to Sesame Simulator**](https://one-for-all.github.io/sesame-robot-sim/)

### Sesame Companion App
The Sesame Companion App is a Python-based application that enables advanced control and interaction with your robot over your local network. It leverages the new JSON API and network mode features to provide:
*   **Voice Assistant Integration:** Control Sesame with voice commands and see real-time emotional expressions.
*   **Remote Control:** Command your robot from anywhere on your local network.
*   **Face Control:** Change expressions dynamically based on conversation or context.
*   **API Examples:** Reference implementation for building your own integrations.

The Companion App works with robots running the latest firmware with network mode enabled.

[**> Go to Sesame Companion App Repository**](https://github.com/dorianborian/sesame-companion-app)

### Firmware
The ESP32 firmware (`sesame-firmware-main.ino`) handles the kinematics, face display, and WiFi control interface.
*   **Web UI:** Control the robot from your phone via the built-in Access Point.
*   **Custom Faces:** Add your own bitmaps (guide in firmware docs).

[**> Go to Firmware Docs**](firmware/README.md)


---

## Robot Eyes & Expression Library (TFT 160x128 Landscape)

Trace-E features an expressive robotic eye system designed for 128x160 color TFT displays (ST7735) in Landscape orientation (**160x128 pixels**), as well as backwards compatibility with 128x64 monochrome OLEDs.

The eyes are styled after modern interactive companion robots (*Cozmo*, *Vector*, *Wall-E*), with large luminous capsule eyes, organic eyelid curves, and dynamic emotion-based color rendering:

### Moods & Emotional Expressions

| Face Name | Mood / Meaning | TFT Eye Color | Visual Description |
|-----------|----------------|---------------|--------------------|
| `idle` / `defualt` | Neutral / Normal | **Cyan** (`ST7735_CYAN`) | Friendly, attentive large rounded capsules (standard robot eyes) |
| `idle_blink` | Eye Blink (4-frame anim) | **Cyan** (`ST7735_CYAN`) | Natural blinking animation (open → upper lid lower → slit → re-open) |
| `happy` | Happy / Cheerful | **Cyan** (`ST7735_CYAN`) | Wide smiling upward arches (`^_^`) with raised cheeks |
| `angry` | Angry / Stern | **Red** (`ST7735_RED`) | Sharp inward slanted brows (`\ /`) with intense focused glare |
| `sad` | Sad / Apologetic | **Cyan** (`ST7735_CYAN`) | Downward drooping upper eyelids (`/ \`) with sorrowful look |
| `surprised` | Surprised / Shocked | **Cyan** (`ST7735_CYAN`) | Giant tall rounded pill eyes (`O O`) with wide open circular pupils |
| `sleepy` | Sleepy / Drowsy | **Blue** (`ST7735_BLUE`) | Heavy droopy eyelids covering 70% of the eyes |
| `love` | In Love / Heart-eyes | **Magenta** (`ST7735_MAGENTA`) | Glowing symmetrical digital hearts (`<3 <3`) |
| `excited` | Excited / Thrilled | **Yellow** (`ST7735_YELLOW`) | Wide open joyful eyes with sparkling 8-point stars inside |
| `confused` | Confused / Skeptical | **Cyan** (`ST7735_CYAN`) | Asymmetrical "Huh?" (left eye tall & arched, right eye squinted flat `o _`) |
| `thinking` / `thinking_2` | Thinking / Pondering | **Cyan** (`ST7735_CYAN`) | Eyes glancing up and to the top-right corner |
| `cute` | Kawaii / Adorable | **Magenta** (`ST7735_MAGENTA`) | Anime eyes with double circular shine glints and blush marks below |
| `dead` / `dead_1` / `dead_2` | Knocked Out / Off | **Red** (`ST7735_RED`) | Bold `X X` crossed eyes, glitch frames, and flatline dashes (`- -`) |
| `freaky` | Hypnotic / Dizzy | **Cyan** (`ST7735_CYAN`) | Concentric circular hypnotic rings (`@ @`) |
| `stand` | Alert / Standing | **Cyan** (`ST7735_CYAN`) | Upright, slightly taller alert capsule eyes |

### Action & Movement Faces

Synchronized with movement sequences and poses:

| Face Name | Movement / Pose | TFT Eye Color | Description |
|-----------|-----------------|---------------|-------------|
| `walk` | Walking Forward | **Cyan** (`ST7735_CYAN`) | Focused forward gaze with slight motion slant |
| `rest` / `rest_1` / `rest_2` | Sleeping / Resting | **Blue** (`ST7735_BLUE`) | Peaceful downward curved closed eyes (`u u`) with floating `z Z` |
| `wave` | Waving / Greeting | **Cyan** (`ST7735_CYAN`) | Left happy arch eye paired with a winking sparkle star eye |
| `dance` / `dance_1` | Dancing / Grooving | **Cyan** (`ST7735_CYAN`) | Alternating playful winking arches to the rhythm of the music |
| `swim` | Swimming Pose | **Cyan** (`ST7735_CYAN`) | Hydrodynamic curved visor with bridge connection |
| `point` / `point_1` / `point_2` | Pointing / Tracking | **Cyan** (`ST7735_CYAN`) | Eyes shifting sharply to the right following pointed direction |
| `pushup` | Pushup Exercise | **Cyan** (`ST7735_CYAN`) | Tightly squinted grit eyes (`> <`) under heavy effort |
| `bow` | Polite Bow | **Cyan** (`ST7735_CYAN`) | Downward angled respectful closed curves (`v v`) |
| `shake` | Body Shake | **Cyan** (`ST7735_CYAN`) | Jittered offset eyes with vibration speed lines |
| `worm` | Worm Motion | **Cyan** (`ST7735_CYAN`) | Playful wavy undulating sine-curve eyes |
| `crab` | Crab Walk | **Cyan** (`ST7735_CYAN`) | Sideways peeking eyes looking hard toward the flank |
| `shrug` | Shrugging | **Cyan** (`ST7735_CYAN`) | Skeptical side-glance with raised eyebrow and smirk |

### Conversational / Talk Variants

Each core emotion includes an animated speech counterpart (`talk_happy`, `talk_angry`, `talk_sad`, `talk_surprised`, `talk_sleepy`, `talk_love`, `talk_excited`, `talk_confused`, `talk_thinking`). In the Web Interface, toggling **Talk Mode** automatically triggers speech-animated eye variants!

---

## Contributing

This robot is a platform for building new features, cosmetics, tools, and ideas. Since the current firmware is a basic implementation, pull requests are very welcome for:
*   Kinematics improvements
*   New animations
*   Improved Web UI/UX
*   Sensor integration (Ultrasonic, Gyro, etc.)

I would also love to see forks of this project with new hardware, software, faces, etc. Be sure to send me a message if you end up building one, and I might feature you on my website or channel!
  
---

*Created by [Dorian Todd](https://www.doriantodd.com/). Need help with your Sesame Robot? Send me a message on Discord, my username is "starphee"*
