#include <windows.h>
#include <tlhelp32.h>
#include "aspi_abi.h"

typedef DWORD (__cdecl *GetInfoFn)(void);
typedef DWORD (__cdecl *SendCommandFn)(void *);

void *__cdecl memset(void *dst, int value, size_t count)
{
    BYTE *p=(BYTE *)dst; size_t i; for(i=0;i<count;i++) p[i]=(BYTE)value; return dst;
}

static char *append(char *p, const char *s) { while (*s) *p++ = *s++; *p = 0; return p; }
static char *append_num(char *p, DWORD n)
{
    char tmp[10]; unsigned i=0;
    do { tmp[i++]=(char)('0'+n%10); n/=10; } while(n && i<sizeof(tmp));
    while(i) *p++=tmp[--i]; *p=0; return p;
}


/* Read-only loader audit: no SCSI, MIDI or registry writes. */
static int audit_modules(void)
{
    HANDLE ps, ms, out; PROCESSENTRY32 pe; MODULEENTRY32 me;
    DWORD wrote; char line[1200], *p; BOOL found=FALSE;
    CreateDirectoryA("C:\\MESA_CAPTURE",NULL);
    out=CreateFileA("C:\\MESA_CAPTURE\\MODULES.TXT",GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(out==INVALID_HANDLE_VALUE) return 3;
    ps=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    ZeroMemory(&pe,sizeof(pe)); pe.dwSize=sizeof(pe);
    if(ps!=INVALID_HANDLE_VALUE && Process32First(ps,&pe)) do {
        p=line; p=append(p,"PROCESS "); p=append_num(p,pe.th32ProcessID); p=append(p," "); p=append(p,pe.szExeFile); p=append(p,"\r\n");
        WriteFile(out,line,(DWORD)(p-line),&wrote,NULL);
        ms=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pe.th32ProcessID);
        ZeroMemory(&me,sizeof(me)); me.dwSize=sizeof(me);
        if(ms!=INVALID_HANDLE_VALUE && Module32First(ms,&me)) do {
            p=line; p=append(p,"  "); p=append(p,me.szModule); p=append(p," => "); p=append(p,me.szExePath); p=append(p,"\r\n");
            WriteFile(out,line,(DWORD)(p-line),&wrote,NULL); found=TRUE;
        } while(Module32Next(ms,&me));
        if(ms!=INVALID_HANDLE_VALUE) CloseHandle(ms);
    } while(Process32Next(ps,&pe));
    if(ps!=INVALID_HANDLE_VALUE) CloseHandle(ps); CloseHandle(out);
    MessageBoxA(NULL,found ? "Loader audit saved to C:\\MESA_CAPTURE\\MODULES.TXT" : "No modules enumerated. See MODULES.TXT.","ASPI loader audit (no hardware)",MB_OK);
    return found?0:4;
}

static int regression_tests(void)
{
    HMODULE dll=LoadLibraryA("WNASPI32.DLL"); SendCommandFn send;
    ASPI_EXEC_SCSI s; BYTE buf[36]; HANDLE event; DWORD rc; int failures=0;
    if(!dll) return 20;
    send=(SendCommandFn)GetProcAddress(dll,(LPCSTR)2);
    if(!send){FreeLibrary(dll);return 21;}
    event=CreateEventA(NULL,TRUE,FALSE,NULL);
    if(!event){FreeLibrary(dll);return 22;}
    ZeroMemory(&s,sizeof(s)); memset(buf,0xaa,sizeof(buf));
    s.cmd=2;s.target=0;s.flags=SRB_DIR_IN|SRB_EVENT_NOTIFY;
    s.buffer=buf;s.buffer_length=36;s.cdb_length=6;s.cdb[0]=0x12;s.cdb[4]=36;
    s.post_proc=(DWORD)(ULONG_PTR)event;
    rc=send(&s);
    if(rc!=SS_NO_DEVICE||s.status!=SS_NO_DEVICE||s.ha_status!=0) ++failures;
    {unsigned i;for(i=0;i<36;i++) if(buf[i]!=0){++failures;break;}}
    if(WaitForSingleObject(event,0)!=WAIT_OBJECT_0) ++failures;
    ResetEvent(event);s.target=2;rc=send(&s);
    if(rc!=SS_COMP||s.status!=SS_COMP||s.ha_status!=0||buf[0]!=3||buf[8]!='A'||buf[16]!='S') ++failures;
    if(WaitForSingleObject(event,0)!=WAIT_OBJECT_0) ++failures;
    ResetEvent(event);s.buffer_length=16u*1024u*1024u+1u;rc=send(&s);
    if(rc!=SS_ERR||s.status!=SS_ERR) ++failures;
    if(WaitForSingleObject(event,0)!=WAIT_OBJECT_0) ++failures;
    { BYTE request[8]={0xf0,0x47,0,0x0a,0x48,0,0,0xf7}, status[3], reply[392];
      ZeroMemory(&s,sizeof(s));s.cmd=2;s.target=2;s.cdb_length=6;
      s.flags=SRB_DIR_OUT;s.cdb[0]=0x0c;s.cdb[4]=8;s.buffer=request;s.buffer_length=8;
      if(send(&s)!=SS_COMP)++failures;
      s.flags=SRB_DIR_IN;s.cdb[0]=0x0d;s.cdb[4]=0;s.buffer=status;s.buffer_length=3;
      if(send(&s)!=SS_COMP||status[0]!=0||status[1]!=1||status[2]!=136)++failures;
      if(send(&s)!=SS_COMP||status[1]!=1||status[2]!=136)++failures;
      s.cdb[0]=0x0e;s.cdb[3]=1;s.cdb[4]=136;s.buffer=reply;s.buffer_length=392;
      if(send(&s)!=SS_COMP||reply[0]!=0xf0||reply[3]!=0x0b||reply[7]!=3||reply[391]!=0xf7)++failures;
      s.cdb[0]=0x0d;s.cdb[3]=s.cdb[4]=0;s.buffer=status;s.buffer_length=3;
      if(send(&s)!=SS_COMP||status[0]||status[1]||status[2])++failures;
      s.cdb[0]=0x0e;s.cdb[4]=1;s.buffer_length=1;
      if(send(&s)!=SS_ERR)++failures;
    }
    { BYTE request[8]={0xf0,0x47,0,0x06,0x48,0,0,0xf7}, reply[392];
      ZeroMemory(&s,sizeof(s));s.cmd=2;s.target=2;s.cdb_length=6;
      s.flags=SRB_DIR_OUT;s.cdb[0]=0x0c;s.cdb[4]=8;s.buffer=request;s.buffer_length=8;
      if(send(&s)!=SS_COMP)++failures;
      s.flags=SRB_DIR_IN;s.cdb[0]=0x0e;s.cdb[3]=1;s.cdb[4]=136;s.buffer=reply;s.buffer_length=392;
      if(send(&s)!=SS_COMP||reply[3]!=0x07||reply[7]!=1||reply[91]!=1||reply[391]!=0xf7)++failures;
    }
    { BYTE request[15]={0xf0,0x47,0,0x34,0x48,0x0b,0,1,0,0,1,0,5,0,0xf7},reply[7];
      ZeroMemory(&s,sizeof(s));s.cmd=2;s.target=2;s.cdb_length=6;
      s.flags=SRB_DIR_OUT;s.cdb[0]=0x0c;s.cdb[4]=15;s.buffer=request;s.buffer_length=15;
      if(send(&s)!=SS_COMP)++failures;
      s.flags=SRB_DIR_IN;s.cdb[0]=0x0e;s.cdb[4]=7;s.buffer=reply;s.buffer_length=7;
      if(send(&s)!=SS_COMP||reply[3]!=0x16||reply[5]!=0||reply[6]!=0xf7)++failures;
    }
    { BYTE request[6]={0xf0,0x47,0,0,0x48,0xf7},reply[21];
      ZeroMemory(&s,sizeof(s));s.cmd=2;s.target=2;s.cdb_length=6;
      s.flags=SRB_DIR_OUT;s.cdb[0]=0x0c;s.cdb[4]=6;s.buffer=request;s.buffer_length=6;
      if(send(&s)!=SS_COMP)++failures;
      s.flags=SRB_DIR_IN;s.cdb[0]=0x0e;s.cdb[4]=21;s.buffer=reply;s.buffer_length=21;
      if(send(&s)!=SS_COMP||reply[3]!=1||reply[6]!=2||reply[20]!=0xf7)++failures;
    }
    { BYTE request[9]={0xf0,0x47,0,8,0x48,0,0,0,0xf7},reply[393];
      ZeroMemory(&s,sizeof(s));s.cmd=2;s.target=2;s.cdb_length=6;
      s.flags=SRB_DIR_OUT;s.cdb[0]=0x0c;s.cdb[4]=9;s.buffer=request;s.buffer_length=9;
      if(send(&s)!=SS_COMP)++failures;
      s.flags=SRB_DIR_IN;s.cdb[0]=0x0e;s.cdb[3]=1;s.cdb[4]=137;s.buffer=reply;s.buffer_length=393;
      if(send(&s)!=SS_COMP||reply[3]!=9||reply[8]!=2||reply[392]!=0xf7)++failures;
    }
    CloseHandle(event);FreeLibrary(dll);
    MessageBoxA(NULL, failures ? "FAIL: synthetic ASPI regression" :
        "PASS: absent ID status, cleared buffer, ID 2 inquiry, oversized request rejection, completion events; queued sample header, status, exact receive and drained-queue rejection.",
        "Synthetic ASPI regression (no hardware)",MB_OK);
    return failures?23:0;
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE prev, LPSTR cmd, int show)
{
    HMODULE dll; GetInfoFn get_info; SendCommandFn send_cmd;
    DWORD info, gdev_rc, exec_rc; char msg[512], *p=msg; DWORD i;
    ASPI_GET_DEVICE_TYPE g; ASPI_EXEC_SCSI s; ASPI_HA_INQUIRY ha; BYTE inq[36];
    (void)h;(void)prev;(void)cmd;(void)show;
    if (cmd) { const char *q=cmd; while (*q) { if (lstrcmpiA(q,"/modules")==0) return audit_modules(); if(lstrcmpiA(q,"/tests")==0) return regression_tests(); ++q; } }
    dll=LoadLibraryA("WNASPI32.DLL");
    if(!dll){ MessageBoxA(NULL,"Could not load WNASPI32.DLL from this folder.","ASPI Probe",MB_OK|MB_ICONERROR); return 1; }
    get_info=(GetInfoFn)GetProcAddress(dll,(LPCSTR)1);
    send_cmd=(SendCommandFn)GetProcAddress(dll,(LPCSTR)2);
    if(!get_info||!send_cmd){ MessageBoxA(NULL,"DLL loaded, but ASPI ordinal 1 or 2 is missing.","ASPI Probe",MB_OK|MB_ICONERROR); FreeLibrary(dll); return 2; }
    info=get_info();
    p=append(p,"GetASPI32SupportInfo = 0x");
    { static const char hex[]="0123456789ABCDEF"; *p++=hex[(info>>12)&15]; *p++=hex[(info>>8)&15]; *p++=hex[(info>>4)&15]; *p++=hex[info&15]; *p=0; }
    p=append(p,"\r\nAdapters (high byte): "); p=append_num(p,(info>>8)&255);
    p=append(p,"\r\nStatus (low byte): "); p=append_num(p,info&255);
    ZeroMemory(&ha,sizeof(ha)); ha.cmd=SC_HA_INQUIRY; send_cmd(&ha);
    p=append(p,"\r\nHA status/target-scan bound: "); p=append_num(p,ha.status); *p++='/'; p=append_num(p,ha.unique[3]);
    ZeroMemory(&g,sizeof(g)); g.cmd=SC_GET_DEV_TYPE; g.ha_id=0; g.target=2; g.lun=0;
    gdev_rc=send_cmd(&g);
    p=append(p,"\r\nID 2 GDEV return/status/type: "); p=append_num(p,gdev_rc); *p++='/'; p=append_num(p,g.status); *p++='/'; p=append_num(p,g.device_type);
    ZeroMemory(&s,sizeof(s)); ZeroMemory(inq,sizeof(inq));
    s.cmd=SC_EXEC_SCSI_CMD; s.ha_id=0; s.target=2; s.lun=0; s.flags=SRB_DIR_IN;
    s.buffer_length=sizeof(inq); s.buffer=inq; s.cdb_length=6; s.cdb[0]=0x12; s.cdb[4]=sizeof(inq);
    exec_rc=send_cmd(&s);
    p=append(p,"\r\nINQUIRY return/SRB/host/target: "); p=append_num(p,exec_rc); *p++='/'; p=append_num(p,s.status); *p++='/'; p=append_num(p,s.ha_status); *p++='/'; p=append_num(p,s.target_status);
    p=append(p,"\r\nVendor: "); for(i=8;i<16;i++) *p++=inq[i]; *p=0;
    p=append(p,"\r\nProduct: "); for(i=16;i<32;i++) *p++=inq[i]; *p=0;
    MessageBoxA(NULL,msg,"Synthetic ASPI diagnostic (no hardware)",MB_OK|MB_ICONINFORMATION);
    FreeLibrary(dll); return 0;
}

void WINAPI ProbeEntry(void)
{
    int rc=WinMain(GetModuleHandleA(NULL),NULL,GetCommandLineA(),SW_SHOWDEFAULT);
    ExitProcess((UINT)rc);
}
