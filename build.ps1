$msbuildPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

if (Test-Path $msbuildPath) {
    Write-Host "Building project..."
    & $msbuildPath "ECommerce.slnx" /p:Configuration=Debug /p:Platform=x64 /t:Build
} else {
    Write-Host "MSBuild not found at: $msbuildPath"
    Write-Host "Searching for MSBuild..."
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $vsPath = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
        if ($vsPath) {
            $msbuildPath = Join-Path $vsPath "MSBuild\Current\Bin\MSBuild.exe"
            if (Test-Path $msbuildPath) {
                Write-Host "Found MSBuild at: $msbuildPath"
                & $msbuildPath "ECommerce.slnx" /p:Configuration=Debug /p:Platform=x64 /t:Build
            }
        }
    }
}
