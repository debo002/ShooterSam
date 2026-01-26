# ShooterSam

> **Educational Project Only** - A third-person shooter demo built with Unreal Engine 5.7 C++ for learning purposes.

## Overview

A simple single-player third-person shooter demonstrating UE5 C++ fundamentals:
- Third-person character movement and shooting
- AI enemies with Behavior Trees
- Health system with animated UI
- Auto-restart on win/lose

## Features

- ✅ Third-person character controller
- ✅ AI with line-of-sight detection
- ✅ Weapon system with VFX
- ✅ Health bar with smooth animation
- ✅ Win/lose conditions

## Requirements

- Unreal Engine 5.7
- Visual Studio 2022
- Windows PC

## Setup

1. Clone the repository
2. Right-click `ShooterSam.uproject` → Generate Visual Studio project files
3. Open solution and build
4. Launch in Unreal Editor
5. Set **Map To Restart** = `Map1` in GameMode Blueprint

## Controls

- **WASD** - Move
- **Mouse** - Look
- **Space** - Jump
- **Left Click** - Shoot

## Project Structure

```
Source/ShooterSam/          # C++ code
├── ShooterSamCharacter.*   # Player/AI character
├── ShooterAI.*             # AI controller
├── Gun.*                   # Weapon system
├── ShooterSamGameMode.*    # Game rules
└── BT*.*                   # Behavior tree nodes
```

## Learning Resources

See documentation in project root:
- `PRODUCTION_AUDIT_COMPLETE.md` - Code quality review
- `FEATURE_SETUP_GUIDE.md` - Feature configuration
- `BUG_FIX_PLAYER_DEATH.md` - Technical deep dive

## License

Educational use only. Not for commercial purposes.

---

**Learning Project by debo002**
