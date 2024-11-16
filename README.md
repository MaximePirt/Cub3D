# Cube3D for 42

> :warning: **Project has not been tested yet.** :warning:

## What is it?

Cube3D is a 42 project that aims to create a simple 3D rendering program using the minilibx library. The program reads a map file that defines a landscape and renders it in a 3D perspective.

## Dependencies

The Cube3D program requires the following dependencies:

- libx11-dev
- libxext-dev
- libbsd-dev

### On Debian/Ubuntu

```bash
sudo apt-get update
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

## Usage

To use the Cube3D program, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/MaximePirt/Cub3D.git
   ```

2. Navigate to the project directory:
   ```bash
   cd Cub3D
   ```

3. Build the executable:
   ```bash
   make
   ```

4. Run the program with a provided map file:
   ```bash
   ./cube3d maps/lvl_1.cub
   ```

## Map Files

The map files define the landscape that will be rendered by the program. The map files must have the `.cub` extension and follow the following format:

:warning: **Note: This project is currently under development and has not been thoroughly tested. Use at your own risk.** :warning: