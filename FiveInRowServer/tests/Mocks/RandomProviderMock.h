#include "gmock/gmock.h"
#include <Util/RandomProvider.h>

class RandomProviderMock : public IRandomProvider {
public:
    MOCK_METHOD(int, Next, (int minValue, int maxValue), (const, override));
};