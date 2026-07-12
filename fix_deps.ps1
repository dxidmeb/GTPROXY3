$ErrorActionPreference = 'Stop'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

Write-Host "Downloading cmake-conan..."
Invoke-WebRequest -Uri "https://github.com/conan-io/cmake-conan/archive/refs/heads/develop2.zip" -OutFile "conan.zip"
Expand-Archive -Path "conan.zip" -DestinationPath "." -Force
Remove-Item -Recurse -Force cmake/cmake-conan -ErrorAction SilentlyContinue
Rename-Item -Path "cmake-conan-develop2" -NewName "cmake-conan"
Move-Item -Path "cmake-conan" -Destination "cmake/"

Write-Host "Downloading enet..."
Invoke-WebRequest -Uri "https://github.com/ZTzTopia/enet/archive/refs/heads/master.zip" -OutFile "enet.zip"
Expand-Archive -Path "enet.zip" -DestinationPath "." -Force
Remove-Item -Recurse -Force lib/enet -ErrorAction SilentlyContinue
Rename-Item -Path "enet-master" -NewName "enet"
Move-Item -Path "enet" -Destination "lib/"

Write-Host "Downloading cpp-httplib..."
Invoke-WebRequest -Uri "https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.zip" -OutFile "httplib.zip"
Expand-Archive -Path "httplib.zip" -DestinationPath "." -Force
Remove-Item -Recurse -Force lib/cpp-httplib -ErrorAction SilentlyContinue
Rename-Item -Path "cpp-httplib-master" -NewName "cpp-httplib"
Move-Item -Path "cpp-httplib" -Destination "lib/"

Remove-Item "conan.zip", "enet.zip", "httplib.zip" -ErrorAction SilentlyContinue

Remove-Item .gitmodules -ErrorAction SilentlyContinue

git rm --cached cmake/cmake-conan -ErrorAction SilentlyContinue
git rm --cached lib/enet -ErrorAction SilentlyContinue
git rm --cached lib/cpp-httplib -ErrorAction SilentlyContinue

git add .
git commit -m "Add missing dependencies as regular folders"
git push
