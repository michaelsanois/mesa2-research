from pathlib import Path
import json,re,csv,hashlib,sys,struct,wave
sys.path.insert(0,'work');from reconcile_captures import load
OUT=Path('outputs');ROOT=OUT/'recovered-captures'
windows=[('sample-no-header-reply','cap_import1',353,370),('sample-no-post-reply','cap_import2',62,77),('sample-complete','cap_postpcm',62,72),('program-no-keygroup-reply','cap_program',57,71),('program-no-post-reply','cap_kg',57,76),('program-complete','cap_final',57,71),('program-readback','cap_final',72,116),('latest-program-complete','MESA_CAPTURE',69,83),('latest-sample-complete','MESA_CAPTURE',149,159),('latest-program-byte-reads','MESA_CAPTURE',127,132),('latest-final-byte-reads','MESA_CAPTURE',208,213)]
trans=[]
with (OUT/'upload-order.csv').open('w') as f:
 w=csv.writer(f);w.writerow(['transaction','archive','seq','tick_ms','cdb','direction','requested_bytes','payload_bytes','srb_status','host_status','target_status','payload_hex','payload_file','payload_sha256'])
 for name,ar,lo,hi in windows:
  rows=[r for r in load(ar)[0] if lo<=r['seq']<=hi];assert len(rows)==hi-lo+1
  trans.append({'name':name,'archive':ar,'first_seq':lo,'last_seq':hi,'authority':'Historical original MESA client against a synthetic ASPI target; DATA IN and statuses are fixture-generated.','records':rows})
  for r in rows:w.writerow([name,ar,r['seq'],r['tick_ms'],r.get('cdb',''),r.get('direction',''),r.get('requested',0),r.get('payload_bytes',0),r.get('srb_status'),r.get('host_status'),r.get('target_status'),r.get('payload_hex',''),r.get('payload_file',''),r.get('payload_sha256','')])
(OUT/'upload-transactions.json').write_text(json.dumps(trans,indent=2)+'\n')
headers=json.loads((OUT/'captured-header-examples.json').read_text());g=[]
for x in headers:
 r=next(r for r in load(x['archive'])[0] if r['seq']==x['seq']);g.append({'kind':x['type'],'archive':x['archive'],'seq':x['seq'],'wire_hex':r['payload_hex'],'cdb':r['cdb'],'decoded_header_hex':x['header_hex'],'wire_sha256':r['payload_sha256'],'authority':'Recovered original-client DATA OUT; not a hardware-accepted default'})
probe=Path('${LOCAL_HOME}/Documents/Codex/2026-09-23/realtime-voice-chat/mesa-lab-fix/PROBE.WAV')
with wave.open(str(probe),'rb') as f:
 assert(f.getnchannels(),f.getsampwidth(),f.getframerate(),f.getnframes())==(1,2,44100,256);pcm=f.readframes(256)
for ar,seq in [('cap_import2',66),('cap_postpcm',66),('MESA_CAPTURE',153)]:
 r=next(r for r in load(ar)[0] if r['seq']==seq);assert bytes.fromhex(r['payload_hex'])==pcm;g.append({'kind':'pcm','archive':ar,'seq':seq,'wire_hex':r['payload_hex'],'cdb':r['cdb'],'wire_sha256':r['payload_sha256'],'source_pcm_equal':True})
(OUT/'captured-golden-vectors.json').write_text(json.dumps({'note':'Captured vectors supplement, not replace, synthetic boundary vectors. Inbound ACK/status vectors in transactions are synthetic target output.','vectors':g},indent=2)+'\n')
# Source-derived encoder comparison; no Bridge build or execution.
base=Path('${LOCAL_HOME}/Documents/Codex/2026-09-07/h/outputs/Akai-S2000-Bridge')
source=base/'src/Library/S2000InitializationTemplate.h';text=source.read_text();part=text.split('{{',1)[1].split('}}',1)[0];raw=bytes(int(x,16) for x in re.findall(r'0x([0-9a-fA-F]{2})',part));assert len(raw)==384;assert hashlib.sha256(raw).hexdigest()=='d87eb973fe8e19ba71b95e34f982e07caeeebaddc9267b319e2014fea553e988'
mp=bytes.fromhex(headers[1]['header_hex']);mk=bytes.fromhex(headers[2]['header_hex']);ms=bytes.fromhex(headers[0]['header_hex'])
# Apply only common template-name and pointer/count preparation so raw default differences are meaningful.
bp=bytearray(raw[:192]);bp[1:3]=b'\0\0';bp[3:15]=mp[3:15];bp[42]=1
bk=bytearray(raw[192:]);bk[1:3]=b'\0\0';bk[34:46]=mk[34:46];bk[132]=1
for z in range(4):bk[56+24*z:58+24*z]=b'\xff\xff'
bs=bytearray(192);bs[0:3]=bytes([3,1,60]);bs[3:15]=ms[3:15];bs[15]=128;bs[19]=2;struct.pack_into('<I',bs,26,256);struct.pack_into('<I',bs,34,255);struct.pack_into('<H',bs,136,65535);struct.pack_into('<H',bs,138,44100)
fields=list(csv.DictReader((OUT/'documentary-header-fields.csv').open()));diffs=[]
for obj,m,b in [('program',mp,bp),('keygroup',mk,bk),('sample',ms,bs)]:
 for i,(a,c) in enumerate(zip(m,b)):
  if a!=c:
   ff=[r['parameter'] for r in fields if r['object']==obj and int(r['offset_decimal'])<=i<int(r['offset_decimal'])+int(r['size_bytes'])]
   diffs.append({'object':obj,'offset':i,'mesa':a,'bridge_prepared_or_derived':c,'documentary_fields':';'.join(ff),'classification':'Confirmed byte difference; hardware rejection not established. Program/keygroup: normalized approved-template comparison, not an executed Bridge snapshot. Sample: source-derived encodeSample(PROBE,256-frame PCM).'} )
with (OUT/'bridge-default-differences.csv').open('w') as f:
 w=csv.DictWriter(f,fieldnames=list(diffs[0]));w.writeheader();w.writerows(diffs)
for obj in ['program','keygroup','sample']:
 d=[x for x in diffs if x['object']==obj];print(obj,len(d),'differences',[(x['offset'],x['mesa'],x['bridge_prepared_or_derived'],x['documentary_fields']) for x in d])
reg=json.loads((OUT/'evidence/source-register.json').read_text());ids={x['id'] for x in reg['sources']}
new=[('B05',source),('B06',base/'docs/HDA_INITIALIZATION_EXPORT.md')]+[(f'C{i+1:02}',ROOT/ar/'TRACE.TXT') for i,ar in enumerate(['cap_import1','cap_import2','cap_postpcm','cap_program','cap_kg','cap_final','cap_range','MESA_CAPTURE'])]+[('C09',ROOT/'recovery-manifest.json')]
for key,p in new:
 b=p.read_bytes();entry={'id':key,'path':str(p.resolve()),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest(),'authority':'Existing source/reference' if key.startswith('B') else 'Recovered historical client capture; synthetic target'}
 reg['sources']=[x for x in reg['sources'] if x['id']!=key];reg['sources'].append(entry)
reg['capture_recovery']=json.loads((ROOT/'recovery-manifest.json').read_text())['provenance'];reg['reconciliation']='See 05-capture-reconciliation.md; raw per-file provenance is recovered-captures/recovery-manifest.json. C identifiers are local register IDs, not REA IDs.'
(OUT/'evidence/source-register.json').write_text(json.dumps(reg,indent=2)+'\n')
print('transactions',len(trans),'captured golden vectors',len(g),'PCM_SHA256',hashlib.sha256(pcm).hexdigest())
