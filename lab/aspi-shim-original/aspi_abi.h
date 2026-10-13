#ifndef MESA_RE_ASPI_ABI_H
#define MESA_RE_ASPI_ABI_H

#include <windows.h>

#define SC_HA_INQUIRY      0x00
#define SC_GET_DEV_TYPE    0x01
#define SC_EXEC_SCSI_CMD   0x02
#define SC_ABORT_SRB       0x03
#define SC_RESET_DEV       0x04
#define SC_RESCAN_SCSI_BUS 0x07

#define SS_PENDING         0x00
#define SS_COMP            0x01
#define SS_ABORTED         0x02
#define SS_ERR             0x04
#define SS_NO_DEVICE       0x82
#define SS_INVALID_CMD     0x80
#define SS_INVALID_HA      0x81

#define SRB_DIR_IN         0x08
#define SRB_DIR_OUT        0x10
#define SRB_EVENT_NOTIFY   0x40
#define HASTAT_OK          0x00
#define HASTAT_DO_DU       0x12

#pragma pack(push, 1)
typedef struct ASPI_HA_INQUIRY {
    BYTE cmd, status, ha_id, flags;
    DWORD reserved;
    BYTE ha_count, ha_scsi_id;
    BYTE manager_id[16];
    BYTE identifier[16];
    BYTE unique[16];
    WORD reserved2;
} ASPI_HA_INQUIRY;

typedef struct ASPI_GET_DEVICE_TYPE {
    BYTE cmd, status, ha_id, flags;
    DWORD reserved;
    BYTE target, lun, device_type, reserved2;
} ASPI_GET_DEVICE_TYPE;

typedef struct ASPI_EXEC_SCSI {
    BYTE cmd, status, ha_id, flags;
    DWORD reserved;
    BYTE target, lun;
    WORD reserved1;
    DWORD buffer_length;
    BYTE *buffer;
    BYTE sense_length, cdb_length, ha_status, target_status;
    DWORD post_proc;
    DWORD reserved2;
    BYTE reserved3[16];
    BYTE cdb[16];
    BYTE sense[16];
} ASPI_EXEC_SCSI;
#pragma pack(pop)

DWORD __cdecl GetASPI32SupportInfo(void);
DWORD __cdecl SendASPI32Command(void *srb);

#endif
