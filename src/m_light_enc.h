#ifndef M_LIGHT_ENC_H
#define M_LIGHT_ENC_H

#include "mode.h"
#include "common.h"

class EncoderLight : public Mode {
  public:
    EncoderLight();
    virtual void enter();
    virtual void loop();
    void setLevel(int level);
    void setHue(int hue);
    int getLevel();
    int getHue();
  protected:
  private:
    int level;
    int hue;
    void setRGB();
    
};

#endif
