# Nutmeg’s Nut Quest — AI Coding Rules

These rules apply to ALL AI-generated code, suggestions, explanations, diffs, refactors, and debugging steps.

The goal: 
Maintain hardware accuracy, avoid hallucinations, keep risk low, and ensure small, safe, incremental improvements.

---

## 1. General Behavior Rules
1. Never rewrite entire files unless explicitly instructed.
2. Always propose **minimal diffs** that solve the immediate issue.
3. If unsure, provide multiple hypotheses and verification steps.
4. Never make assumptions about code or assets that do not exist.
5. Ask for missing files or lines before guessing.
6. Maintain compatibility with **real Game Boy Color hardware**.
7. Never suggest APIs, functions, macros, or constants that are not already present in the repo or ZGB/GBDK docs.
8. For any change affecting multiple files, explain all dependencies clearly.

---

## 2. ZGB Engine Rules
1. Do not modify ZGB engine internals (`ZGBMain.c`, engine cores, engine macros) unless explicitly asked.
2. Do not introduce new engine systems (physics rewrites, new collision systems, custom managers) without request.
3. Always register:
   - states in `ZGBMain.c`
   - sprites in `ZGBMain.c`
   - entities in their correct world folders
4. Maintain expected ZGB entity lifecycle functions:
   - `START()`
   - `UPDATE()`
   - `DESTROY()`

5. Avoid:
   - large structs
   - complex nested loops in `UPDATE()`
   - expensive per-frame operations

---

## 3. GBDK / Hardware Rules
1. Never use:
   - recursion  
   - floating-point math  
   - dynamic memory (`malloc`, etc.)  
   - large local arrays  
   - large stack-allocated buffers  

2. Use integer math or fixed-point for any calculations.
3. Respect VRAM limits and OAM sprite limits:
   - max 10 sprites per scanline
4. Always respect hardware palettes and tile assumptions.
5. Do not modify interrupt handlers or timing unless instructed.

---

## 4. Banking Rules
1. Always mark banked functions with `BANKED`.
2. Never move functions between banks unless the request is explicit.
3. Keep data in the correct bank files.
4. Never exceed a bank’s size (AI must warn if a change risks this).

---

## 5. Sprite / Tile / Animation Rules
1. Do not exceed sprite or tile memory available for a given entity.
2. Never assume more frames or tiles exist; always confirm with resources in `res/`.
3. For animations:
   - modify only frame indices or speed unless explicitly asked for overhaul
4. For new sprites:
   - require confirmation of tile count, palette, and memory constraints

---

## 6. SFX Rules (CBT-FX)
1. Do not invent new SFX IDs.
2. Do not reference SFX indices that don’t exist in the generated CBT files.
3. Keep sound effects short and avoid overlapping long SFX in code.
4. For exports: only use IDs Sean provides unless he requests new ones.

---

## 7. Programming Style Rules
1. Match existing naming conventions:
   - Entities: `EntityName`
   - Constants/macros: `SFX_JUMP`, `SPR_BUNNY`
   - Functions: `FunctionName`
   - Snake case is not used.

2. Keep functions small and readable.
3. Don’t introduce global variables unless absolutely necessary.
4. Prefer modifying existing patterns rather than inventing new systems.

---

## 8. Debugging Rules
When diagnosing errors:
1. Provide at least **3 hypotheses**, ranked by likelihood.
2. Provide supporting reasoning for each hypothesis.
3. Provide verification steps for Sean to confirm or eliminate each one.
4. Provide the least invasive patch first.
5. Never claim certainty without evidence from the code.

---

## 9. Safety Rules
1. Avoid any changes that could cause VRAM corruption, OAM overflow, or bank overflows.
2. Avoid changes that increase CPU load significantly (since GBC is limited).
3. Warn if a suggested change may impact performance or sprite count.
4. Ensure code always compiles in real GBDK builds, not just hypothetically.

---

## 10. Multi-File / Refactor Rules
1. If a change affects multiple files:
   - explain the chain of effects
   - ensure imports and banks remain correct
   - ensure ZGB registration remains valid
2. Never reorganize directory structure unless explicitly asked.
3. Never rename files or entities unless the user requests it.

---

## 11. Behavior With Cursor Agents
1. Always prefer precise, minimal diffs.
2. Always check for references across the repo before suggesting changes.
3. Avoid mass-refactors.
4. Use `diff` or patch-style output only when requested.
5. Ask BEFORE applying changes that could break other subsystems.

---

# Final Principle
**When in doubt: stop, ask clarifying questions, and avoid risk.**

