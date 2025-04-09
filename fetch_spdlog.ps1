# Define variables
$spdlogVersion = "v1.15.2"
$destDir = "lib\spdlog"
$zipFile = "spdlog-$spdlogVersion.zip"
$zipUrl = "https://github.com/gabime/spdlog/archive/refs/tags/$spdlogVersion.zip"

# Create the destination directory
New-Item -ItemType Directory -Force -Path lib

# Download the zip file
Write-Host "Downloading spdlog version $spdlogVersion..."
Invoke-WebRequest -Uri $zipUrl -OutFile $zipFile

# Extract the zip file
Write-Host "Extracting spdlog..."
Expand-Archive -Path $zipFile -DestinationPath lib -Force

# Rename the extracted folder to 'spdlog'
Rename-Item -Path "lib\spdlog-$($spdlogVersion.TrimStart('v'))" -NewName "spdlog"

# Clean up
Write-Host "Cleaning up..."
Remove-Item $zipFile

Write-Host "spdlog has been downloaded and placed in $destDir!"