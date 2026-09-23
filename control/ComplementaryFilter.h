#ifndef COMPLEMENTARY_FILTER_H
#define COMPLEMENTARY_FILTER_H

class ComplementaryFilter
{
public:

    void begin(float initialAngle);

    float update(
        float gyroRate,
        float accelAngle,
        float dt
    );

    float getAngle() const;

private:

    float angle = 0.0;
};

#endif