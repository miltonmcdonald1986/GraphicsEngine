#!/bin/bash

# Define variables
spdlogVersion="v1.15.2"
destDir="lib/spdlog"
zipFile="spdlog-${spdlogVersion}.zip"
zipUrl="https://github.com/gabime/spdlog/archive/refs/tags/${spdlogVersion}.zip"

# Create the destination directory
mkdir -p lib

# Download the zip file
echo "Downloading spdlog version ${spdlogVersion}..."
wget -O "${zipFile}" "${zipUrl}"

# Extract the zip file
echo "Extracting spdlog..."
unzip -o "${zipFile}" -d lib

# Rename the extracted folder to 'spdlog'
mv "lib/spdlog-${spdlogVersion#v}" "${destDir}"

# Clean up
echo "Cleaning up..."
rm "${zipFile}"

echo "spdlog has been downloaded and placed in ${destDir}!"

