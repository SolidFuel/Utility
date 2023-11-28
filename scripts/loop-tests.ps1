
param($Dir="build", $Count=100, $Level=5)

Push-Location $Dir

$env:OS_TAG = "win64"

$output = & bash ../scripts/project_vars.sh - ps | Out-String
Invoke-Expression $output

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
    .\pluginval.exe --validate-in-process --strictness-level $Level --output-dir "val-logs" "${env:SF_VST3_BUILD_PATH}\${env:SF_ARTIFACT_PATH}\${env:SF_BUILD_FILE}" | Out-Null
    
    if ($LASTEXITCODE -ne 0 ) {
        Write-Error "FAILED!!!"
        $LOOP_COUNT = -1
    } else {
        $LOOP_COUNT = $LOOP_COUNT - 1
    }

}

Pop-Location
