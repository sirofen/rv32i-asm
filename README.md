[![C++ CI](https://github.com/sirofen/rv32i-asm/actions/workflows/ci.yml/badge.svg)](https://github.com/sirofen/rv32i-asm/actions/workflows/ci.yml)
# RV32I Assembler

## Overview

This project provides a C++ implementation of an assembler for the RV32I instruction set. It translates RV32I assembly language code into machine code.

## Dependencies

- **Boost Libraries**: Version 1.71
- **CMake**: Version 3.14 or newer is required for building the project.

## Building the Project

To build the assembler, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/sirofen/rv32i-asm.git
   cd rv32i-asm
   ```

2. **Configure with CMake**:
   ```bash
   mkdir build && cd build
   cmake ..
   ```

3. **Compile**:
   ```bash
   cmake --build .
   ```

   Optionally, to build tests, ensure that the `BUILD_TESTS` option is enabled in CMake by passing `-DBUILD_TESTS=ON`.

## Usage

Run the assembler using the following command format:

```bash
./rv32i-assembler -i <input_path> -o <output_path>
```

- `-i, --input`: Specifies the path to the input assembly file.
- `-o, --output`: Specifies the path for the output machine code file.

## License

This project is released under the MIT License, which permits modification, distribution, and private use under the condition that the license and copyright notice are included in all copies or substantial portions of the software.
