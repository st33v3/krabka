#ifndef MODE_H
#define MODE_H

class Mode {
    public:
    virtual void enter() = 0;
    virtual void loop() = 0;
    virtual void setup() = 0;
};

#endif