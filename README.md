# Professional Game Development in C++ and Unreal Engine Course
![UnrealEngineCourse](https://github.com/user-attachments/assets/d63d09a9-f388-4084-a21c-dde1dfbc5562)

This project is a third-person action / RPG-style prototype built in Unreal Engine using a fully custom C++ gameplay framework (with minimal Blueprint integration), following the structure and lessons of Tom Looman’s Professional Game Development in C++ and Unreal Engine course (https://courses.tomlooman.com/p/unrealengine-cpp). The goal of this project was to demonstrate a robust, production-quality codebase all built with clean architecture, engine-level understanding and performance awareness.

This prototype showcases core systems like character control, abilities, AI, multiplayer support, UI, state saving, and modular gameplay components; all implemented in C++ and ready for extension by designers or other programmers.

## Features

### Modular C++ Gameplay Framework
- A custom framework built from the ground up using Unreal’s class hierarchy (Actors, Pawns, GameMode, Components) rather than relying solely on built-in templates.
- Properties exposed via Unreal’s reflection system (UPROPERTY / UFUNCTION), making components easy to configure via editor.
- Designed for easy extension: ability to add new items, abilities, mechanics, without rewriting core code.
### Player Character & Abilities
- Basic third-person controls (movement, rotation, camera) and combat mechanics, including projectile attacks. 
- Custom “Action / Ability System” from scratch (inspired by standard ability-system design), including actions like sprinting, attacking, using abilities, and attribute-based effects. 
- Attribute system (health, stamina, ...) and UI integration to reflect it (health bar, dynamic feedback on damage/pickups).
### UI & Feedback
- Responsive UIs using Unreal’s UMG system for HUD (health, status), crosshair, feedback on hits/abilities, and in-game menus. 
- Event-based UI updates to reflect gameplay events (health changes, ability cooldowns). 
### Visual & Audio Effects
- Dynamic materials/shader effects controlled via C++: hit flashes, dissolve effects, material parameter modulation for feedback.
- Integration of sound cues for actions (attacks, ability usage, UI events) to improve feedback and immersion.
- Simple animation system / Animation Blueprints for character movement, attacks, death/fall-back, and clean transitions.
### Enemy AI & Behavior System
- Basic AI bots using Unreal’s built-in AI systems: Behavior Trees, Blackboard, environment queries (EQS), custom C++ tasks/services to build behaviors (patrolling, chasing, attacking).
- Damage reactions, hit feedback, and simple ragdoll / physics impulses on death or knockback, integrating AI, physics, and gameplay.
### Multiplayer & Networking Support
- Client-server model implementation: attributes, abilities, world interactions, UI, and state replicate properly across clients ensuring consistent experience in multiplayer sessions.
- Applied best practices for network replication, authority management (server vs client), and optimized for low-bandwidth / efficient replication.
### Persistence & World State
- Save/load system to serialize player progression and world state, using Unreal’s SaveGame system (slots, player state, persistent world data), allowing sessions to be resumed. 
- Soft references & asynchronous asset loading via Unreal’s Asset Manager, supporting dynamic loading/unloading of content, which helps with performance and memory management.
### Debugging & Performance Awareness
- Use of debugging tools (breakpoints, logging, debug-draw shapes, assertions) for both C++ and Blueprint workflows, to test and ensure code correctness, especially for collision, gameplay, replication, and AI logic. 
- Performance profiling: using Unreal’s profiling tools to monitor FPS, memory usage, loading times, to identify bottlenecks, optimize content and ensure stable performance.
