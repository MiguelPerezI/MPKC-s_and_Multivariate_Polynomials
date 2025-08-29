# MPKC's and Multivariate Polynomials

A comprehensive study of **Multivariate Public Key Cryptography (MPKC)** and **multivariate polynomials over finite fields**, combining theoretical analysis with computational implementation using C and OpenGL visualization.

This repository explores multivariate polynomials over finite fields both formally and computationally, using OpenGL to simulate and visualize multivariate finite field polynomial operations.

## Project Overview

This project consists of two main components:

1. **Java Implementation** (`Zp/` directory): Pure mathematical operations for polynomials over finite fields
2. **C/OpenGL Implementation** (`polinomialFields_c/` directory): Advanced computational framework with 3D visualization

### Key Features

- **Polynomial arithmetic** over finite fields (Zp)
- **Matrix operations** for multivariate polynomials  
- **3D visualization** of polynomial field structures using OpenGL
- **Ring and field operations** with visual representations
- **Fractal curve generation** related to polynomial structures
- **Interactive mathematical exploration** tools

## Repository Structure

```
MPKC-s_and_Multivariate_Polynomials/
├── README.md                           # This file
├── LICENSE                            # GNU GPL v3 license
├── Zp/                               # Java implementation
│   ├── Zp.java                       # Basic finite field operations
│   ├── polinomio.java                # Polynomial operations in Zp[x]
│   ├── ZnPoli.class                  # Compiled Java classes
│   └── polinomio.class
├── polinomialFields_c/               # C/OpenGL implementation
│   ├── Main.c                        # Basic testing program
│   ├── MainOpenGL.c                  # OpenGL visualization program
│   ├── polinomios.h/.c              # Polynomial operations
│   ├── Matrix.h/.c                   # Matrix operations
│   ├── vector.h/.c                   # Vector mathematics
│   ├── Arista.h/.c                   # Edge/graph structures
│   ├── Hilbert.h/.c                  # Hilbert curve generation
│   ├── fractalCurves.h/.c           # Fractal mathematics
│   ├── Tree.h/.c                     # Tree data structures
│   ├── turtle.h/.c                   # Turtle graphics system
│   └── a.out                         # Compiled executable
└── Documentation/                    # Academic papers (PDFs)
    ├── Expo.pdf                      # Main exposition
    ├── PolinomiosMultivariable.pdf   # Multivariate polynomials theory
    ├── Signature_Schemes.pdf         # Cryptographic signature schemes
    └── UiO_Math_Department_Beamer_Theme(3).pdf # Presentation
```

## Prerequisites

### For Java Components
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install default-jdk

# macOS
brew install openjdk

# Verify installation
java --version
javac --version
```

### For C/OpenGL Components
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install gcc build-essential
sudo apt-get install freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install libx11-dev libxmu-dev libxi-dev

# macOS (with Homebrew)
brew install gcc
brew install freeglut

# Verify OpenGL libraries
pkg-config --exists gl glu glut && echo "OpenGL libraries ready"
```

## Building and Running

### Java Components

#### Basic Finite Field Operations
```bash
cd Zp/
javac Zp.java
java Zp
```

#### Polynomial Operations
```bash
cd Zp/
javac polinomio.java
java polinomio

# Follow interactive prompts:
# 1. Enter modulus (e.g., 7 for Z_7)
# 2. Enter first polynomial g(x) coefficients
# 3. Enter second polynomial p(x) coefficients
# 4. View polynomial operations and residue calculations
```

### C/OpenGL Components

#### Basic Mathematical Testing
```bash
cd polinomialFields_c/
gcc -o test_math Main.c vector.c Matrix.c polinomios.c Arista.c -lm -lGL -lGLU -lglut
./test_math
```

#### Full OpenGL Visualization
```bash
cd polinomialFields_c/

# Compile the complete visualization system
gcc Arista.c fractalCurves.c Hilbert.c MainOpenGL.c Matrix.c polinomios.c Tree.c turtle.c vector.c -lGL -lGLU -lglut -lm -o polynomial_visualizer

# Run the visualization
./polynomial_visualizer
```

#### Individual Component Testing
```bash
cd polinomialFields_c/

# Test polynomial operations only
gcc Main.c polinomios.c Matrix.c vector.c Arista.c -lm -lGL -lGLU -lglut -o test_polynomials
./test_polynomials
```

## Usage Examples

### Java Polynomial Operations

The Java implementation provides an interactive interface for polynomial arithmetic:

```
$ java polinomio
Introduce (mod n) = 7

Ingrese g(x):
Choose the degree of the polinomial:
deg(p) = 2
Now type the coeficientes needed:
a[0] = 1
a[1] = 2  
a[2] = 3
p(x) = 1 + 2x^{1} + 3x^{2}

[Enter second polynomial...]

residuo(x) := [result of polynomial division]
```

### C Implementation Features

The C implementation provides:

- **Vector operations** in 3D space
- **Matrix computations** for polynomial coefficients  
- **Ring structure** visualization for finite fields
- **Interactive OpenGL** rendering of mathematical objects
- **Fractal generation** related to polynomial structures

## Mathematical Background

This project implements:

1. **Polynomial Rings**: Operations in Zp[x] where p is prime
2. **Finite Field Arithmetic**: Addition, multiplication, division in finite fields
3. **Multivariate Extensions**: Polynomials in multiple variables
4. **Geometric Representations**: 3D visualization of algebraic structures
5. **Cryptographic Applications**: Related to MPKC signature schemes

## Development and Testing

### Code Organization

- **Modular Design**: Separate headers for different mathematical structures
- **Memory Management**: Proper allocation/deallocation for dynamic structures
- **Error Handling**: Input validation and mathematical constraint checking
- **Performance**: Optimized algorithms for polynomial operations

### Testing Workflow

1. **Unit Testing**: Test individual mathematical operations
2. **Integration Testing**: Verify component interactions
3. **Visual Verification**: Use OpenGL output to confirm correctness
4. **Performance Testing**: Benchmark critical operations

## Troubleshooting

### Common Build Issues

**OpenGL linking errors:**
```bash
# Ensure all OpenGL development packages are installed
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

# For older systems, you might need:
sudo apt-get install libglut3-dev
```

**Java compilation errors:**
```bash
# Ensure Java Development Kit is installed
sudo apt-get install default-jdk
export JAVA_HOME=/usr/lib/jvm/default-java
```

**Runtime display errors:**
```bash
# For OpenGL applications, ensure X11 forwarding if using SSH:
ssh -X username@hostname

# Or set display environment:
export DISPLAY=:0.0
```

### Performance Notes

- **Large Field Operations**: Performance scales with field size (mod p)
- **Graphics Rendering**: Requires hardware-accelerated OpenGL for smooth visualization
- **Memory Usage**: Large polynomial degrees require significant RAM

## Contributing

1. **Mathematical Extensions**: Add support for additional field types
2. **Visualization**: Enhance OpenGL rendering capabilities
3. **Optimization**: Improve algorithm efficiency for large computations
4. **Documentation**: Expand theoretical background and examples

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Academic References

See the included PDF documents for detailed mathematical background:

- `Expo.pdf`: Main theoretical exposition
- `PolinomiosMultivariable.pdf`: Multivariate polynomial theory
- `Signature_Schemes.pdf`: Cryptographic applications
- `UiO_Math_Department_Beamer_Theme(3).pdf`: Academic presentation

## Author

Research project exploring the intersection of algebra, geometry, and cryptography through computational implementation.
