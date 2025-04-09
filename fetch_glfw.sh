#!/bin/bash

# Define variables
glfwVersion="3.4"
destDir="lib/GLFW"
zipName="glfw-${glfwVersion}.bin.WIN64"
zipFile="${zipName}.zip"
zipUrl="https://github.com/glfw/glfw/releases/download/${glfwVersion}/glfw-${glfwVersion}.bin.WIN64.zip"

# Create the destination directory
mkdir -p lib

# Download the zip file
echo "Downloading glfw version ${glfwVersion}..."
wget -O "${zipFile}" "${zipUrl}"

# Extract the zip file
echo "Extracting glfw..."
unzip -o "${zipFile}" -d lib

# Rename the extracted folder to 'GLFW'
mv "lib/${zipName}" "${destDir}"

# Clean up
echo "Cleaning up..."
rm "${zipFile}"

echo "GLFW has been downloaded and placed in ${destDir}!"

