#include <Arduino.h>

const int BUFFER_SIZE = 10;

class SensorAverager {
public:
    void addReading(float reading) {
        if (reading > -999.0) {
            _buffer[_index] = reading;
            _index = (_index + 1) % BUFFER_SIZE;
            _count = (_count < BUFFER_SIZE) ? _count + 1 : BUFFER_SIZE;
        }
    }

    float getAverage() {
        if (_count == 0) return -999.0;
        float sum = 0.0;
        for (int i = 0; i < _count; i++) {
            sum += _buffer[i];
        }
        return sum / _count;
    }

private:
    float _buffer[BUFFER_SIZE] = {0.0};
    int _index = 0;
    int _count = 0;
};