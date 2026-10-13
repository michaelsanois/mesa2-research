from pathlib import Path
import hashlib,json,re,csv,sys,shutil
sys.path.insert(0,'work');from pe_view import PE
out=Path('outputs');ev=out/'evidence';ev.mkdir(exist_ok=True)
roots=Path('${LOCAL_HOME}/Documents/Codex')
prior=roots/'2026-09-23/realtime-voice-chat'
register={
'H01':prior/'MESA-UPLOAD-FINDINGS.md','H02':prior/'MESA-verification-20261007.md','H03':prior/'mesa-lab-fix/MESA-effects-audit.md',
'H04':roots/'mesa-re/notes/loader-audit-20261007.md','H05':roots/'mesa-re/README.md',
'H06':roots/'bridge-scsi/RESIDENT_PCM_AUDIT.md','H07':roots/'bridge-scsi/V23B-COMPATIBILITY-ASSESSMENT.md',
'D01':roots/'2026-09-06/you-are-building-a-native-macos/work/parameter-sources/s1000_sysex.html',
'D02':roots/'2026-09-06/you-are-building-a-native-macos/work/parameter-sources/s2800_sysex.html',
'D03':roots/'2026-09-06/you-are-building-a-native-macos/work/parameter-sources/s2000_sysex.html',
'D04':roots/'2026-09-06/you-are-building-a-native-macos/docs/S2000_PROTOCOL_SOURCES.md',
'L01':roots/'2026-09-06/you-are-building-a-native-macos/work/protocol-verification/lakai-0.1.orig/lakai.c',
'F01':prior/'mesa-lab-fix/fake_aspi.c','F02':prior/'mesa-lab-fix/PROBE.WAV',
'B01':roots/'2026-09-07/h/outputs/Akai-S2000-Bridge/src/S2000/AkaiTransport.h',
'B02':roots/'2026-09-07/h/outputs/Akai-S2000-Bridge/src/S2000/AkaiHardwareRequestQueue.h',
'B03':roots/'2026-09-07/h/outputs/Akai-S2000-Bridge/src/Library/AkaiSliceHdaExport.h',
'B04':roots/'2026-09-07/h/outputs/Akai-S2000-Bridge/src/Library/AkaiHdaWriter.h',
'A01':Path('${LOCAL_HOME}/Downloads/MESA.ISO'),'A02':roots/'mesa-re/mesa/installer/DPSSETUP.MSI',
'A03':roots/'mesa-re/mesa/payload/SCSIPlug.dll','A04':Path('work/MESASAMPLER.dll').resolve()}
rows=[]
for k,p in register.items():
 b=p.read_bytes();entry={'id':k,'path':str(p),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()};rows.append(entry)
 if k.startswith('H') or k=='D04':shutil.copyfile(p,ev/(k+'-'+p.name))
(ev/'source-register.json').write_text(json.dumps({'date':'2026-10-13','method':'Offline local files; no target execution. H IDs are historical analyst reports, D documentary sources, L secondary source, F synthetic fixtures, B implementation, A artifacts. Local IDs are not REA Evidence IDs.','sources':rows},indent=2)+'\n')
ranges={
'SCSIPlug':[(0x100010e0,0x10001191),(0x10001240,0x10001480),(0x10001490,0x100014e3),(0x100027e0,0x1000292c),(0x10002990,0x10002a4b),(0x10002a60,0x10002b54),(0x10002b60,0x10002c9a),(0x10002ca0,0x10002dd2),(0x10003390,0x100033b1),(0x100035e0,0x1000366a)],
'MESASAMPLER':[(0x10003ba0,0x10003be3),(0x10003c30,0x10003c68),(0x10003cc0,0x10003d09),(0x10003d10,0x10003f04),(0x10006480,0x1000655f),(0x100065b3,0x1000660b),(0x10007390,0x100075c3),(0x100075d0,0x100077f5),(0x10008b00,0x10008ef7),(0x1000a040,0x1000a2a4),(0x1000a2b0,0x1000a536)]}
for name,rs in ranges.items():
 lines=Path('work/'+name+'.asm').read_text().splitlines();p=PE(register['A03' if name=='SCSIPlug' else 'A04']);parts=['# '+name+' static disassembly excerpts','\nSource identity: '+next(x['sha256'] for x in rows if x['id']==('A03' if name=='SCSIPlug' else 'A04')),'\nTool: /usr/bin/objdump -d --x86-asm-syntax=intel. Preferred PE virtual addresses; inferred function boundaries, no execution or decompiler. Data/jump tables can be decoded as instructions in linear output; do not treat them as executable facts.']
 for start,end in rs:
  parts+=['\n## '+hex(start)+'–'+hex(end),'\nFile start offset: '+hex(p.offset(start))+'\n','```asm']
  for l in lines:
   m=re.match(r'([0-9a-f]+):',l)
   if m and start<=int(m[1],16)<=end:parts.append(l)
  parts.append('```')
 (ev/(name+'-excerpts.md')).write_text('\n'.join(parts)+'\n')
p=PE(register['A04']);data={'classification':'Static MESA embedded initialization templates. Names are ASCII here, converted before transmission. These are not physical S2000 defaults.','program':{'address':'0x10057b1c','bytes_hex':p.read(0x10057b1c,192).hex()},'keygroup':{'address':'0x10057a38','bytes_hex':p.read(0x10057a38,192).hex()},'alphabet':p.read(0x10056f60,41).decode(),'sampler_vtable':{'address':'0x100578b0','entries':{hex(o):hex(p.words(0x100578b0+o,1)[0]) for o in [0x104,0x108,0x13c,0x150,0x154,0xc4,0xc8]}},'upload_vtable':{'address':'0x10005288','entries':{hex(o):hex(PE(register['A03']).words(0x10005288+o,1)[0]) for o in [0x28,0x3c,0x40,0x44,0x48]}}}
(ev/'static-data.json').write_text(json.dumps(data,indent=2)+'\n')
# Exact documentary field map, preserving the applicability caveat for every row.
txt=Path('work/s2800-reference.txt').read_text();matches=list(re.finditer(r'Parameter:\s*([^\n]+)\s*\n+Offset:\s*(\d+)\s+bytes?\s*\n+Field size:\s*(\d+)\s+bytes?\s*\n+Range:\s*([^\n]*)\n+Description:\s*([^\n]+)',txt))
with (out/'documentary-header-fields.csv').open('w') as f:
 w=csv.writer(f);w.writerow(['object','parameter','offset_decimal','size_bytes','range_verbatim','description_verbatim','evidence','applicability'])
 for m in matches:
  before=txt[:m.start()];heads=[(before.rfind('Structure of S3000 Program Header'),'program'),(before.rfind('Accessing Keygroup Header bytes'),'keygroup'),(before.rfind('Structure of S3000 Sample header'),'sample')];at,obj=max(heads)
  if at<0:continue
  w.writerow([obj,m[1].strip(),m[2],m[3],m[4].strip(),m[5].strip(),'D02','Documentary S3000-family layout; S2000 firmware applicability requires field-specific validation. Not a write allowlist.'])
print('Sources:',len(rows),'Documentary fields:',len(matches))
