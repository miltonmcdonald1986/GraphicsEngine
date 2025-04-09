$destDir = "lib\imgui"

# Create the destination directory
New-Item -ItemType Directory -Force -Path lib

# Download the zip file
Write-Host "Downloading imgui docking branch..."
Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" -OutFile "docking.zip"

# Extract the zip file
Write-Host "Extracting imgui..."
Expand-Archive -Path "docking.zip" -DestinationPath lib -Force

# Rename the extracted folder to 'imgui'
Rename-Item -Path "lib\imgui-docking" -NewName "imgui"

# Clean up
Write-Host "Cleaning up..."
Remove-Item "docking.zip"

Write-Host "imgui has been downloaded and placed in $destDir!"