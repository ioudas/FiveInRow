#include <string>

class Player {
public:
    const int Id;
    char Symbol = '\0';
    std::string PlayerName;

    explicit Player(int playerId) : Id(playerId) {}
};