#ifndef SERVODS3240_H
#define SERVODS3240_H

class ServoDS3240 {
public:
    ServoDS3240(int pwmPin, int pwmChannel = 0);
    void begin();
    void setAngle(float angle);
    void detach();

private:
    int pin;
    int channel;
    float angleToDutyCycle(float angle);
};

#endif
