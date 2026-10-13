from pathlib import Path
import json,hashlib
out=Path('outputs')
def u14(n):
 if not 0<=n<=16383:raise ValueError(n)
 return bytes([n&127,n>>7])
def nibbles(b):return bytes(v for x in b for v in [x&15,x>>4])
def cdb(op,n,bulk=False):
 if not 0<=n<=0xffffff:raise ValueError(n)
 return bytes([op,0,(n>>16)&255,(n>>8)&255,n&255,128 if bulk else 0])
def head(op,i,h,k=None):
 return bytes([240,71,0,op,72])+u14(i)+(bytes([k]) if k is not None else b'')+nibbles(h)+b'\xf7'
def vector(name,b,**kw):return dict(name=name,bytes=len(b),hex=b.hex(),sha256=hashlib.sha256(b).hexdigest(),**kw)
h=bytes(range(192));vectors=[]
for name,op,i,k,t in [('pdata128',7,128,None,1),('kdata255_group0',9,255,0,2),('sdata_sample1',11,1,None,3)]:
 raw=bytes([t])+h[1:];b=head(op,i,raw,k);off=8 if k is not None else 7
 assert len(b)==(393 if k is not None else 392)
 assert bytes(b[off+2*j]|(b[off+2*j+1]<<4) for j in range(192))==raw
 assert b[5:7]==({'pdata128':b'\x00\x01','kdata255_group0':b'\x7f\x01','sdata_sample1':b'\x01\x00'}[name])
 vectors.append(vector(name,b,raw_header_hex=raw.hex(),note='Synthetic codec fixture: typed incrementing byte pattern, intentionally not a valid playable default header.'))
for name,b,expected in [('send392',cdb(12,392),'0c0000018800'),('send393',cdb(12,393),'0c0000018900'),('pcm512',cdb(12,512,True),'0c0000020080'),('pcm32768',cdb(12,32768,True),'0c0000800080'),('pcm2',cdb(12,2,True),'0c0000000280'),('receiveAck7',cdb(14,7),'0e0000000700')]:
 assert b.hex()==expected;vectors.append(vector(name,b))
for name,hexval in [('modeBulk','090001010000'),('modeMidi','090001000000'),('modeNormal','090000000000'),('statusOrdinary','0d0000000000'),('statusBulk','0d0000000080'),('postObject1','f04700344801000000000000f7'),('replyOk','f04700164800f7'),('replyError','f04700164801f7'),('rstat','f047000048f7'),('rplist','f047000248f7'),('rslist','f047000448f7'),('rpdataOrdinal1','f0470006480100f7'),('rkdataOrdinal1Group0','f047000848010000f7'),('rsdataOrdinal1','f047000a480100f7')]:vectors.append(vector(name,bytes.fromhex(hexval)))
alphabet='0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ#+-.';assert len(alphabet)==41
names=[{'text':n,'hex':bytes([alphabet.index(c) for c in n]+[10]*(12-len(n))).hex()} for n in ['PROBE','PROGPROBE']]
chunks=[]
for size in [2,512,32766,32768,32770,65536,65538]:
 parts=[];at=0
 while at<size:
  n=min(32768,size-at);parts.append({'offset_bytes':at,'length_bytes':n,'cdb_hex':cdb(12,n,True).hex()});at+=n
 assert sum(p['length_bytes'] for p in parts)==size and all(p['length_bytes']%2==0 for p in parts)
 chunks.append({'pcm_bytes':size,'frames':size//2,'blocks':parts})
(out/'golden-vectors.json').write_text(json.dumps({'purpose':'Offline wire codec vectors. No hardware execution. Header byte patterns are synthetic codec fixtures, not MESA capture bytes or validated S2000 defaults.','address':0,'vectors':vectors,'encoded_names':names,'mono_chunk_schedules':chunks},indent=2)+'\n')
print('Validated',len(vectors),'vectors and',len(chunks),'even-byte chunk schedules')
