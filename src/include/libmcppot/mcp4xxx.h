#ifndef MCP4XXX_H
#define MCP4XXX_H

#include <stdint.h>

// Depends on pot model
#define POT_RESOLUTION 128

// Table 6-2
#define POT_ADDR 0x2E // 0101 110

// Table 7-2
#define REG_VWIPER0     0x00
#define REG_NVWIPER0    0x02
#define REG_STATUS      0x05
 
// Figure 7-1
#define CMD_WRITE 0x00
#define CMD_INC   0x01
#define CMD_DEC   0x02
#define CMD_READ  0x03

// Figure 7-1
#define OFFSET_REG 4
#define OFFSET_CMD 2

uint8_t pot_read_status();
void pot_set_v_wiper(uint16_t v);
void pot_set_nv_wiper(uint16_t v);

#endif // MCP4XXX_H
