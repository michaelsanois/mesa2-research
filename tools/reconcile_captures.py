from pathlib import Path
import json,collections,hashlib,struct
ROOT=Path('outputs/recovered-captures')
def load(name):
 p=ROOT/name;records=[json.loads(l) for l in (p/'TRACE.TXT').read_text().splitlines() if l.strip()];seq=collections.Counter(x['seq'] for x in records);issues=[]
 for r in records:
  f=r.get('payload_file');r['archive']=name
  if f:
   b=(p/f).read_bytes() if (p/f).exists() else None
   if b is None or len(b)!=r['payload_bytes']:issues.append({'seq':r['seq'],'issue':'payload absent/length mismatch','file':f,'actual_size':None if b is None else len(b)})
   elif seq[r['seq']]!=1:issues.append({'seq':r['seq'],'issue':'reused sequence; file association ambiguous'})
   else:r['payload_hex']=b.hex();r['payload_sha256']=hashlib.sha256(b).hexdigest()
 return records,issues,seq
if __name__=='__main__':
 allrows=[];summaries=[]
 for p in ROOT.iterdir():
  if not (p/'TRACE.TXT').exists():continue
  rows,issues,seq=load(p.name);allrows+=rows
  summary={'archive':p.name,'records':len(rows),'min_seq':min(seq),'max_seq':max(seq),'duplicate_seqs':[(k,v) for k,v in seq.items() if v>1],'issues':issues,'upload_records':[]}
  for r in rows:
   b=bytes.fromhex(r.get('payload_hex',''));c=r.get('cdb','').lower()
   if c.startswith('0c') and (c.endswith('80') or (len(b)>4 and b[3] in [7,9,11])):summary['upload_records'].append({'seq':r['seq'],'tick_ms':r['tick_ms'],'cdb':c,'bytes':len(b),'prefix':b[:9].hex()})
  summaries.append(summary);print(json.dumps(summary))
 Path('outputs/capture-integrity.json').write_text(json.dumps(summaries,indent=2)+'\n');Path('outputs/normalized-captures.json').write_text(json.dumps(allrows,indent=2)+'\n')
 for name,lo,hi in [('cap_import2',60,78),('cap_postpcm',60,78),('cap_final',55,80),('MESA_CAPTURE',55,95)]:
  rows,_,_=load(name);print('\nWINDOW',name)
  for r in rows:
   if lo<=r['seq']<=hi:print(r['seq'],r['tick_ms'],r.get('cdb'),r.get('direction'),r.get('requested'),r.get('payload_bytes'),r.get('payload_hex','')[:70])
