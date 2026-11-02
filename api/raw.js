/**
 * Vercel API Route: api/raw.js  →  GET /r?f=<filename>&d=<compressed_code>
 *
 * Serves raw PowerShell delivery script from a compressed stateless URL.
 * Reachable via the /r rewrite defined in vercel.json.
 */

const zlib = require('zlib');

export default async function handler(req, res) {
  res.setHeader('Access-Control-Allow-Origin', '*');

  const { f: rawF, d: data } = req.query;
  const filename = (rawF || 'experiment.py').replace(/[^\w\.\-_]/g, '_');

  if (!data) {
    res.setHeader('Content-Type', 'text/plain; charset=utf-8');
    return res.status(400).send('Write-Error "Missing data parameter (d)."');
  }

  try {
    let base64 = data.replace(/-/g, '+').replace(/_/g, '/');
    while (base64.length % 4) {
      base64 += '=';
    }
    const buf = Buffer.from(base64, 'base64');
    let decoded;
    try {
      decoded = zlib.gunzipSync(buf).toString('utf-8');
    } catch (e) {
      decoded = buf.toString('utf-8');
    }

    let script;
    if (decoded.includes('$target') && decoded.includes('Set-Content')) {
      script = decoded;
    } else {
      script = `# LabX Remote - Custom Experiment Delivery
$filename = "${filename}"
$code = @'
${decoded}
'@
$target = Join-Path $PWD $filename
Set-Content -Path $target -Value $code -Encoding utf8
Write-Host ""
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host " [OK] Experiment code saved to: $filename" -ForegroundColor Green
Write-Host " Theory is embedded after line 50. Ready to execute!" -ForegroundColor White
Write-Host " Run: py $filename" -ForegroundColor Yellow
Write-Host "============================================================" -ForegroundColor Cyan
`;
    }

    res.setHeader('Content-Type', 'text/plain; charset=utf-8');
    res.setHeader('Cache-Control', 'public, max-age=86400');
    return res.status(200).send(script);
  } catch (err) {
    res.setHeader('Content-Type', 'text/plain; charset=utf-8');
    return res
      .status(500)
      .send(`Write-Error "Failed to process delivery script: ${err.message}"`);
  }
}
