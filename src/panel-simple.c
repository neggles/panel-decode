#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdalign.h>
#include <string.h>
#include <errno.h>

#include "panel-simple.h"

static void print_bytes(char *bytes, int len) {
    for (int i = 0; i < len; i++) {
        printf(((i == len - 1) ? (" 0x%02X") : (" 0x%02X,")), bytes[i]);
    }
}

int panel_simple_parse_cmd_seq(const uint8_t *data, int length, panel_cmd_seq_t *seq) {
    panel_cmd_header_t *header;
    panel_cmd_desc_t   *desc;
    char               *buf, *d;
    unsigned int        i, cnt, len;
    int                 ret;

    if (!seq) return -EINVAL;

    buf = malloc(length);
    if (!buf) return -ENOMEM;
    memcpy(buf, data, length);
    if (ret) return ret;

    d   = buf;
    len = length;
    cnt = 0;
    while (len > sizeof(*header)) {
        header = (panel_cmd_header_t *)d;

        d += sizeof(*header);
        len -= sizeof(*header);

        if (header->payload_length > len) return -EINVAL;

        d += header->payload_length;
        len -= header->payload_length;
        cnt++;
    }

    if (len) return -EINVAL;

    seq->cmd_cnt = cnt;
    seq->cmds    = calloc(cnt, sizeof(*desc));
    if (!seq->cmds) return -ENOMEM;

    d   = buf;
    len = length;
    for (i = 0; i < cnt; i++) {
        header = (panel_cmd_header_t *)d;
        len -= sizeof(*header);
        d += sizeof(*header);

        desc          = &seq->cmds[i];
        desc->header  = *header;
        desc->payload = d;

        d += header->payload_length;
        len -= header->payload_length;
    }

    return 0;
}

void panel_simple_xfer_dsi_cmd_seq(panel_cmd_seq_t *seq) {
    unsigned int i;

    for (i = 0; i < seq->cmd_cnt; i++) {
        panel_cmd_desc_t *cmd = &seq->cmds[i];

        switch (cmd->header.data_type) {
            case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
            case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
            case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
            case MIPI_DSI_GENERIC_LONG_WRITE:
                printf("mipi_dsi_generic_write(dsi, (u8[]){");
                print_bytes(cmd->payload, cmd->header.payload_length);
                printf(" }, %i);\n", cmd->header.payload_length);
                break;

            case MIPI_DSI_DCS_SHORT_WRITE:
            case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
            case MIPI_DSI_DCS_LONG_WRITE:
                printf("mipi_dsi_dcs_write_buffer(dsi, (u8[]){");
                print_bytes(cmd->payload, cmd->header.payload_length);
                printf(" }, %i);\n", cmd->header.payload_length);
                break;

            default: break;
        }

        if (cmd->header.delay) {
            printf("msleep(%i);\n", cmd->header.delay);
        }
    }
}
