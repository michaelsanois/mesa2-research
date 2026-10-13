/*
 * MESA II isolated fake ASPI adapter.
 *
 * This DLL does not call DeviceIoControl, open SCSI devices, access USB/MIDI,
 * or use networking. It reports a synthetic SCSI-2 AKAI S2000 at HA 0 / ID 2.
 * Unknown target-2 commands are captured and completed with synthetic GOOD;
 * Known header requests receive explicitly synthetic fixtures; other DATA IN
 * buffers are zero-filled except INQUIRY and REQUEST SENSE. Every record states synthetic=true. This is a lab probe, not
 * a physical-device implementation and must never be installed on the Mac.
 */
#include "aspi_abi.h"

#define FAKE_TARGET 2
#define MAX_CAPTURE (16u * 1024u * 1024u)

/* Research fixture only: Lakai RSDATA/SDATA envelope and 192-byte S2000
 * header. No real PCM or resident object is claimed by this fixture. */
static BYTE g_reply[393];
static DWORD g_reply_size, g_reply_offset;
static void queue_header_reply(const BYTE *request, DWORD size)
{
    BYTE header[192]; DWORD i;
    g_reply_size = g_reply_offset = 0;
    /* Exact startup write observed from MESA; isolated synthetic ACK only. */
    { static const BYTE startup[15]={0xf0,0x47,0,0x34,0x48,0x0b,0,1,0,0,1,0,5,0,0xf7};
      DWORD matches=size==15;
      if(matches)for(i=0;i<15;++i)if(request[i]!=startup[i])matches=0;
      if(matches){static const BYTE ack[7]={0xf0,0x47,0,0x16,0x48,0,0xf7};
        for(i=0;i<7;++i)g_reply[i]=ack[i];g_reply_size=7;return;}
    }

    /* Synthetic STAT fixture: documented layout, invented lab capacities. */
    if(size==6 && request[0]==0xf0 && request[1]==0x47 && request[2]==0 &&
       request[3]==0 && request[4]==0x48 && request[5]==0xf7){
        static const BYTE status[21]={0xf0,0x47,0,1,0x48,0,2,0,8,126,7,
            0,0,64,0,112,127,63,0,0,0xf7};
        for(i=0;i<21;++i)g_reply[i]=status[i];g_reply_size=21;return;
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
        header[17]=15; header[25]=99; header[42]=1;
    }
    g_reply[3]=request[3]==0x06?0x07:0x0b;
    for(i=0;i<192;++i){g_reply[7+2*i]=header[i]&15;g_reply[8+2*i]=header[i]>>4;}
    g_reply[391]=0xf7; g_reply_size=392;
}
static DWORD g_sequence;
static volatile LONG g_log_lock;
static char g_process_name[64] = "unknown";
static const char g_trace_path[] = "C:\\MESA_CAPTURE\\TRACE.TXT";

typedef struct TEXT_BUFFER { char data[4096]; DWORD size; } TEXT_BUFFER;
static TEXT_BUFFER g_log_buffer;

static void put_char(TEXT_BUFFER *b, char c)
{
    if (b->size < sizeof(b->data)) b->data[b->size++] = c;
}

static void put_string(TEXT_BUFFER *b, const char *s)
{
    while (*s && b->size < sizeof(b->data)) put_char(b, *s++);
}

static void identify_process(void)
{
    char full[MAX_PATH]; DWORD n, start = 0, i = 0;
    n = GetModuleFileNameA(NULL, full, MAX_PATH);
    if (!n || n >= MAX_PATH) return;
    while (i < n) {
        if (full[i] == '\\' || full[i] == '/') start = i + 1;
        ++i;
    }
    i = 0;
    while (start < n && i + 1 < sizeof(g_process_name))
        g_process_name[i++] = full[start++];
    g_process_name[i] = 0;
}

static void put_u32(TEXT_BUFFER *b, DWORD value)
{
    char digits[10]; DWORD n = 0;
    do { digits[n++] = (char)('0' + value % 10); value /= 10; } while (value && n < sizeof(digits));
    while (n) put_char(b, digits[--n]);
}

static void put_hex_byte(TEXT_BUFFER *b, BYTE value)
{
    static const char hex[] = "0123456789ABCDEF";
    put_char(b, hex[(value >> 4) & 15]);
    put_char(b, hex[value & 15]);
}

static BOOL write_file(const char *path, const void *data, DWORD length, BOOL append)
{
    HANDLE h; DWORD written = 0;
    h = CreateFileA(path, GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                    append ? OPEN_ALWAYS : CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return FALSE;
    if (append && SetFilePointer(h, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER
        && GetLastError() != NO_ERROR) { CloseHandle(h); return FALSE; }
    if (length && !WriteFile(h, data, length, &written, NULL)) { CloseHandle(h); return FALSE; }
    CloseHandle(h);
    return written == length;
}

static void make_payload_name(DWORD sequence, char *out)
{
    static const char prefix[] = "C:\\MESA_CAPTURE\\DATA";
    DWORD i = 0, divisor = 1000000;
    while (prefix[i]) { out[i] = prefix[i]; ++i; }
    for (; divisor; divisor /= 10) { out[i++] = (char)('0' + (sequence / divisor) % 10); }
    out[i++] = '.'; out[i++] = 'B'; out[i++] = 'I'; out[i++] = 'N'; out[i] = 0;
}

static void make_log_name(DWORD sequence, char *out)
{
    static const char prefix[] = "C:\\MESA_CAPTURE\\LOG";
    DWORD i = 0, divisor = 1000000;
    while (prefix[i]) { out[i] = prefix[i]; ++i; }
    for (; divisor; divisor /= 10) out[i++] = (char)('0' + (sequence / divisor) % 10);
    out[i++] = '.'; out[i++] = 'T'; out[i++] = 'X'; out[i++] = 'T'; out[i] = 0;
}

static DWORD next_sequence(void)
{
    return (DWORD)InterlockedIncrement((volatile LONG *)&g_sequence);
}

static void log_simple(const char *event, BYTE command, BYTE status,
                       BYTE ha_id, BYTE target, BYTE lun, BYTE detail)
{
    TEXT_BUFFER *b = &g_log_buffer; DWORD sequence;
    while (InterlockedExchange(&g_log_lock, 1)) Sleep(0);
    b->size = 0;
    sequence = next_sequence();
    put_string(b, "{\"seq\":"); put_u32(b, sequence);
    put_string(b, ",\"tick_ms\":"); put_u32(b, GetTickCount());
    put_string(b, ",\"process\":\""); put_string(b, g_process_name); put_char(b, '"');
    put_string(b, ",\"synthetic\":true,\"event\":\""); put_string(b, event);
    put_string(b, "\",\"srb_cmd\":"); put_u32(b, command);
    put_string(b, ",\"srb_status\":"); put_u32(b, status);
    put_string(b, ",\"ha\":"); put_u32(b, ha_id);
    put_string(b, ",\"target\":"); put_u32(b, target);
    put_string(b, ",\"lun\":"); put_u32(b, lun);
    put_string(b, ",\"detail\":"); put_u32(b, detail);
    put_string(b, "}\r\n");
    CreateDirectoryA("C:\\MESA_CAPTURE", NULL);
    write_file(g_trace_path, b->data, b->size, TRUE);
    InterlockedExchange(&g_log_lock, 0);
}

static void log_exec(const ASPI_EXEC_SCSI *srb, DWORD sequence,
                     const char *payload_name, const char *payload_kind,
                     DWORD payload_bytes, BOOL payload_ok)
{
    TEXT_BUFFER *b = &g_log_buffer; DWORD i, cdb_len = srb->cdb_length;
    while (InterlockedExchange(&g_log_lock, 1)) Sleep(0);
    b->size = 0;
    put_string(b, "{\"seq\":"); put_u32(b, sequence);
    put_string(b, ",\"tick_ms\":"); put_u32(b, GetTickCount());
    put_string(b, ",\"process\":\""); put_string(b, g_process_name); put_char(b, '"');
    put_string(b, ",\"synthetic\":true,\"srb_cmd\":2,\"ha\":"); put_u32(b, srb->ha_id);
    put_string(b, ",\"target\":"); put_u32(b, srb->target);
    put_string(b, ",\"lun\":"); put_u32(b, srb->lun);
    put_string(b, ",\"cdb\":\"");
    if (cdb_len > 16) cdb_len = 16;
    for (i = 0; i < cdb_len; ++i) put_hex_byte(b, srb->cdb[i]);
    put_string(b, "\",\"direction\":\"");
    if (srb->flags & SRB_DIR_IN) put_string(b, "in");
    else if (srb->flags & SRB_DIR_OUT) put_string(b, "out");
    else put_string(b, "none-or-unspecified");
    put_string(b, "\",\"requested\":"); put_u32(b, srb->buffer_length);
    put_string(b, ",\"payload_bytes\":"); put_u32(b, payload_bytes);
    put_string(b, ",\"srb_status\":"); put_u32(b, srb->status);
    put_string(b, ",\"host_status\":"); put_u32(b, srb->ha_status);
    put_string(b, ",\"target_status\":"); put_u32(b, srb->target_status);
    if (payload_name && payload_name[0]) {
        put_string(b, ",\"payload_kind\":\""); put_string(b, payload_kind);
        put_string(b, "\"");
        put_string(b, ",\"payload_file\":\"");
        /* File names contain no JSON-special characters. */
        put_string(b, payload_name + 16); /* basename after C:\\MESA_CAPTURE\\ */
        put_string(b, "\",\"payload_write_ok\":");
        put_string(b, payload_ok ? "true" : "false");
    }
    put_string(b, "}\r\n");
    CreateDirectoryA("C:\\MESA_CAPTURE", NULL);
    write_file(g_trace_path, b->data, b->size, TRUE);
    InterlockedExchange(&g_log_lock, 0);
}

static void copy_bytes(BYTE *dst, const BYTE *src, DWORD count)
{
    DWORD i; for (i = 0; i < count; ++i) dst[i] = src[i];
}

static DWORD min_u32(DWORD a, DWORD b) { return a < b ? a : b; }

static DWORD complete_exec(ASPI_EXEC_SCSI *s)
{
    /* MESA supplies an event handle in SRB_PostProc, not a callback. */
    if ((s->flags & SRB_EVENT_NOTIFY) && s->post_proc)
        SetEvent((HANDLE)(ULONG_PTR)s->post_proc);
    return s->status;
}

DWORD __cdecl GetASPI32SupportInfo(void)
{
    /* ASPI return: adapter count in bits 8..15, status in bits 0..7. */
    log_simple("GetASPI32SupportInfo", 0xff, SS_COMP, 0, 0, 0, 1);
    return (1u << 8) | SS_COMP;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    (void)instance; (void)reserved;
    /* A load marker distinguishes Windows loader failure from ASPI rejection. */
    if (reason == DLL_PROCESS_ATTACH) {
        identify_process();
        log_simple("DllMain_PROCESS_ATTACH", 0xfe, SS_COMP, 0, 0, 0, 0);
    }
    return TRUE;
}

DWORD __cdecl SendASPI32Command(void *opaque)
{
    BYTE *header = (BYTE *)opaque;
    if (!header) return SS_ERR;

    if (header[0] == SC_HA_INQUIRY) {
        ASPI_HA_INQUIRY *s = (ASPI_HA_INQUIRY *)opaque;
        s->status = SS_COMP; s->ha_count = 1; s->ha_scsi_id = 7;
        /* SCSIPlug reads SRB byte 45 (unique[3]) as target-scan bound.
           A narrow synthetic bus exposes IDs 0..7; zero prevents discovery. */
        s->unique[3] = 8;
        copy_bytes(s->manager_id, (const BYTE *)"MESA RE FAKE ASPI", 16);
        copy_bytes(s->identifier, (const BYTE *)"SYNTHETIC S2000", 15);
        log_simple("SRB_HA_INQUIRY", s->cmd, s->status, s->ha_id, 0, 0, s->ha_count);
        return SS_COMP;
    }
    if (header[0] == SC_GET_DEV_TYPE) {
        ASPI_GET_DEVICE_TYPE *s = (ASPI_GET_DEVICE_TYPE *)opaque;
        if (s->ha_id == 0 && s->target == FAKE_TARGET && s->lun == 0) {
            s->device_type = 3; s->status = SS_COMP;
            log_simple("SRB_GET_DEV_TYPE", s->cmd, s->status, s->ha_id, s->target, s->lun, s->device_type);
            return SS_COMP;
        }
        s->status = SS_NO_DEVICE;
        log_simple("SRB_GET_DEV_TYPE", s->cmd, s->status, s->ha_id, s->target, s->lun, 0xff);
        return SS_NO_DEVICE;
    }
    if (header[0] == SC_RESCAN_SCSI_BUS) {
        header[1] = SS_COMP; log_simple("SRB_RESCAN", header[0], header[1], header[2], 0, 0, 0); return SS_COMP;
    }
    if (header[0] == SC_RESET_DEV) {
        header[1] = SS_COMP; log_simple("SRB_RESET", header[0], header[1], header[2], 0, 0, 0); return SS_COMP;
    }
    if (header[0] == SC_ABORT_SRB) {
        header[1] = SS_ABORTED; log_simple("SRB_ABORT", header[0], header[1], header[2], 0, 0, 0); return SS_ABORTED;
    }

    if (header[0] == SC_EXEC_SCSI_CMD) {
        ASPI_EXEC_SCSI *s = (ASPI_EXEC_SCSI *)opaque;
        DWORD actual = 0, requested = s->buffer_length;
        char payload_name[64]; BOOL payload_ok = TRUE; BOOL has_payload = FALSE;
        DWORD sequence = next_sequence();
        const char *payload_kind = "";
        payload_name[0] = 0;
        CreateDirectoryA("C:\\MESA_CAPTURE", NULL);

        s->status = SS_COMP;
        s->ha_status = HASTAT_OK;
        s->target_status = 0; /* SCSI GOOD */
        if (s->ha_id != 0 || s->target != FAKE_TARGET || s->lun != 0) {
            /* Absent synthetic IDs are NO_DEVICE, never successful commands.
             * Clear DATA IN so the discovery consumer cannot inspect stale bytes.
             * No physical bus transaction or response is claimed here. */
            DWORD i;
            if ((s->flags & SRB_DIR_IN) && s->buffer && requested <= MAX_CAPTURE)
                for (i = 0; i < requested; ++i) s->buffer[i] = 0;
            s->status = SS_NO_DEVICE;
            log_exec(s, sequence, NULL, "synthetic_absent", 0, TRUE);
            return complete_exec(s);
        }
        if (requested > MAX_CAPTURE || (requested && !s->buffer)) {
            s->status = SS_ERR; s->ha_status = HASTAT_DO_DU;
            log_exec(s, sequence, NULL, "", 0, FALSE); return complete_exec(s);
        }

        if ((s->flags & SRB_DIR_OUT) && requested) {
            make_payload_name(sequence, payload_name);
            has_payload = TRUE;
            payload_ok = write_file(payload_name, s->buffer, requested, FALSE);
            actual = payload_ok ? requested : 0;
            payload_kind = "mesa_data_out";
            if (s->cdb[0]==0x0c && payload_ok) queue_header_reply(s->buffer, requested);
            if (!payload_ok) { s->status = SS_ERR; s->ha_status = HASTAT_DO_DU; }
        } else if ((s->flags & SRB_DIR_IN) && requested && s->buffer) {
            DWORD i;
            for (i = 0; i < requested; ++i) s->buffer[i] = 0;
            if (s->cdb[0] == 0x12) { /* SCSI INQUIRY: synthetic AKAI S2000 */
                static const BYTE inquiry[36] = {
                    0x03,0x00,0x02,0x02,0x1f,0x00,0x00,0x00,
                    'A','K','A','I',' ',' ',' ',' ',
                    'S','2','0','0','0',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                    '2','.','0',' '
                };
                actual = min_u32(requested, min_u32(s->cdb[4], sizeof(inquiry)));
                copy_bytes(s->buffer, inquiry, actual);
            } else if (s->cdb[0] == 0x0d && requested == 3) {
                DWORD remaining=g_reply_size-g_reply_offset;
                s->buffer[0]=(BYTE)(remaining>>16);s->buffer[1]=(BYTE)(remaining>>8);s->buffer[2]=(BYTE)remaining;
                actual=3;
            } else if (s->cdb[0] == 0x0e) {
                DWORD cdb_count=((DWORD)s->cdb[2]<<16)|((DWORD)s->cdb[3]<<8)|s->cdb[4];
                DWORD remaining=g_reply_size-g_reply_offset;
                if(cdb_count!=requested || requested>remaining){s->status=SS_ERR;s->ha_status=HASTAT_DO_DU;actual=0;}
                else {copy_bytes(s->buffer,g_reply+g_reply_offset,requested);g_reply_offset+=requested;actual=requested;}
            } else if (s->cdb[0] == 0x03) { /* REQUEST SENSE: no pending error */
                static const BYTE sense[18] = {0x70,0,0,0,0,0,0,10};
                actual = min_u32(requested, min_u32(s->cdb[4], sizeof(sense)));
                copy_bytes(s->buffer, sense, actual);
            } else {
                /* Unknown DATA IN is synthetic zero-fill, called out in the log. */
                actual = requested;
            }
            make_payload_name(sequence, payload_name);
            has_payload = TRUE;
            payload_kind = "synthetic_response";
            payload_ok = write_file(payload_name, s->buffer, actual, FALSE);
            if (!payload_ok) { s->status = SS_ERR; s->ha_status = HASTAT_DO_DU; }
        }

        if (s->status != SS_ERR) s->status = SS_COMP;
        log_exec(s, sequence, has_payload ? payload_name : NULL, payload_kind, actual, payload_ok);
        return complete_exec(s);
    }

    header[1] = SS_INVALID_CMD;
    log_simple("SRB_UNKNOWN", header[0], header[1], header[2], 0, 0, 0);
    return SS_INVALID_CMD;
}
