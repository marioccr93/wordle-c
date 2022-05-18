param(
    [string]$codeName
)

Write-Host "Nombre del programa es $codeName"

if($codeName.Length -gt 0){
    # Hacía falta pasar la ruta completa (PSScriptRoot) del archivo a compilar
    Write-Host "Ruta del archivo es $PSScriptRoot"
    Write-Host "Compilando archivo $codeName en $codeName.exe"
    cmd /c gcc "$PSScriptRoot\$codeName.c" -o $codeName
    Write-Host "Ejecutando $codeName.exe"
    & "./$codeName.exe"
}else{
    Write-Host "Compilando main"
    gcc main.c -o main
    Write-Host "Ejecutando main"
    ./main.exe
}