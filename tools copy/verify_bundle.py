from pathlib import Path
import hashlib, json
root = Path(__file__).resolve().parents[1]
manifest = json.loads((root / "SHA256SUMS.json").read_text())
for name, expected in manifest.items():
    p = root / name
    assert p.is_file(), "Missing: " + name
    assert hashlib.sha256(p.read_bytes()).hexdigest() == expected, "Changed: " + name
recovery = json.loads((root / "outputs/recovered-captures/recovery-manifest.json").read_text())
for item in recovery["files"]:
    p = root / item["path"]
    assert len(p.read_bytes()) == item["size"], str(p)
    assert hashlib.sha256(p.read_bytes()).hexdigest() == item["sha256"], str(p)
print(f"PASS: {len(manifest)} exported files; {len(recovery['files'])} original recovered files unchanged")
