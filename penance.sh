#!/usr/bin/env bash

# -------- CONFIG --------
BUILD_DIR=/build   # your build folder
TARGET=/build/penance      # name of the executable
# ------------------------

# Helper: colored output
info() { echo -e "\033[1;34m[INFO]\033[0m $1"; }
error() { echo -e "\033[1;31m[ERROR]\033[0m $1"; }

# Default command
CMD=${1:-run}

case "$CMD" in

    run)
        info "Building project..."
        make -C $BUILD_DIR || { error "Build failed"; exit 1; }
        info "Running executable..."
        ./$BUILD_DIR/$TARGET
        ;;

    clean)
        info "Cleaning build..."
        make -C $BUILD_DIR clean
        ;;

    rebuild)
        info "Cleaning build..."
        make -C $BUILD_DIR clean
        info "Rebuilding project..."
        make -C $BUILD_DIR || { error "Build failed"; exit 1; }
        info "Running executable..."
        ./$BUILD_DIR/$TARGET
        ;;

    check)
        info "Building project to check for errors..."
        make -C $BUILD_DIR || { error "Build failed"; exit 1; }
        ;;

    *)
        error "Unknown command: $CMD"
        echo "Usage: $0 [run|clean|rebuild|check]"
        exit 1
        ;;
esac

