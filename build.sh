#!/bin/bash

if [ ! -d "./build" ]; then
  mkdir -p build
fi

if [ ! -d "./bin" ]; then
  mkdir -p bin
fi

cmake -S . -B build -G Ninja
cmake --build build
cp build/VulkanEngine bin/VulkanEngine
