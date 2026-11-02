/**
 * Vercel API Route: api/publish.js  →  POST /api/publish
 *
 * Receives an experiment Python code or delivery script, publishes it to dpaste,
 * and returns the custom short PowerShell command:
 *   irm https://aisccli.vercel.app/s/<ID> | iex
 */

const zlib = require('zlib');

const BASE_URL = process.env.VERCEL_URL
  ? `https://${process.env.VERCEL_URL}`
  : 'https://aisccli.vercel.app';

export default async function handler(req, res) {
  // CORS preflight
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');

  if (req.method === 'OPTIONS') {
    return res.status(204).end();
  }

  if (req.method !== 'POST') {
    return res
      .status(405)
      .json({ error: 'Method not allowed. Use POST.' });
  }

  try {
    const payload = req.body || {};
    const filename = (payload.filename || 'experiment.py').replace(/[^\w\.\-_]/g, '_');
    const code = payload.code || '';
    let script = payload.script;

    if (!script && !code) {
      return res
        .status(400)
        .json({ error: 'Missing code or script in request body.' });
    }

    // If only code is provided, wrap into an automated PowerShell delivery script
    if (!script) {
      script = `# LabX Remote - Custom Experiment Delivery
$filename = "${filename}"
$code = @'
${code}
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

    let slug = null;
    let customUrl = null;

    try {
      // 1. Attempt publishing to dpaste
      const params = new URLSearchParams({
        content: script,
        format: 'url',
        expiry_days: '30'
      });

      const response = await fetch('https://dpaste.org/api/', {
        method: 'POST',
        body: params,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
      });

      if (response.ok) {
        const text = (await response.text()).trim();
        // text is e.g. "https://dpaste.org/AbCdE" or "https://dpaste.org/AbCdE/"
        const parts = text.split('/').filter(Boolean);
        slug = parts[parts.length - 1];
        customUrl = `${BASE_URL}/s/${slug}`;
      }
    } catch (dpasteErr) {
      console.warn('dpaste error, falling back to compressed URL:', dpasteErr.message);
    }

    // 2. If dpaste succeeded, return the short command
    if (slug && customUrl) {
      return res.status(200).json({
        success: true,
        slug,
        filename,
        url: customUrl,
        command: `irm ${customUrl} | iex`
      });
    }

    // 3. Fallback: Stateless compressed URL pointing to /api/raw
    const compressed = zlib.gzipSync(Buffer.from(script, 'utf-8')).toString('base64url');
    const directUrl = `${BASE_URL}/r?f=${encodeURIComponent(filename)}&d=${compressed}`;

    return res.status(200).json({
      success: true,
      slug: 'direct',
      filename,
      url: directUrl,
      command: `irm "${directUrl}" | iex`
    });
  } catch (err) {
    return res.status(500).json({ error: err.message });
  }
}
