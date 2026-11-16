#!/bin/sh
set -e

# Clear out any firmware files
rm -f *.hex
rm -f *.uf2

# Add Homebrew's keg-only cross-compilers to PATH (macOS)
for d in /opt/homebrew/opt/avr-gcc@8/bin \
         /opt/homebrew/opt/arm-none-eabi-gcc@8/bin \
         /opt/homebrew/opt/arm-none-eabi-binutils/bin \
         "$HOME/.local/bin"; do
    [ -d "$d" ] && PATH="$d:$PATH"
done
export PATH

# Ensure QMK CLI is installed
if ! command -v qmk >/dev/null 2>&1; then
    echo "QMK CLI not found" >&2
    echo "Install with pipx install qmk" >&2
    exit 2
fi

# Checkout QMK repository
if [ -d "vial-qmk" ]; then
    echo "VIAL QMK repository already exists, pulling latest changes"
    cd vial-qmk
    git pull
    cd ..
else
    echo "VIAL QMK repository does not exist, cloning"
    git clone --depth 1 --recurse-submodules https://github.com/vial-kb/vial-qmk
fi

# Copy files to QMK repository
if [ ! -L "vial-qmk/keyboards/crkbd/keymaps/custom" ]; then
    echo "Symlink keymaps in VIAL QMK repository"
    ln -sfn "$(pwd)/keyboards/crkbd/keymaps/custom" vial-qmk/keyboards/crkbd/keymaps/
fi

# Build firmware
echo "Building firmware..."
cd vial-qmk
qmk compile -e MASTER=left -e CONVERT_TO=kb2040 --keyboard crkbd --keymap custom
qmk compile -e MASTER=left -e ALLOW_WARNINGS=yes --keyboard crkbd --keymap custom
cd ..

# Copy firmware out of build directory
cp vial-qmk/.build/*.hex .
cp vial-qmk/.build/*.uf2 .