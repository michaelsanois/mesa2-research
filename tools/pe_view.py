from pathlib import Path
import struct,sys
class PE:
 def __init__(self,p):
  self.b=Path(p).read_bytes();o=struct.unpack_from('<I',self.b,0x3c)[0];n=struct.unpack_from('<H',self.b,o+6)[0];s=struct.unpack_from('<H',self.b,o+20)[0];self.base=struct.unpack_from('<I',self.b,o+24+28)[0];self.sections=[]
  for i in range(n):
   q=o+24+s+40*i;name=self.b[q:q+8].rstrip(b'\0').decode();vs,va,rs,rp=struct.unpack_from('<4I',self.b,q+8);self.sections.append((name,va,vs,rp,rs))
 def offset(self,a):
  for name,va,vs,rp,rs in self.sections:
   if va<=a-self.base<va+rs:return rp+a-self.base-va
  raise ValueError(hex(a))
 def read(self,a,n):o=self.offset(a);return self.b[o:o+n]
 def words(self,a,n):return struct.unpack('<'+'I'*n,self.read(a,n*4))
if __name__=='__main__':
 p=PE(sys.argv[1]);a=int(sys.argv[2],16);n=int(sys.argv[3]);print(p.sections);print('file_offset',hex(p.offset(a)));print(p.read(a,n).hex());print([hex(x) for x in p.words(a,n//4)])
