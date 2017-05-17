#include <msp430.h>
#include <stdint.h>

#include <libmspware/driverlib.h>

#include "mcp4xxx.h"

uint8_t pot_read_status()
{
  EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, POT_ADDR);
  EUSCI_B_I2C_enable(EUSCI_B0_BASE);
  EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
  EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE,
        (REG_STATUS << OFFSET_REG) | (CMD_READ << OFFSET_CMD));
  EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_MODE);
  EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

  uint8_t msb = EUSCI_B_I2C_masterReceiveSingle(EUSCI_B0_BASE); // don't care
  EUSCI_B_I2C_masterReceiveMultiByteFinish(EUSCI_B0_BASE);

  uint8_t lsb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);

  (void)msb;
  return lsb;
}

uint16_t pot_get_wiper(uint8_t reg)
{
  EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, POT_ADDR);
  EUSCI_B_I2C_enable(EUSCI_B0_BASE);
  EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
  EUSCI_B_I2C_masterSendSingleByte(EUSCI_B0_BASE,
        (reg << OFFSET_REG) | (CMD_READ << OFFSET_CMD));
  EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_MODE);
  EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

  uint8_t msb = EUSCI_B_I2C_masterReceiveSingle(EUSCI_B0_BASE); // don't care
  EUSCI_B_I2C_masterReceiveMultiByteFinish(EUSCI_B0_BASE);

  uint8_t lsb = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);

  uint16_t wiper = (msb << 8) | lsb;
  return wiper;
}

static void pot_set_wiper(uint8_t reg, uint16_t v)
{
  EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, POT_ADDR);
  EUSCI_B_I2C_enable(EUSCI_B0_BASE);
  EUSCI_B_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

  EUSCI_B_I2C_masterSendStart(EUSCI_B0_BASE);
  EUSCI_B_I2C_masterSendMultiByteNext(EUSCI_B0_BASE,
        (reg << OFFSET_REG) | (CMD_WRITE << OFFSET_CMD) | ((v >> 8) & 0x3));
  EUSCI_B_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, (uint8_t)(v & 0xff));
  EUSCI_B_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);
  while(EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));
}

uint16_t pot_get_v_wiper()
{
    return pot_get_wiper(REG_VWIPER0);
}

uint16_t pot_get_nv_wiper()
{
    return pot_get_wiper(REG_NVWIPER0);
}

void pot_set_v_wiper(uint16_t v)
{
    pot_set_wiper(REG_VWIPER0, v);
}

void pot_set_nv_wiper(uint16_t v)
{
    pot_set_wiper(REG_NVWIPER0, v);
}
