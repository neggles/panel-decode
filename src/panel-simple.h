#ifndef __PD_PANEL_H__
#define __PD_PANEL_H__

#include <stdint.h>

#define MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM 0x03
#define MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM 0x13
#define MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM 0x23
#define MIPI_DSI_GENERIC_LONG_WRITE          0x29
#define MIPI_DSI_DCS_SHORT_WRITE             0x05
#define MIPI_DSI_DCS_SHORT_WRITE_PARAM       0x15
#define MIPI_DSI_DCS_LONG_WRITE              0x39

typedef struct __attribute__((__packed__)) {
    uint8_t data_type;
    uint8_t delay;
    uint8_t payload_length;
} panel_cmd_header_t;

typedef struct {
    panel_cmd_header_t header;
    char              *payload;
} panel_cmd_desc_t;

typedef struct {
    panel_cmd_desc_t *cmds;
    uint32_t          cmd_cnt;
} panel_cmd_seq_t;

int  panel_simple_parse_cmd_seq(const uint8_t *data, int length, panel_cmd_seq_t *seq);
void panel_simple_xfer_dsi_cmd_seq(panel_cmd_seq_t *seq);

#endif // __PD_PANEL_H__
