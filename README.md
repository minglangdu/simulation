# WIP NPC Project

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/minglangdu/Simulation)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/minglangdu/Simulation)
![GitHub contributors](https://img.shields.io/github/contributors/minglangdu/Simulation)
![GitHub Repo stars](https://img.shields.io/github/stars/minglangdu/Simulation)
![GitHub forks](https://img.shields.io/github/forks/minglangdu/Simulation)

Partly inspired by one of my favorit games, Dwarf Fortress.

Had a cool idea about how to simulate people and had nothing else to do lol.
Basic system I envisioned in case I forget:

- **Motivations** are changed, *not* added when specific stimuli occur; they always exist so that there are almost always actions the npc wants to do. Motivations are *extremely* rarely negative, so the minimum is mostly 0 for many.
- **Actions** are taken from a global list of possible actions for a particular "species" of npc. Specific actions are chosen by motivations; a motivation value increases likelihood of a new group of possible actions. Actions are chosen at random, with a weighting by motivations.
- **Mood** is used to determine how much the character wants to do things. Normally, characters will only do actions which have a total motivation higher than the base willingness to do things (due to personality) minus the mood.
- **Jobs** are implemented in case you want the player to indirectly influence them. Jobs are a subgroup of motivations.
- **Personality** is changed throughout the character's life, and influences decision making in varioius ways. 

## Files

Again, in case I forget.

- **map.h** basically handles all the spatial functions so that
- **ai.h** can focus on the system above and the two are used together in
- **main.cpp** which is self-explanatory.
