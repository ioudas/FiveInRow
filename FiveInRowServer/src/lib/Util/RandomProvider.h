
#ifndef FIVEINROWSERVER_RANDOMPROVIDER_H
#define FIVEINROWSERVER_RANDOMPROVIDER_H

class IRandomProvider {
public:
    virtual int Next(int minValue, int maxValue) const = 0;
};

class RandomProvider : public IRandomProvider{
    int Next(int minValue, int maxValue) const override;
};

#endif //FIVEINROWSERVER_RANDOMPROVIDER_H
