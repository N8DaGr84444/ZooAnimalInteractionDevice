#include <EEPROM.h>

struct Config {
  uint8_t dFac;
};

static struct Config conf;
static const uint8_t ADDR = 0;

void initDFac(void)
{
  conf.dFac = 0;
  EEPROM.put(ADDR, conf.dFac);
}

uint8_t getDFac(void)
{
  EEPROM.get(ADDR, conf.dFac);
  return conf.dFac;
}

void setDFac(int cVal)
{
  uint8_t nDFac = conf.dFac + cVal;
  if (nDFac <= 100)
  {
    conf.dFac = nDFac;
    EEPROM.put(ADDR, conf.dFac);
  }
}
