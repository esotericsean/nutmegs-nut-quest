# Nutmeg’s Nut Quest — Project Context

## Overview
Nutmeg’s Nut Quest is a Game Boy Color platformer written in **C** using **GBDK-2020** with the **ZGB engine** and **CBT-FX** for sound. 
The protagonist is **Nutmeg**, a squirrel collecting acorns for her babies. 
The game is inspired by Kirby’s Adventure, Super Mario Bros. 3, and Super Mario World.

Core gameplay:
- lightweight, responsive platforming
- small enemies with simple patterns
- multi-world structure
- boss fights
- collectible acorns

The game runs on real GBC hardware and must maintain GBC limitations.

---

## Target Platform Constraints
- Runs on Game Boy Color (160×144 resolution)
- Limited CPU, RAM, VRAM
- 8×8 sprites, 8×16 option if needed
- Max 10 sprites per scanline
- 4-color sprite palettes
- 8 hardware sprite palettes total
- Tile-based backgrounds
- Banked code and data
- All code must be interrupt-safe and hardware-stable

---

## Engines / Tools
### **GBDK-2020**
Used for:
- main program flow (main.c)
- hardware interaction
- VRAM and sprite memory management
- input, timing, etc.

### **ZGB Engine**
Handles:
- states (e.g., STATE_GAME, STATE_MENU)
- entities, update loops
- sprite sets
- collisions
- animations

Typical file structure:
- **src/** source code
- **res/** assets
- **banks/** banked code/data
- **build/** output ROM and object files

ZGB requires registering:
- states in `ZGBMain.c`
- sprites in `ZGBMain.c`
- entities in each world folder

### **CBT-FX**
- FX-Hammer creates `.sav` with sound effect data.
- Sound effects exported using hammer2cbt.py.
- SFX referenced by ID in code (e.g., SFX_JUMP).
- Avoid overlapping long SFX to conserve CPU time.

---

## Project Structure

### **States**
- `STATE_GAME`: main gameplay
- `STATE_MENU`: title / intro
- `STATE_PAUSE`
- `STATE_BOSS`
(You can expand this list as needed.)

### **Worlds / Levels**
Currently includes:
- Forest-themed areas
- Water sections
- Picnic table boss level
- i.e., world folders under `src/stages/`

### **Entities**
Current enemies and behaviors:

**Forest**
- Bunny: hops back and forth
- Butterfly: floats randomly
- Bird / Bat: flies upward then descends
- Rockith: stationary rock that occasionally grows legs and walks
- Snail / Beetle: simple left-right patrol
- Caterpillar: inching movement

**Water**
- Fish: jumps in/out on a timer

**Weather hazards**
- Lightning: strikes with warning

**Bosses**
- Picnic Table Boss with hands that throw objects

**Non-enemy**
- Earthworm: inching, harmless in some levels
- Spikes: ceiling hazard

**Player**
- Nutmeg: move, jump, collect acorns

---

## Style & Rules for AI Code Editing
Use these rules in all code suggestions:

1. **Never rewrite entire files unless explicitly asked.**
2. Prefer **minimal diffs**. Focus on the smallest safe change.
3. Avoid inventing nonexistent ZGB APIs. Use only documented functions.
4. Keep compatibility with real GBC hardware and ZGB constraints.
5. Keep functions small and avoid unnecessary allocations.
6. Respect existing naming patterns (CamelCase for entities, uppercase for constants).
7. Maintain correct bank attribution using `BANKED`.
8. For SFX: use existing IDs; do not create new SFX unless asked.
9. For animations: modify only frames or speeds unless major redesign requested.
10. When debugging: provide multiple hypotheses, verification steps, and minimal-code patches.

---

## Build Process
Standard:
make clean
make
Or the project-specific build script if present.
We currently use build_Color_CBTFX.bat to build/link the project and create the .gbc file

Outputs:
- `.gbc` ROM
- `.lst`, `.sym`, `.map` for debugging

---

## Common Pitfalls (AI, avoid these)
- **Do not** suggest dynamic memory allocation: GBDK doesn’t support it safely.
- **Do not** propose modifying engine internals (ZGBCore files) unless explicitly asked.
- **Do not** suggest large arrays or large stack variables.
- **Do not** use recursion.
- **Do not** create more sprites than VRAM allows.
- **Do not** use floats; use fixed-point or integers.
- **Do not** assume 60fps; use VBlank timing.

---

## Debugging Notes
Frequent issues:
- Incorrect bank declarations
- Overflowing sprite limits
- Wrong sprite tile indexing
- Entity update order issues
- Timing issues based on hardware cycles
- Off-by-one tile collisions
- SFX cutting each other off due to limited channels

When debugging, always ask for:
- console logs (if using debug prints)
- error output from make
- snippets from ZGBMain
- entity registration code

---

## High-Level Goals
- Smooth, cute, responsive platforming
- Hardware-accurate GBC performance
- Fun enemy variety
- Charming visuals
- Smooth boss fights
- Stable build with no VRAM corruption or flicker