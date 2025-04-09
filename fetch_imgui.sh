#!/bin/bash

# Define variables
destDir="lib/imgui"

# Create the destination directory
mkdir -p lib

# Download the zip file
echo "Downloading imgui docking branch..."
wget -O "docking.zip" "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip"

# Extract the zip file
echo "Extracting imgui..."
unzip -o "docking.zip" -d lib

# Rename the extracted folder to 'imgui'
mv "lib/imgui-docking" "${destDir}"

# Clean up
echo "Cleaning up..."
rm "docking.zip"

echo "imgui has been downloaded and placed in ${destDir}!"
