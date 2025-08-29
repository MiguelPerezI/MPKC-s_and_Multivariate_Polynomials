# Polynomial Fields Visualizer

This OpenGL-based polynomial visualizer demonstrates operations on polynomial fields Zp and renders various mathematical structures including fractal curves and polynomial rings.

## Building and Running

The application is built using C with OpenGL/GLUT. To run the executable:

```bash
./polynomial_visualizer
```

## Key Controls

The application provides interactive controls for manipulating polynomial operations and visualization:

### Polynomial Ring Operations

- **`a`** - Addition with polynomial (1,0): Adds the polynomial p(x) = 1 + 0x to the current ring element
- **`s`** - Addition with polynomial (0,1): Adds the polynomial q(x) = 0 + 1x to the current ring element
- **`A`** (Shift+a) - Subtraction with polynomial (1,0): Subtracts the polynomial p(x) = 1 + 0x from the current ring element  
- **`S`** (Shift+s) - Subtraction with polynomial (0,1): Subtracts the polynomial q(x) = 0 + 1x from the current ring element
- **`d`** - Multiplication with polynomial (1,1): Multiplies the current ring element by the polynomial pp(x) = 1 + 1x

### Visualization Controls

- **`r`** - Increase rotation speed: Increases the automatic rotation speed of the 3D visualization
- **`R`** (Shift+r) - Decrease rotation speed: Decreases the automatic rotation speed of the 3D visualization
- **`i`** - Increase fractal iterations: Increases the iteration count for fractal rendering by 3
- **`I`** (Shift+i) - Decrease fractal iterations: Decreases the iteration count for fractal rendering by 1
- **`c`** - Change color scheme: Cycles through different color schemes for the visualization
- **`w`** - Advance animation cycle: Manually advances the animation cycle counter
- **`n`** - Advance secondary cycle: Advances the secondary animation cycle counter

## Mathematical Operations

The visualizer operates on polynomial rings Zp where:
- **Ring Structure**: Z11 (integers modulo 11) with 2-dimensional polynomial space
- **Base Polynomials**: 
  - p(x) = 1 + 0x (constant polynomial 1)
  - q(x) = 0 + 1x (linear polynomial x)  
  - pp(x) = 1 + 1x (polynomial 1 + x)

### Visual Representation

The polynomial ring operations are visualized as:
- **3D Lattice Points**: Each element in the ring is represented as a point in 3D space
- **Dynamic Updates**: Operations transform the lattice structure in real-time
- **Color Coding**: Different polynomial operations are distinguished by color changes
- **Fractal Overlay**: Dragon curve fractal is rendered simultaneously to demonstrate mathematical beauty

### Console Output

Each operation prints to the console:
- **Addition**: `+ -->(1, 0)` or `+ -->(0, 1)` followed by the updated ring structure
- **Subtraction**: `- -->(1, 0)` or `- -->(0, 1)` followed by the updated ring structure  
- **Multiplication**: `* -->(1, 1)` followed by the updated ring structure

## Technical Details

The application demonstrates:
- **OpenGL Rendering**: Real-time 3D graphics with lighting and depth buffering
- **Mathematical Visualization**: Abstract algebra concepts made visual through geometric representation
- **Interactive Mathematics**: Direct manipulation of polynomial ring elements through keyboard input
- **Fractal Mathematics**: Dragon curve generation using L-system turtle graphics
- **Modular Arithmetic**: All operations performed in finite fields Zp

The visualization provides an intuitive way to understand polynomial field operations by mapping abstract mathematical concepts to visual 3D transformations.