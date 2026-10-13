from recover_captures import *
d=QCOW(COPY);fat=FAT(d,63*512);root=fat.entries(fat.root);out=Path('outputs/recovered-captures');out.mkdir(exist_ok=True);records=[]
selected=['cap_import1','cap_import2','cap_postpcm','cap_program','cap_kg','cap_final','cap_range','MESA_CAPTURE']
def extract(e,path):
 assert '/' not in e['name'] and '\\' not in e['name']
 dest=out/path
 if e['directory']:
  dest.mkdir(exist_ok=True)
  for x in fat.entries(e['cluster']):extract(x,path/x['name'])
 else:
  b=fat.file(e);assert len(b)==e['size'];dest.write_bytes(b)
  records.append({'guest_path':'C:\\'+str(path).replace('/','\\'),'path':str(dest),'sha256':hashlib.sha256(b).hexdigest(),'size':len(b),'cluster':e['cluster'],'raw_directory_entry_hex':e['raw_entry_hex']})
for name in selected:
 es=[e for e in root if e['name'].casefold()==name.casefold()];assert len(es)==1;extract(es[0],Path(name))
for name in ['WAVPCM.BIN','sentpcm.bin','prog.bin','kg.bin','final.bin','upload.bin']:
 e=next(e for e in root if e['name'].lower()==name.lower());(out/'guest-scratch').mkdir(exist_ok=True);extract(e,Path('guest-scratch')/name)
manifest={'provenance':json.loads(Path('work/disk-provenance.json').read_text()),'method':'Direct read-only QCOW2 v3 L1/L2 mapping and FAT32 parsing from a hash-verified local disk copy; no VM boot, mount, or execution. Only allocated files in named capture directories plus identified guest scratch were materialized.','partition_start_lba':63,'fat32':{'sector_bytes':fat.bps,'sectors_per_cluster':fat.spc,'root_cluster':fat.root},'files':records}
(out/'recovery-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print('extracted',len(records),'files',sum(x['size'] for x in records),'bytes')
for name in selected:
 rr=[x for x in records if x['guest_path'].startswith('C:\\'+name+'\\')];print(name,len(rr),sum(x['size'] for x in rr))
for p in out.rglob('*'):
 if p.name.lower()=='trace.txt':print(p, p.read_text(errors='replace')[:1800])
