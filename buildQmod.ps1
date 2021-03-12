# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk -j 4
Compress-Archive -Path  "./libs/arm64-v8a/libbeatsaber-hook_1_1_2.so",`
                        "./extern/libbeatsaber-hook_1_1_0.so",`
                        "./libs/arm64-v8a/libcustom-types.so",`
                        "./libs/arm64-v8a/libmonkecomputer.so",`
                        "./ExtraFiles/monitor.json",`
                        "./ExtraFiles/monitor",`
                        "./mod.json" -DestinationPath "./MonkeComputer.zip" -Update

& copy-item -Force "./MonkeComputer.zip" "./MonkeComputer.qmod"