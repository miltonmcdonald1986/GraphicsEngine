# Define variables
$glmVersion = "1.0.1"
$destDir = "lib\glm"
$zipName = "$glmVersion"
$zipFile = "$zipName.zip"
$zipUrl = "https://github.com/g-truc/glm/archive/refs/tags/$zipFile"

# Create the destination directory
New-Item -ItemType Directory -Force -Path lib

# Download the zip file
Write-Host "Downloading glm version $glmVersion..."
Invoke-WebRequest -Uri $zipUrl -OutFile $zipFile

# Extract the zip file
Write-Host "Extracting glm..."
Expand-Archive -Path $zipFile -DestinationPath lib -Force

# Rename the extracted folder to 'glm'
Rename-Item -Path "lib\glm-$zipName" -NewName "glm"

# Clean up
Write-Host "Cleaning up..."
Remove-Item $zipFile

Write-Host "glm has been downloaded and placed in $destDir!"