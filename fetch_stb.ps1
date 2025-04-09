# Define variables
$destDir = "lib\stb"
$zipFile = "stb.zip"
$zipUrl = "https://github.com/nothings/stb/archive/refs/heads/master.zip"

# Create the destination directory
New-Item -ItemType Directory -Force -Path lib

# Download the zip file
Write-Host "Downloading stb"
Invoke-WebRequest -Uri $zipUrl -OutFile $zipFile

# Extract the zip file
Write-Host "Extracting stb..."
Expand-Archive -Path $zipFile -DestinationPath lib -Force

# Rename the extracted folder to 'stb'
Rename-Item -Path "lib\stb-master" -NewName "stb"

# Clean up
Write-Host "Cleaning up..."
Remove-Item $zipFile

Write-Host "stb has been downloaded and placed in $destDir!"