#!/bin/bash

# Define variables
destDir="lib/stb"
zipFile="stb.zip"
zipUrl="https://github.com/nothings/stb/archive/refs/heads/master.zip"

# Create the destination directory
mkdir -p lib

# Download the zip file
echo "Downloading stb..."
curl -L -o "$zipFile" "$zipUrl"

# Extract the zip file
echo "Extracting stb..."
unzip -o "$zipFile" -d lib

# Rename the extracted folder to 'stb'
mv "lib/stb-master" "$destDir"

# Clean up
echo "Cleaning up..."
rm "$zipFile"

echo "stb has been downloaded and placed in $destDir!"
