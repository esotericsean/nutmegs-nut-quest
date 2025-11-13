# Nutmeg’s Nut Quest — Entity Reference

This document defines all enemies, hazards, collectibles, and boss components currently implemented in the game. 
It ensures consistency and prevents the AI from inventing or modifying entities that do not exist.

---

# PLAYER

## Nutmeg (Player)
- Behavior: run, jump, collect items, take damage
- Focus on responsiveness and smooth platforming
- Uses multiple sprite frames for running and jumping
- Collision: tilemap + entity collision

---

# FOREST WORLD ENTITIES

## Bunny
- Behavior: hops back and forth on the ground
- Movement: timed hop cycle; reverses when hitting a wall or edge
- Hurtbox: active
- Notes: simple 2–3 frame animation
- Common Bugs:
  - direction flip incorrectly triggered
  - hop timing drift

## Butterfly
- Behavior: gentle floating enemy with semi-random movement
- Movement: slow, drifting left/right/up/down
- Hurtbox: active
- Notes: small 2-frame flapping animation
- Common Bugs:
  - drifting into ceilings or walls
  - unpredictable movement if delta too high

## Bird (vertical flyer)
- Behavior: moves up → down → up in a repeating cycle
- Movement: fixed amplitude vertical movement
- Hurtbox: active
- Notes: flapping 2-frame animation

## Bat (vertical flyer, similar behavior)
- Behavior: same pattern as birds but usually found in darker/underground areas
- Movement: up/down patrol loop
- Hurtbox: active

## Rockith (Rock Monster)
- Behavior:
  1. **Rock form** – stationary, harmless
  2. **Awake form** – sprouts legs and walks left/right briefly
- Hurtbox:
  - inactive: safe
  - active: harmful
- Notes: has distinct rock frame + walking animation frames
- Common Bugs:
  - hurtbox active too early
  - switching between forms too quickly/erratically

---

# WATER WORLD ENTITIES

## Fish
- Behavior: jumps out of the water and back in on a fixed cycle
- Movement: jump arc controlled by timer
- Hurtbox:
  - active mid-air
  - inactive underwater
- Notes: simple 1–2 frame animation
- Common Bugs:
  - arc misalignment with tile boundaries

---

# UNDERGROUND / EARTH ENTITIES

## Earthworm
- Behavior: slow inching left and right (harmless)
- Hurtbox: none
- Purpose: environmental flavor / animation
- Notes: simple 2-frame animation

---

# WEATHER / HAZARDS

## Lightning
- States:
  1. **Warning** – blinking indicator  
  2. **Strike** – instant vertical beam (harmful)  
- Hurtbox: strike frame only
- Notes: appears in weather-themed levels
- Common Bugs:
  - desync between warning and strike
  - hurtbox lasting too long

## Spikes
- Behavior: static hazard
- Hurtbox: always active
- Notes: simple sprite or tile

---

# BOSS ENTITIES

## Picnic Table Boss
A multi-component boss with separate entity logic.

### Components:
- Table Body  
- Left Hand  
- Right Hand  
- Thrown projectiles (if implemented)

### Behavior:
- Hands throw or slam objects on timers
- Table serves as the main damage target
- Multiple possible phases

### Notes:
- Assembled from multiple sprite tiles
- Must stay within VRAM and OAM limits

---

# COLLECTIBLES

## Acorn
- Standard collectible
- Purpose: score/progression
- Single-frame sprite

## **Golden Acorn**
- Rare collectible
- Typically worth more / bonus item
- Requires distinct sprite/palette slot

## **1-Up**
- Grants extra life
- Usually floating or placed in a hidden location

## **Bow**
- Cosmetic item (Nutmeg wears it)
- Behavior:
  - Changes appearance only (no gameplay effects)
  - Persistent until level end or loss (depending on design)

---

# DECORATIVE ENTITIES
Non-colliding, purely visual:
- Leaves
- Flowers
- Environmental bugs
- Water splashes
- Dust puffs

Used only for visual flair. No AI or collision.

---

# PROHIBITED ENTITIES (Do NOT invent these)
The following should not be generated unless explicitly requested:
- mushrooms with faces  
- walking nuts  
- seedlings  
- leaf monsters  
- plant-people  
- log golems  
- any “living vegetation” enemies  
- any Pokémon-like or mascot-style creatures  

Sean prefers grounded forest animals, not fantasy plant creatures.

---

# AI / CURSOR Notes
- Match existing sprite counts and resource constraints.
- Never invent new frames, palettes, or behaviors without confirmation.
- Confirm tile counts before suggesting new animations.
- Provide minimal diffs for any modifications to entity logic.

