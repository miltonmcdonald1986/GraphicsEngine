#!/bin/bash

# Define variables
glmVersion="1.0.1"
destDir="lib/glm"
zipName="$glmVersion"
zipFile="$zipName.zip"
zipUrl="https://github.com/g-truc/glm/archive/refs/tags/$zipFile"

# Create the destination directory
mkdir -p lib

# Download the zip file
echo "Downloading glm version $glmVersion..."
curl -L -o "$zipFile" "$zipUrl"

# Extract the zip file
echo "Extracting glm..."
unzip -o "$zipFile" -d lib

# Rename the extracted folder to 'glm'
mv "lib/glm-$zipName" "$destDir"

# Clean up
echo "Cleaning up..."
rm "$zipFile"

echo "glm has been downloaded and placed in $destDir!"