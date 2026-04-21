param(
    [Parameter(Mandatory = $true)]
    [string]$ChartExe,
    [Parameter(Mandatory = $true)]
    [int]$SceneIndex,
    [Parameter(Mandatory = $true)]
    [string]$GoldenImage,
    [string]$S57Root = $env:S57_TESTDATA_ROOT,
    [string]$AssetRoot = "vendor/opencpn_s57data",
    [string]$Palette = "DAY_BRIGHT",
    [string]$OutputImage = ""
)

Add-Type -AssemblyName System.Drawing

function Get-ImagePixelDigest {
    param(
        [Parameter(Mandatory = $true)]
        [string]$ImagePath
    )

    $bitmap = [System.Drawing.Bitmap]::FromFile($ImagePath)
    try {
        $stream = New-Object System.IO.MemoryStream
        try {
            $bitmap.Save($stream, [System.Drawing.Imaging.ImageFormat]::Bmp)
            $streamBytes = $stream.ToArray()
            $sha256 = [System.Security.Cryptography.SHA256]::Create()
            try {
                return ([System.BitConverter]::ToString($sha256.ComputeHash($streamBytes))).Replace("-", "").ToLowerInvariant()
            }
            finally {
                $sha256.Dispose()
            }
        }
        finally {
            $stream.Dispose()
        }
    }
    finally {
        $bitmap.Dispose()
    }
}

if ($SceneIndex -lt 1) {
    Write-Error "SceneIndex must be >= 1."
    exit 1
}

if ([string]::IsNullOrWhiteSpace($S57Root) -or -not (Test-Path -LiteralPath $S57Root -PathType Container)) {
    Write-Host "Skipping scene $SceneIndex because S57 root is unavailable."
    exit 125
}

if (-not (Test-Path -LiteralPath $ChartExe -PathType Leaf)) {
    Write-Error "chart_standalone executable not found: $ChartExe"
    exit 2
}

if (-not (Test-Path -LiteralPath $GoldenImage -PathType Leaf)) {
    Write-Error "Golden image not found: $GoldenImage"
    exit 3
}

$sceneCells = Get-ChildItem -LiteralPath $S57Root -File |
    Where-Object { $_.Extension -match '^\.\d{3}$' } |
    Sort-Object Name

if ($sceneCells.Count -lt $SceneIndex) {
    Write-Error "SceneIndex $SceneIndex is out of range for available cells ($($sceneCells.Count))."
    exit 4
}

$selectedCell = $sceneCells[$SceneIndex - 1]
$tempSceneRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("zero_wx_scene_{0}_{1}" -f $SceneIndex, [Guid]::NewGuid().ToString("N"))

try {
    New-Item -ItemType Directory -Path $tempSceneRoot -Force | Out-Null
    Copy-Item -LiteralPath $selectedCell.FullName -Destination (Join-Path $tempSceneRoot $selectedCell.Name) -Force

    if ([string]::IsNullOrWhiteSpace($OutputImage)) {
        $OutputImage = Join-Path $tempSceneRoot ("scene-{0:D2}-actual.png" -f $SceneIndex)
    } else {
        $outputDir = Split-Path -Parent $OutputImage
        if (-not [string]::IsNullOrWhiteSpace($outputDir)) {
            New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
        }
    }

    & $ChartExe `
        "--real-s57-smoke" `
        "--golden-capture" `
        "--asset-root=$AssetRoot" `
        "--palette=$Palette" `
        "--s57-root=$tempSceneRoot" `
        "--capture-path=$OutputImage"
    $runExit = $LASTEXITCODE
    if ($runExit -eq 125) {
        exit 125
    }

    if ($runExit -ne 0) {
        Write-Error "chart_standalone failed for scene $SceneIndex with exit code $runExit."
        exit $runExit
    }

    if (-not (Test-Path -LiteralPath $OutputImage -PathType Leaf)) {
        Write-Error "Scene output was not created: $OutputImage"
        exit 5
    }

    $expectedDigest = Get-ImagePixelDigest -ImagePath $GoldenImage
    $actualDigest = Get-ImagePixelDigest -ImagePath $OutputImage
    if ($expectedDigest -ne $actualDigest) {
        Write-Error ("Golden image mismatch for scene-{0}: expected={1}, actual={2}" -f $SceneIndex, $expectedDigest, $actualDigest)
        exit 6
    }

    exit 0
}
finally {
    if (Test-Path -LiteralPath $tempSceneRoot -PathType Container) {
        Remove-Item -LiteralPath $tempSceneRoot -Recurse -Force
    }
}
