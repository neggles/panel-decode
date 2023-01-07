#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "panel-simple.h"


static uint8_t initseq[] = {
    0x39, 0x00, 0x03, 0xe0, 0xab, 0xba, 0x39, 0x00, 0x03, 0xe1, 0xba, 0xab, 0x39, 0x00, 0x05, 0xb1, 0x10,
    0x01, 0x47, 0xff, 0x39, 0x00, 0x07, 0xb2, 0x0c, 0x14, 0x04, 0x50, 0x50, 0x14, 0x39, 0x00, 0x04, 0xb3,
    0x56, 0x53, 0x00, 0x39, 0x00, 0x04, 0xb4, 0x33, 0x30, 0x04, 0x39, 0x00, 0x08, 0xb6, 0xb0, 0x00, 0x00,
    0x10, 0x00, 0x10, 0x00, 0x39, 0x00, 0x08, 0xb8, 0x05, 0x12, 0x29, 0x49, 0x48, 0x00, 0x00, 0x39, 0x00,
    0x27, 0xb9, 0x7c, 0x65, 0x55, 0x49, 0x46, 0x36, 0x3b, 0x24, 0x3d, 0x3c, 0x3d, 0x5c, 0x4c, 0x55, 0x47,
    0x46, 0x39, 0x26, 0x06, 0x7c, 0x65, 0x55, 0x49, 0x46, 0x36, 0x3b, 0x24, 0x3d, 0x3c, 0x3d, 0x5c, 0x4c,
    0x55, 0x47, 0x46, 0x39, 0x26, 0x06, 0x39, 0x00, 0x11, 0xc0, 0xff, 0x87, 0x12, 0x34, 0x44, 0x44, 0x44,
    0x44, 0x98, 0x04, 0x98, 0x04, 0x0f, 0x00, 0x00, 0xc1, 0x39, 0x00, 0x0b, 0xc1, 0x54, 0x94, 0x02, 0x85,
    0x9f, 0x00, 0x7f, 0x00, 0x54, 0x00, 0x39, 0x00, 0x0d, 0xc2, 0x17, 0x09, 0x08, 0x89, 0x08, 0x11, 0x22,
    0x20, 0x44, 0xff, 0x18, 0x00, 0x39, 0x00, 0x17, 0xc3, 0x86, 0x46, 0x05, 0x05, 0x1c, 0x1c, 0x1d, 0x1d,
    0x02, 0x1f, 0x1f, 0x1e, 0x1e, 0x0f, 0x0f, 0x0d, 0x0d, 0x13, 0x13, 0x11, 0x11, 0x00, 0x39, 0x00, 0x17,
    0xc4, 0x07, 0x07, 0x04, 0x04, 0x1c, 0x1c, 0x1d, 0x1d, 0x02, 0x1f, 0x1f, 0x1e, 0x1e, 0x0e, 0x0e, 0x0c,
    0x0c, 0x12, 0x12, 0x10, 0x10, 0x00, 0x39, 0x00, 0x03, 0xc6, 0x2a, 0x2a, 0x39, 0x00, 0x07, 0xc8, 0x21,
    0x00, 0x31, 0x42, 0x34, 0x16, 0x39, 0x00, 0x03, 0xca, 0xcb, 0x43, 0x39, 0x00, 0x09, 0xcd, 0x0e, 0x4b,
    0x4b, 0x20, 0x19, 0x6b, 0x06, 0xb3, 0x39, 0x00, 0x05, 0xd2, 0xe3, 0x2b, 0x38, 0x00, 0x39, 0x00, 0x0c,
    0xd4, 0x00, 0x01, 0x00, 0x0e, 0x04, 0x44, 0x08, 0x10, 0x00, 0x00, 0x00, 0x39, 0x00, 0x09, 0xe6, 0x80,
    0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x39, 0x00, 0x06, 0xf0, 0x12, 0x03, 0x20, 0x00, 0xff, 0x15,
    0x00, 0x02, 0xf3, 0x00, 0x05, 0x78, 0x01, 0x11, 0x05, 0x32, 0x01, 0x29};

static uint8_t exitseq[] = {0x05, 0xdc, 0x01, 0x28, 0x05, 0x78, 0x01, 0x10};


int main(void) {
    panel_cmd_seq_t *initcmd = malloc(sizeof(panel_cmd_seq_t));
    panel_cmd_seq_t *exitcmd = malloc(sizeof(panel_cmd_seq_t));
    printf("INIT:\n");
    panel_simple_parse_cmd_seq(initseq, 301, initcmd);
    panel_simple_xfer_dsi_cmd_seq(initcmd);
    printf("\n\nEXIT:\n");
    panel_simple_parse_cmd_seq(exitseq, 8, exitcmd);
    panel_simple_xfer_dsi_cmd_seq(exitcmd);
}