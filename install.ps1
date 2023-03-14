# yush - Young's Shell

# build

$projectPath = Get-Location

Write-Output "`nstart Build`n"

$BuildDir = './build'
if ( !(Test-Path -Path $BuildDir) )
{
    mkdir build
}
Set-Location $projectPath\build
cmake $projectPath
Set-Location $projectPath

# add to path

Write-Output "`nset yush binary file to PATH`n"

$UserDir = "~"
Set-Location -Path $UserDir

$envDir = '~\yush'
if ( !(Test-Path -Path $envDir) )
{
    mkdir yush
}

copy $projectPath\build\Debug\yush.exe $UserDir\yush\

[Environment]::SetEnvironmentVariable("PATH", "$ENV:PATH;$UserDir\yush\", "USER")

Set-Location $projectPath

Write-Output "All tasks done`n"