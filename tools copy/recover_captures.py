from pathlib import Path
import struct,os,hashlib,json,shutil
SRC=Path('${LOCAL_HOME}/Library/Containers/com.utmapp.UTM/Data/Documents/Windows.utm/Data/1FD07E86-5695-4BC4-A72B-DA61BE76CAF5.qcow2')
COPY=Path('work/Windows-capture-recovery.qcow2')
def sha(p):
 h=hashlib.sha256()
 with p.open('rb') as f:
  for b in iter(lambda:f.read(1024*1024),b''):h.update(b)
 return h.hexdigest()
if not COPY.exists():
 before=SRC.stat();shutil.copyfile(SRC,COPY);after=SRC.stat()
 assert (before.st_size,before.st_mtime_ns)==(after.st_size,after.st_mtime_ns),'Source changed during copy'
 digest=sha(SRC);assert digest==sha(COPY)
 Path('work/disk-provenance.json').write_text(json.dumps({'source':str(SRC),'copy':str(COPY.resolve()),'sha256':digest,'size':before.st_size,'mtime_ns':before.st_mtime_ns,'copy_verified':True},indent=2))
class QCOW:
 def __init__(self,p):
  self.f=open(p,'rb');b=self.f.read(112);assert b[:4]==b'QFI\xfb'
  self.bits,self.size,crypt,n,o=struct.unpack_from('>IQIIQ',b,20);assert crypt==0
  assert struct.unpack_from('>Q',b,8)[0]==0,'Backing file not supported'
  assert struct.unpack_from('>Q',b,72)[0]==0,'Unsupported incompatible features'
  self.cs=1<<self.bits;self.l2n=self.cs//8;self.mask=0x00fffffffffffe00
  self.f.seek(o);self.l1=struct.unpack('>'+str(n)+'Q',self.f.read(8*n));self.cache={}
 def read(self,o,n):
  assert 0<=o<=o+n<=self.size
  out=bytearray()
  while n:
   cluster=o//self.cs;within=o%self.cs;take=min(n,self.cs-within);a=cluster//self.l2n;j=cluster%self.l2n;l1=self.l1[a]&self.mask
   if l1:
    if l1 not in self.cache:
     self.f.seek(l1);self.cache[l1]=struct.unpack('>'+str(self.l2n)+'Q',self.f.read(self.cs))
    e=self.cache[l1][j];assert not (e&(1<<62)),'Compressed cluster requires separate decoder'
    off=e&self.mask
   else:e=off=0
   if not off or e&1:out.extend(bytes(take))
   else:self.f.seek(off+within);b=self.f.read(take);assert len(b)==take;out.extend(b)
   o+=take;n-=take
  return bytes(out)
class FAT:
 def __init__(self,d,base):
  self.d=d;self.base=base;b=d.read(base,512);self.bps=struct.unpack_from('<H',b,11)[0];self.spc=b[13];r,nf,re=struct.unpack_from('<HBH',b,14);fs16=struct.unpack_from('<H',b,22)[0];self.fs=fs16 or struct.unpack_from('<I',b,36)[0];self.fat=base+r*self.bps;self.data=base+(r+nf*self.fs+(re*32+self.bps-1)//self.bps)*self.bps;self.cs=self.bps*self.spc;self.root=struct.unpack_from('<I',b,44)[0] if not fs16 else None;assert self.root is not None,'Only FAT32 admitted'
  self.ft=d.read(self.fat,self.fs*self.bps);self.dirs={}
 def chain(self,c):
  seen=set()
  while 2<=c<0x0ffffff8:
   assert c not in seen,'FAT cycle';seen.add(c);yield c;c=struct.unpack_from('<I',self.ft,4*c)[0]&0xfffffff
 def datafor(self,c):return b''.join(self.d.read(self.data+(x-2)*self.cs,self.cs) for x in self.chain(c))
 def entries(self,c):
  b=self.datafor(c);lfn=[];out=[]
  for at in range(0,len(b),32):
   e=b[at:at+32]
   if e[0]==0:break
   if e[0]==0xe5:lfn=[];continue
   if e[11]==15:
    chars=e[1:11]+e[14:26]+e[28:32];lfn.append((e[0]&31,chars));continue
   short=e[:8].decode('cp437').rstrip();ext=e[8:11].decode('cp437').rstrip();sn=short+('.'+ext if ext else '')
   if lfn:
    name=b''.join(x[1] for x in sorted(lfn)).decode('utf-16le').split('\0')[0].rstrip('\uffff')
   else:name=sn
   lfn=[]
   if e[11]&8 or name in ('.','..'):continue
   cluster=(struct.unpack_from('<H',e,20)[0]<<16)|struct.unpack_from('<H',e,26)[0];size=struct.unpack_from('<I',e,28)[0]
   out.append({'name':name,'short':sn,'directory':bool(e[11]&16),'cluster':cluster,'size':size,'raw_entry_hex':e.hex()})
  return out
 def file(self,e):return self.datafor(e['cluster'])[:e['size']] if e['size'] else b''
if __name__=='__main__':
 d=QCOW(COPY);m=d.read(0,512);parts=[]
 for i in range(4):
  e=m[446+16*i:462+16*i];start,count=struct.unpack_from('<II',e,8)
  if e[4]:parts.append({'type':hex(e[4]),'start_lba':start,'sectors':count})
 print('partitions',parts);fat=FAT(d,parts[0]['start_lba']*512);root=fat.entries(fat.root);print('FAT',fat.bps,fat.spc,'root',fat.root);print('root',[(e['name'],e['directory'],e['size']) for e in root]);Path('work/fat-root.json').write_text(json.dumps(root,indent=2))
