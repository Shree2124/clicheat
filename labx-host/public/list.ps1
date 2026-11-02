$cat = Invoke-RestMethod "https://clicheat.vercel.app/catalog.json"
Write-Host "`n==== AISC & Embedded Systems / RTOS Laboratory Experiments (CliCheat) ====" -ForegroundColor Cyan
$cat.experiments | Format-Table @{Label="ID"; Expression={"Exp " + ("{0:D2}" -f $_.id)}}, @{Label="Title"; Expression={$_.title}}, @{Label="Language"; Expression={$_.language}}
Write-Host "Quick commands:" -ForegroundColor Yellow
Write-Host "  Pull ERTOS experiments : irm https://clicheat.vercel.app/ertos.ps1 | iex" -ForegroundColor White
Write-Host "  Pull all experiments   : irm https://clicheat.vercel.app/all.ps1 | iex" -ForegroundColor White
Write-Host "  Pull one experiment    : & (irm https://clicheat.vercel.app/get.ps1) <id>`n" -ForegroundColor White
