# Fluffy Robot Pet

## Student Information

- **Student Name:** Sama Rizk El-Saeed Azzam
- **Email:** [samaazzam33@gmail.com](mailto:samaazzam33@gmail.com)

## Project Description

Fluffy Robot Pet is a console-based virtual pet game written in standard C. The user takes care of a pet named Fluffy by monitoring and changing its food, fun, energy, and mood states.

The project demonstrates:

- Structures for storing the pet data.
- `uint8_t` and `uint16_t` types for compact state storage.
- Bit manipulation to represent mood flags such as asleep, hungry, sad, and sick.
- Functions for feeding, playing, sleeping, passing time, and displaying a pet report.
- Input validation for menu choices and the pet name.
- ASCII-art output and text-based status bars.

## Features

- Hatch the pet with a custom name.
- Draw Fluffy's face according to its current mood.
- Feed Fluffy to increase its food level.
- Play with Fluffy to increase fun and reduce energy.
- Put Fluffy to sleep or wake it up.
- Pass one hour and update the pet's needs automatically.
- View a care card containing the current status and next need.

## Requirements

- A C99-compatible compiler
- Standard C library
- Windows, Linux, or macOS terminal

## Build and Run

Using GCC:

```bash
gcc -std=c99 -Wall -Wextra -o fluffy main.c
./fluffy
```

On Windows, run:

```text
fluffy.exe
```

## How to Use

1. Enter Fluffy's name when the program starts.
2. Select an option from the menu.
3. Keep Fluffy's food, fun, and energy levels above the warning level.
4. Use the pet report to check Fluffy's mood and recommended next action.
5. Select `0` to exit the program.

## Project Files

- `main.c`: Source code for the virtual pet game.
- `Five_C_Practice_Projects.md`: Practice project descriptions and requirements.
- `screanshots/`: Project screenshots.
