#!/bin/bash

# SFIio Shared Library Installer
# Author: T.Vikram (an idiot don't be like me - still an idiot but learning!)
# Date: Current date

echo "Building SFIio library..."

# Get the script's directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "Installer location: $SCRIPT_DIR"

# Navigate to project root
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
echo "Project root: $PROJECT_ROOT"

# Set paths to source files - CHANGED THESE
SRC_DIR="$PROJECT_ROOT/src"
SFIIO_C="$SRC_DIR/SFIio.c"
SFIIO_H="$SRC_DIR/SFIio.h"

# Verify source files exist - CHANGED THESE
if [ ! -f "$SFIIO_C" ]; then
    echo "Error: Cannot find SFIio.c at $SFIIO_C"
    exit 1
fi

if [ ! -f "$SFIIO_H" ]; then
    echo "Error: Cannot find SFIIio.h at $SFIIO_H"
    exit 1
fi

# Check if gcc is installed
if ! command -v gcc &> /dev/null; then
    echo "gcc not found. Please install gcc first."
    exit 1
fi

# Navigate to src directory
cd "$SRC_DIR" || {
    echo "Failed to enter src directory"
    exit 1
}

echo "Building shared library from: $(pwd)..."

# Compile as shared library - CHANGED FILENAMES
gcc -c -Wall -Wextra -std=c99 -fPIC -O2 SFIio.c -o SFIio.o
gcc -shared SFIio.o -o libSFIio.so

# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Make library readable
chmod 644 libSFIio.so

# Optional: Install system-wide
read -p "Install to /usr/local? (requires sudo) [y/N]: " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    # Install library - CHANGED FILENAMES
    sudo cp libSFIio.so /usr/local/lib/
    sudo ldconfig
    
    # Install header - CHANGED FILENAMES
    sudo cp SFIio.h /usr/local/include/
    
    echo "Library installed to /usr/local/lib/libSFIio.so"
    echo "Header installed to /usr/local/include/SFIio.h"
    
    # Clean up - CHANGED FILENAME
    rm -f SFIio.o
    echo "Build files cleaned up"
else
    echo "Library built locally in $SRC_DIR/libSFIio.so"
    echo "Header available at $SRC_DIR/SFIio.h"
    
    # Copy library to project root
    cp libSFIio.so "$PROJECT_ROOT/"
    echo "Also copied libSFIio.so to project root: $PROJECT_ROOT"
    
    echo ""
    echo "To compile with local library:"
    echo "  cd $PROJECT_ROOT"
    echo "  gcc your_program.c -L. -lSFIio -o your_program"
    echo "  export LD_LIBRARY_PATH=.:\$LD_LIBRARY_PATH"
fi

echo
echo "Build complete! Thanks for using my SFIio library :)"
