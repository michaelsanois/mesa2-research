#include <assert.h>
#include <stdint.h>
#include <stdio.h>
typedef uint8_t BYTE; typedef uint32_t DWORD;
static BYTE g_reply[1037];
static DWORD g_reply_size, g_reply_offset;
static BYTE g_uploaded_header[192];
static DWORD g_uploaded_header_valid;
static BYTE g_uploaded_keygroup[192];
static DWORD g_uploaded_keygroup_valid;
static BYTE g_uploaded_program[192];
static DWORD g_uploaded_program_valid;
static BYTE g_uploaded_pcm[512];
static DWORD g_uploaded_pcm_valid;
static void queue_header_reply(const BYTE *request, DWORD size)
{
    BYTE header[192]; DWORD i;
    g_reply_size = g_reply_offset = 0;
    /* Captured explorer S3RPDATA27 reads offsets16 (seq128) and15
     * (RANGE_LAB seq109). Serve validated ranges from the SAME legacy
     * program fixture/model. Only the two existing lab slots are allowed.
     * Synthetic replies establish client behavior, not hardware acceptance. */
    if(size==13 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0x27 && request[4]==0x48 && request[6]==0 &&
       request[7]==0 && request[12]==0xf7){
        DWORD offset,count; BYTE legacy[8]={0xf0,0x47,0,6,0x48,0,0,0xf7};
        for(i=5;i<12;++i)if(request[i]>127)return;
        offset=request[8]+128u*request[9];count=request[10]+128u*request[11];
        if(request[5]>1 || !count || offset>=192 || count>192-offset)return;
        if(request[5]==1 && !g_uploaded_program_valid)return;
        legacy[5]=request[5];queue_header_reply(legacy,8);
        if(g_reply_size!=392){g_reply_size=g_reply_offset=0;return;}
        for(i=0;i<count;++i)header[i]=g_reply[7+2*(offset+i)]|(g_reply[8+2*(offset+i)]<<4);
        for(i=0;i<12;++i)g_reply[i]=request[i];g_reply[3]=0x28;
        for(i=0;i<count;++i){g_reply[12+2*i]=header[i]&15;g_reply[13+2*i]=header[i]>>4;}
        g_reply_size=13+2*count;g_reply[g_reply_size-1]=0xf7;g_reply_offset=0;return;
    }
    /* Original MESA seq129: PDATA, identifier00/01,192 nibbled bytes.
     * Identifier decodes128 in Lakai's 7-bit encoding; allocation semantics
     * are NOT established. Exact bounded lab slot only, synthetic ACK. */
    if(size==392 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==7 && request[4]==0x48 && request[5]==0 &&
       request[6]==1 && request[391]==0xf7){
        for(i=0;i<192;++i){
            if(request[7+2*i]>15 || request[8+2*i]>15)return;
            header[i]=request[7+2*i]|(request[8+2*i]<<4);
        }
        if(header[0]!=1)return;
        for(i=0;i<192;++i)g_uploaded_program[i]=header[i];
        g_uploaded_program_valid=1;g_uploaded_keygroup_valid=0;
        {static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
         for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;}
    }
    if(size==8 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==6 && request[4]==0x48 && request[5]==0 &&
       request[6]==1 && request[7]==0xf7 && g_uploaded_program_valid){
        for(i=0;i<7;++i)g_reply[i]=request[i];g_reply[3]=7;
        for(i=0;i<192;++i){g_reply[7+2*i]=g_uploaded_program[i]&15;
                            g_reply[8+2*i]=g_uploaded_program[i]>>4;}
        g_reply[391]=0xf7;g_reply_size=392;return;
    }
    /* Captured KDATA09, previous-created-program255, KG0 only.
     * Lab allocation is slot1, not a claim about hardware allocation order. */
    if(size==393 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==9 && request[4]==0x48 && request[5]==127 &&
       request[6]==1 && request[7]==0 && request[392]==0xf7 && g_uploaded_program_valid){
        for(i=0;i<192;++i){
            if(request[8+2*i]>15 || request[9+2*i]>15)return;
            header[i]=request[8+2*i]|(request[9+2*i]<<4);
        }
        if(header[0]!=2)return;
        for(i=0;i<192;++i)g_uploaded_keygroup[i]=header[i];
        g_uploaded_keygroup_valid=1;
        {static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
         for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;}
    }
    if(size==9 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==8 && request[4]==0x48 && request[5]==1 &&
       request[6]==0 && request[7]==0 && request[8]==0xf7 && g_uploaded_keygroup_valid){
        for(i=0;i<8;++i)g_reply[i]=request[i];g_reply[3]=9;
        for(i=0;i<192;++i){g_reply[8+2*i]=g_uploaded_keygroup[i]&15;
                            g_reply[9+2*i]=g_uploaded_keygroup[i]>>4;}
        g_reply[392]=0xf7;g_reply_size=393;return;
    }
    if(size==8 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==6 && request[4]==0x48 && request[5]==1 &&
       request[6]==0 && request[7]==0xf7 && g_uploaded_program_valid){
        for(i=0;i<7;++i)g_reply[i]=request[i];g_reply[3]=7;
        for(i=0;i<192;++i){g_reply[7+2*i]=g_uploaded_program[i]&15;
                            g_reply[8+2*i]=g_uploaded_program[i]>>4;}
        g_reply[391]=0xf7;g_reply_size=392;return;
    }
    /* Isolated probe only: preserve all512 PCM bytes; never acknowledge a
     * post-transfer function before the complete bounded payload exists. */
    if(size==512 && g_uploaded_header_valid && request[0]!=0xf0){
        for(i=0;i<512;++i)g_uploaded_pcm[i]=request[i];
        g_uploaded_pcm_valid=1;return;
    }
    { static const BYTE post_pcm[13]={0xf0,0x47,0,0x34,0x48,1,0,0,0,0,0,0,0xf7};
      DWORD matches=size==13;
      if(matches)for(i=0;i<13;++i)if(request[i]!=post_pcm[i])matches=0;
      if(matches && ((g_uploaded_header_valid && g_uploaded_pcm_valid) ||
                     (g_uploaded_program_valid && g_uploaded_keygroup_valid))){
        /* MESA10006480 constructs bank0/zero-count functions;10006570
         * requires REPLY16/status0. Also observed after PDATA/KDATA seq68/tick48716269.
         * Meaning of function1 remains unknown.
         * This is synthetic client-acceptance evidence only. */
        static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
        for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;
      }
    }
    /* Exact startup write observed from MESA; isolated synthetic ACK only. */
    { static const BYTE startup[15]={0xf0,0x47,0,0x34,0x48,0x0b,0,1,0,0,1,0,5,0,0xf7};
      DWORD matches=size==15;
      if(matches)for(i=0;i<15;++i)if(request[i]!=startup[i])matches=0;
      if(matches){static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
        for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;}
    }

    /* Actual MESA import seq354/tick39693889: SDATA index1,192 bytes.
     * Store the header before synthetic ACK. This acknowledges metadata ONLY;
     * no PCM or complete upload is claimed. Bounded to the256-frame lab probe. */
    if(size==392 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0x0b && request[4]==0x48 && request[5]==1 &&
       request[6]==0 && request[391]==0xf7){
        for(i=0;i<192;++i){
            if(request[7+2*i]>15 || request[8+2*i]>15)return;
            header[i]=request[7+2*i]|(request[8+2*i]<<4);
        }
        if(header[0]!=3 || header[26]!=0 || header[27]!=1 ||
           header[28]!=0 || header[29]!=0)return;
        for(i=0;i<192;++i)g_uploaded_header[i]=header[i];
        g_uploaded_header_valid=1;g_uploaded_pcm_valid=0;
        {static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
         for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;}
    }
    if(size==8 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0x0a && request[4]==0x48 && request[5]==1 &&
       request[6]==0 && request[7]==0xf7 && g_uploaded_header_valid){
        for(i=0;i<7;++i)g_reply[i]=request[i];g_reply[3]=0x0b;
        for(i=0;i<192;++i){g_reply[7+2*i]=g_uploaded_header[i]&15;
                            g_reply[8+2*i]=g_uploaded_header[i]>>4;}
        g_reply[391]=0xf7;g_reply_size=392;return;
    }

    /* Synthetic STAT fixture: documented layout, invented lab capacities. */
    if(size==6 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0 && request[4]==0x48 && request[5]==0xf7){
        static const BYTE status[21]={0xf0,0x47,0,1,0x48,0,2,0,8,126,7,
            0,0,64,0,112,127,63,0,0,0xf7};
        for(i=0;i<21;++i)g_reply[i]=status[i];g_reply_size=21;return;
    }

    /* MESA refresh capture seq45/tick34973959: exact bank1/index20 read.
     * Explicit synthetic value zero, NOT captured hardware state. S3000
     * extension envelope: echo 12-byte header, function34, nibbled byte, EOX.
     * The meaning of index20 is not established by the available manual.
     */
    { static const BYTE misc_read[13]={0xf0,0x47,0,0x33,0x48,0x14,0,1,0,0,1,0,0xf7};
      DWORD matches=size==13;
      if(matches)for(i=0;i<13;++i)if(i!=5 && request[i]!=misc_read[i])matches=0;
      if(matches && request[5]!=0x14 && request[5]!=0x49)matches=0;
      if(matches){for(i=0;i<12;++i)g_reply[i]=request[i];g_reply[3]=0x34;
        g_reply[12]=0;g_reply[13]=0;g_reply[14]=0xf7;g_reply_size=15;return;}
    }

    /* Isolated blank FX fixture. Sizes/index sequence from original MESA
     * 10009690/10009770; name offsets from 10009989/10009b7e/10009b9a.
     * Reserved/unknown fields are synthetic zero, NOT verified S2000 defaults.
     * This is a bounded lab compatibility experiment, never device evidence. */
    if(size==13 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0x2d && request[4]==0x48 && request[6]==0 &&
       request[8]==0 && request[9]==0 && request[12]==0xf7){
        DWORD count=request[10]+128u*request[11], selector=request[7];
        if((selector==0 && request[5]==0 && count==32) ||
           (selector==1 && request[5]==0 && count==512) ||
           (selector==2 && request[5]<50 && count==128)){
            for(i=0;i<12;++i)g_reply[i]=request[i];g_reply[3]=0x2e;
            for(i=0;i<count;++i){BYTE value=0;
                if(selector==0 && i>=3 && i<15)value=10;
                if(selector==1)value=255; /* explicit unassigned lab sentinel */
                if(selector==2 && (i<12 || (i>=96 && i<108)))value=10;
                g_reply[12+2*i]=value&15;g_reply[13+2*i]=value>>4;
            }
            g_reply_size=13+2*count;g_reply[g_reply_size-1]=0xf7;return;
        }
    }

    /* Documented legacy PLIST/SLIST; exactly one synthetic lab object. */
    if(size==6 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       (request[3]==2 || request[3]==4) && request[4]==0x48 && request[5]==0xf7){
        static const BYTE name[12]={29,35,24,30,18,10,22,11,12,10,10,10};
        for(i=0;i<5;++i)g_reply[i]=request[i];g_reply[3]=request[3]+1;
        g_reply[5]=1;g_reply[6]=0;
        for(i=0;i<12;++i)g_reply[7+i]=name[i];
        if((request[3]==2 && g_uploaded_program_valid) ||
           (request[3]==4 && g_uploaded_header_valid)){
            const BYTE *added=request[3]==2?g_uploaded_program:g_uploaded_header;
            g_reply[5]=2;for(i=0;i<12;++i)g_reply[19+i]=added[3+i];
            g_reply[31]=0xf7;g_reply_size=32;return;
        }
        g_reply[19]=0xf7;g_reply_size=20;return;
    }

    /* Captured MESA RSDATA includes a zero pad AFTER EOX (9 DATA OUT bytes).
     * Accept only this exact transport padding. Synthetic memory has index0
     * only: documented REPLY/error for other resident indexes, never fake data. */
    if(size==9 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0x0a && request[4]==0x48 && request[7]==0xf7 && request[8]==0){
        queue_header_reply(request,8);return;
    }
    if(((size==8 && (request[3]==6 || request[3]==0x0a) && request[7]==0xf7 &&
          (request[5]!=0 || request[6]!=0)) ||
        (size==9 && request[3]==8 && request[8]==0xf7 &&
          (request[5]!=0 || request[6]!=0 || request[7]!=0))) &&
       request[0]==0xf0 && request[1]==0x47 && request[2]==0 && request[4]==0x48){
        static const BYTE error[7]={0xf0,0x47,0,0x16,0x48,1,0xf7};
        for(i=0;i<7;++i)g_reply[i]=error[i];g_reply_size=7;return;
    }

    /* Exact index-zero RKDATA; synthetic one-zone keygroup only. */
    if(size==9 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==8 && request[4]==0x48 && request[5]==0 &&
       request[6]==0 && request[7]==0 && request[8]==0xf7){
        static const BYTE name[12]={29,35,24,30,18,10,22,11,12,10,10,10};
        for(i=0;i<192;++i)header[i]=0;
        header[0]=2;header[3]=24;header[4]=127;header[7]=99;header[14]=99;
        for(i=0;i<12;++i)header[34+i]=name[i];
        header[46]=0;header[47]=127;
        for(i=1;i<4;++i){DWORD j;for(j=0;j<12;++j)header[34+24*i+j]=10;}
        for(i=0;i<8;++i)g_reply[i]=request[i];g_reply[3]=9;
        for(i=0;i<192;++i){g_reply[8+2*i]=header[i]&15;g_reply[9+2*i]=header[i]>>4;}
        g_reply[392]=0xf7;g_reply_size=393;return;
    }

    if (size != 8 || request[0]!=0xf0 || request[1]!=0x47 ||
        (request[3]!=0x0a && request[3]!=0x06) || request[4]!=0x48 || request[5]!=0 ||
        request[6]!=0 || request[7]!=0xf7) return;
    for(i=0;i<192;++i) header[i]=0;
    header[0]=3; header[2]=60;
    /* Akai alphabet: 0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ#+-. */
    { static const BYTE name[12]={29,35,24,30,18,10,22,11,12,10,10,10};
      for(i=0;i<12;++i) header[3+i]=name[i]; }
    header[15]=0x80; header[19]=2;
    header[26]=16; header[34]=16; header[138]=0x44; header[139]=0xac;
    for(i=0;i<7;++i) g_reply[i]=request[i];
    if(request[3]==0x06) {
        for(i=0;i<192;++i) header[i]=0;
        header[0]=1;
        { static const BYTE name[12]={29,35,24,30,18,10,22,11,12,10,10,10};
          for(i=0;i<12;++i) header[3+i]=name[i]; }
        header[17]=15; header[18]=1; header[19]=24; header[20]=127;
        header[22]=255; header[23]=99; header[25]=99; header[42]=1;
    }
    g_reply[3]=request[3]==0x06?0x07:0x0b;
    for(i=0;i<192;++i){g_reply[7+2*i]=header[i]&15;g_reply[8+2*i]=header[i]>>4;}
    g_reply[391]=0xf7; g_reply_size=392;
}
int main(void){
 BYTE padded[9]={0xf0,0x47,0,0x0a,0x48,0,0,0xf7,0};
 queue_header_reply(padded,9);assert(g_reply_size==392 && g_reply[3]==0x0b);
 padded[5]=1;queue_header_reply(padded,9);assert(g_reply_size==7 && g_reply[5]==1);
 padded[8]=1;queue_header_reply(padded,9);assert(g_reply_size==0);

 BYTE list[6]={0xf0,0x47,0,2,0x48,0xf7};
 queue_header_reply(list,6);assert(g_reply_size==20 && g_reply[3]==3 && g_reply[5]==1 && g_reply[19]==0xf7);
 list[3]=4;queue_header_reply(list,6);assert(g_reply_size==20 && g_reply[3]==5);
 list[5]=0;queue_header_reply(list,6);assert(g_reply_size==0);

 BYTE r[]={0xf0,0x47,0,0x33,0x48,0x14,0,1,0,0,1,0,0xf7};
 queue_header_reply(r,sizeof(r));assert(g_reply_size==15);assert(g_reply[3]==0x34);assert(g_reply[12]==0&&g_reply[13]==0&&g_reply[14]==0xf7);
 for(unsigned i=0;i<12;i++)if(i!=3)assert(g_reply[i]==r[i]);
 r[5]=21;queue_header_reply(r,sizeof(r));assert(g_reply_size==0);
 r[5]=0x49;queue_header_reply(r,13);assert(g_reply_size==15&&g_reply[5]==0x49);
 r[5]=20;queue_header_reply(r,12);assert(g_reply_size==0);
 BYTE p[]={0xf0,0x47,0,6,0x48,0,0,0xf7};queue_header_reply(p,sizeof(p));assert(g_reply_size==392);
 unsigned h[192];for(unsigned i=0;i<192;i++)h[i]=g_reply[7+2*i]|(g_reply[8+2*i]<<4);
 assert(h[0]==1&&h[19]==24&&h[20]==127&&h[42]==1&&h[23]==99);
 BYTE k[]={0xf0,0x47,0,8,0x48,0,0,0,0xf7};queue_header_reply(k,sizeof(k));assert(g_reply_size==393&&g_reply[392]==0xf7);
 BYTE fx[]={0xf0,0x47,0,0x2d,0x48,0,0,0,0,0,32,0,0xf7};
 queue_header_reply(fx,13);assert(g_reply_size==77&&g_reply[3]==0x2e&&g_reply[76]==0xf7);
 fx[7]=1;fx[10]=0;fx[11]=4;queue_header_reply(fx,13);assert(g_reply_size==1037);
 for(unsigned i=0;i<512;i++)assert(g_reply[12+2*i]==15&&g_reply[13+2*i]==15);
 fx[7]=2;fx[11]=1;
 for(unsigned j=0;j<50;j++){fx[5]=j;queue_header_reply(fx,13);assert(g_reply_size==269&&g_reply[268]==0xf7);}
 fx[5]=50;queue_header_reply(fx,13);assert(g_reply_size==0);
 fx[5]=0;fx[11]=0;queue_header_reply(fx,13);assert(g_reply_size==0);
 BYTE note[]={0xc0,0};queue_header_reply(note,2);assert(g_reply_size==0);
 BYTE upload[392]={0xf0,0x47,0,0x0b,0x48,1,0};
 upload[7]=3;upload[7+2*27]=1;upload[391]=0xf7;
 queue_header_reply(upload,392);assert(g_reply_size==7&&g_reply[5]==0&&g_uploaded_header_valid);
 padded[8]=0;queue_header_reply(padded,9);assert(g_reply_size==392);
 assert((g_reply[7+2*27]|(g_reply[8+2*27]<<4))==1);
 upload[7]=16;queue_header_reply(upload,392);assert(g_reply_size==0);
 upload[7]=3;queue_header_reply(upload,391);assert(g_reply_size==0);
 upload[7+2*27]=2;queue_header_reply(upload,392);assert(g_reply_size==0);
 BYTE final[13]={0xf0,0x47,0,0x34,0x48,1,0,0,0,0,0,0,0xf7};
 queue_header_reply(final,13);assert(g_reply_size==0);
 BYTE pcm[512];for(unsigned i=0;i<512;++i)pcm[i]=(BYTE)i;
 queue_header_reply(pcm,511);assert(!g_uploaded_pcm_valid);
 queue_header_reply(final,13);assert(g_reply_size==0);
 queue_header_reply(pcm,512);assert(g_uploaded_pcm_valid&&g_reply_size==0);
 for(unsigned i=0;i<512;++i)assert(g_uploaded_pcm[i]==pcm[i]);
 final[5]=2;queue_header_reply(final,13);assert(g_reply_size==0);
 final[5]=1;queue_header_reply(final,12);assert(g_reply_size==0);
 queue_header_reply(final,13);assert(g_reply_size==7&&g_reply[3]==0x16&&g_reply[5]==0);
 upload[7+2*27]=1;queue_header_reply(upload,392);assert(!g_uploaded_pcm_valid);
 queue_header_reply(final,13);assert(g_reply_size==0);
 BYTE program[392]={0xf0,0x47,0,7,0x48,0,1};
 program[7]=1;program[391]=0xf7;
 for(unsigned i=1;i<192;i++){program[7+2*i]=i&15;program[8+2*i]=(i>>4)&15;}
 queue_header_reply(program,391);assert(!g_uploaded_program_valid&&g_reply_size==0);
 program[9]=16;queue_header_reply(program,392);assert(!g_uploaded_program_valid&&g_reply_size==0);
 program[9]=1;program[7]=2;queue_header_reply(program,392);assert(!g_uploaded_program_valid&&g_reply_size==0);
 program[7]=1;program[6]=2;queue_header_reply(program,392);assert(!g_uploaded_program_valid&&g_reply_size==0);
 program[6]=1;queue_header_reply(program,392);assert(g_uploaded_program_valid&&g_reply_size==7&&g_reply[3]==0x16&&g_reply[5]==0);
 for(unsigned i=0;i<192;i++)assert(g_uploaded_program[i]==(i?i:1));
 BYTE readprogram[8]={0xf0,0x47,0,6,0x48,0,1,0xf7};
 queue_header_reply(readprogram,8);assert(g_reply_size==392&&g_reply[3]==7);
 for(unsigned i=0;i<192;i++)assert((g_reply[7+2*i]|(g_reply[8+2*i]<<4))==g_uploaded_program[i]);
 program[391]=0;queue_header_reply(program,392);assert(g_reply_size==0&&g_uploaded_program_valid);
 BYTE kw[393]={0xf0,0x47,0,9,0x48,127,1,0};kw[8]=2;kw[392]=0xf7;
 for(unsigned i=1;i<192;i++){kw[8+2*i]=i&15;kw[9+2*i]=(i>>4)&15;}
 queue_header_reply(kw,392);assert(!g_uploaded_keygroup_valid&&g_reply_size==0);
 kw[10]=16;queue_header_reply(kw,393);assert(!g_uploaded_keygroup_valid&&g_reply_size==0);
 kw[10]=1;kw[8]=3;queue_header_reply(kw,393);assert(!g_uploaded_keygroup_valid&&g_reply_size==0);
 kw[8]=2;kw[7]=1;queue_header_reply(kw,393);assert(!g_uploaded_keygroup_valid&&g_reply_size==0);
 kw[7]=0;queue_header_reply(kw,393);assert(g_uploaded_keygroup_valid&&g_reply_size==7&&g_reply[5]==0);
 for(unsigned i=0;i<192;i++)assert(g_uploaded_keygroup[i]==(i?i:2));
 g_uploaded_header_valid=0;g_uploaded_pcm_valid=0;
 queue_header_reply(final,13);assert(g_reply_size==7&&g_reply[3]==0x16);
 k[5]=1;queue_header_reply(k,9);assert(g_reply_size==393);
 for(unsigned i=0;i<192;i++)assert((g_reply[8+2*i]|(g_reply[9+2*i]<<4))==g_uploaded_keygroup[i]);
 readprogram[5]=1;readprogram[6]=0;queue_header_reply(readprogram,8);assert(g_reply_size==392);
 list[3]=2;list[5]=0xf7;queue_header_reply(list,6);assert(g_reply_size==32&&g_reply[5]==2);
 for(unsigned i=0;i<12;i++)assert(g_reply[19+i]==g_uploaded_program[3+i]);
 program[391]=0xf7;queue_header_reply(program,392);assert(!g_uploaded_keygroup_valid);
 g_uploaded_program_valid=0;queue_header_reply(kw,393);assert(!g_uploaded_keygroup_valid&&g_reply_size==0);
 BYTE ranged[13]={0xf0,0x47,0,0x27,0x48,0,0,0,16,0,1,0,0xf7};
 queue_header_reply(ranged,13);assert(g_reply_size==15&&g_reply[3]==0x28&&g_reply[14]==0xf7);
 BYTE rangedvalue=g_reply[12]|(g_reply[13]<<4);
 BYTE base[8]={0xf0,0x47,0,6,0x48,0,0,0xf7};
 queue_header_reply(base,8);assert(rangedvalue==(g_reply[39]|(g_reply[40]<<4)));
 ranged[8]=15;queue_header_reply(ranged,13);assert(g_reply_size==15);
 ranged[8]=191;ranged[10]=2;queue_header_reply(ranged,13);assert(g_reply_size==0);
 ranged[8]=16;ranged[10]=2;queue_header_reply(ranged,13);assert(g_reply_size==17);
 ranged[10]=1;ranged[5]=1;queue_header_reply(ranged,13);assert(g_reply_size==0);
 ranged[5]=2;queue_header_reply(ranged,13);assert(g_reply_size==0);
 ranged[5]=0;ranged[10]=0;queue_header_reply(ranged,13);assert(g_reply_size==0);
 ranged[10]=1;ranged[8]=128;queue_header_reply(ranged,13);assert(g_reply_size==0);
 ranged[8]=16;
 ranged[5]=0;queue_header_reply(ranged,12);assert(g_reply_size==0);
 puts("PASS: exact misc read, envelope, unknown/truncated rejection, program range, legacy KG length");
}
