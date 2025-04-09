# Define variables
$glfwVersion = "3.4"
$destDir = "lib\GLFW"
$zipName = "glfw-$glfwVersion.bin.WIN64"
$zipFile = "$zipName.zip"
$zipUrl = "https://github.com/glfw/glfw/releases/download/$glfwVersion/glfw-$glfwVersion.bin.WIN64.zip"

# Create the destination directory
New-Item -ItemType Directory -Force -Path lib

# Download the zip file
Write-Host "Downloading glfw version $glfwVersion..."
Invoke-WebRequest -Uri $zipUrl -OutFile $zipFile

# Extract the zip file
Write-Host "Extracting glfw..."
Expand-Archive -Path $zipFile -DestinationPath lib -Force

# Rename the extracted folder to 'spdlog'
Rename-Item -Path "lib\$zipName" -NewName "GLFW"

# Clean up
Write-Host "Cleaning up..."
Remove-Item $zipFile

Write-Host "GLFW has been downloaded and placed in $destDir!"