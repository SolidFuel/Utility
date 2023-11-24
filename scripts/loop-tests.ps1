
param($Dir=".", $Count="100")

Push-Location $Dir

$SF_PROJECT = "solidUtility"
if (!(Test-Path "pluginval.zip")) {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;
    Invoke-WebRequest https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_Windows.zip -OutFile pluginval.zip
}

if (!(Test-Path "pluginval.exe")) {
    Expand-Archive pluginval.zip -DestinationPath .
}

if (!(Test-Path "val-logs")) {
    mkdir "val-logs"
}

$LOOP_COUNT=$Count

while ($LOOP_COUNT -gt 0 ) {
    Write-Host "---------- COUNT = $LOOP_COUNT ----------"
    .\pluginval.exe --validate-in-process --strictness-level 5 --output-dir "val-logs" "Source\${SF_PROJECT}_artefacts\Release\VST3\${SF_PROJECT}.vst3\Contents\x86_64-win\${SF_PROJECT}.vst3" | Out-Null
    
    if ($LASTEXITCODE -ne 0 ) {
        Write-Error "FAILED!!!"
        $LOOP_COUNT = -1
    } else {
        $LOOP_COUNT = $LOOP_COUNT - 1
    }

}

Pop-Location
