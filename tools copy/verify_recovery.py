from pathlib import Path
import json,hashlib,sys,re,wave
sys.path.insert(0,'work');from recover_captures import SRC,sha
O=Path('outputs');manifest=json.loads((O/'recovered-captures/recovery-manifest.json').read_text());prov=manifest['provenance'];st=SRC.stat();assert st.st_size==prov['size'] and st.st_mtime_ns==prov['mtime_ns'];assert sha(SRC)==prov['sha256']
for r in manifest['files']:
 p=Path(r['path']);b=p.read_bytes();assert len(b)==r['size'] and hashlib.sha256(b).hexdigest()==r['sha256']
transactions={x['name']:x for x in json.loads((O/'upload-transactions.json').read_text())}
expected=['090001010000','0c0000018800','0d0000000000','0e0000000700','0c0000020080','090000000000','090001000000','0c0000000d00','0d0000000000','0e0000000700','090000000000']
for key in ['sample-complete','latest-sample-complete']:assert [r['cdb'].lower() for r in transactions[key]['records']]==expected
expectedp=['090001000000','0c0000018800','0d0000000000','0e0000000700','090000000000','090001000000','0c0000018900','0d0000000000','0e0000000700','090000000000','090001000000','0c0000000d00','0d0000000000','0e0000000700','090000000000']
for key in ['program-complete','latest-program-complete']:assert [r['cdb'].lower() for r in transactions[key]['records']]==expectedp
for key in ['sample-complete','latest-sample-complete','program-complete','latest-program-complete']:
 for r in transactions[key]['records']:
  assert (r['srb_status'],r['host_status'],r['target_status'])==(1,0,0)
  if r['cdb'].lower().startswith('0e'):assert r['payload_hex']=='f04700164800f7'
headers=json.loads((O/'captured-header-examples.json').read_text());gs=json.loads((O/'captured-golden-vectors.json').read_text())['vectors']
for v in gs:
 b=bytes.fromhex(v['wire_hex']);assert hashlib.sha256(b).hexdigest()==v['wire_sha256'];assert int(v['cdb'][4:10],16)==len(b)
 if 'decoded_header_hex' in v:
  off=8 if v['kind']=='keygroup' else 7;n=b[off:-1];assert len(n)==384 and max(n)<=15;assert bytes(n[i]|n[i+1]<<4 for i in range(0,384,2)).hex()==v['decoded_header_hex']
rows=json.loads((O/'normalized-captures.json').read_text());sampleout=next(r for r in rows if r['archive']=='MESA_CAPTURE' and r['seq']==150);samplein=next(r for r in rows if r['archive']=='MESA_CAPTURE' and r['seq']==188);assert samplein['payload_hex']==sampleout['payload_hex']
for kind in ['program','keygroup']:
 h=bytes.fromhex(next(x['header_hex'] for x in headers if x['type']==kind));assert len(h)==192
 if kind=='keygroup':assert all(h[34+24*z:46+24*z]==bytes([10])*12 for z in range(4))
reg=json.loads((O/'evidence/source-register.json').read_text())
for r in reg['sources']:
 if r['id'] in ['B01','B02','B03','B04','B05','B06']:assert hashlib.sha256(Path(r['path']).read_bytes()).hexdigest()==r['sha256']
bad=[]
for p in O.glob('*.md'):
 for ref in re.findall(r'\]\(([^)]+)\)',p.read_text()):
  if not ref.startswith(('http','#')) and not (p.parent/ref.split('#')[0]).exists():bad.append((p.name,ref))
assert not bad,bad
result={'source_disk_hash_unchanged':True,'source_disk_stat_unchanged':True,'recovered_files_hash_verified':len(manifest['files']),'successful_transcript_orders_checked':4,'captured_golden_packets_checked':len(gs),'sample_metadata_fixture_round_trip_exact':True,'captured_keygroup_zones_blank':True,'reviewed_bridge_files_hash_unchanged':True,'document_links_valid':True,'physical_validation':False}
(O/'recovery-verification.json').write_text(json.dumps(result,indent=2)+'\n');print(result)
newmanifest={str(p.relative_to(O)):{'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(O.rglob('*')) if p.is_file() and p.name!='package-manifest.json'}
(O/'package-manifest.json').write_text(json.dumps(newmanifest,indent=2)+'\n')
