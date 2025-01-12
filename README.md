# WIP NPC Project

Partly inspired by one of my favorit games, Dwarf Fortress.

Had a cool idea about how to simulate people and had nothing else to do lol.
Basic system I envisioned in case I forget:

- **Motivations** are changed, *not* added when specific stimuli occur; they always exist so that there are always actions the npc wants to do. Motivations are *extremely* rarely negative, so the minimum is mostly 0 for many.
- **Actions** are taken from a global list of possible actions for a particular "species" of npc. Specific actions are chosen by motivations; a non-negative motivation value introduces a new group of possible actions. Actions are chosen at random, with a weighting by motivations.
- **Mood** is self-explanatory.
- **Jobs** are implemented in case you want the player to indirectly influence them. Jobs are a subgroup of motivations, and have higher weights based on mood.

## Files

Again, in case I forget.

- **map.h** basically handles all the spatial functions so that
- **ai.h** can focus on the system above and the two are used together in
- **main.cpp** which is self-explanatory.
