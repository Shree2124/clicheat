$zip = Join-Path $PWD "pdfs_temp.zip"
Write-Host "Downloading ES & RTOS PDF Submissions (Div A - Batch C)..." -ForegroundColor Cyan
Invoke-WebRequest "https://clicheat.vercel.app/downloads/ES_RTOS_DIV_A_BATCH_C_PDF_Submissions.zip" -OutFile $zip -UseBasicParsing
Expand-Archive $zip -DestinationPath $PWD -Force
Remove-Item $zip -Force
Write-Host "[OK] PDF submissions extracted to current directory!" -ForegroundColor Green
