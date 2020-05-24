
#ifndef FIVEINROWSERVER_PLAYER_H
#define FIVEINROWSERVER_PLAYER_H

#include <string>

class Player {
public:
    const int Id;
    char Symbol = '\0';
    std::string PlayerName;

    explicit Player(int playerId) : Id(playerId) {}
};

#endif //FIVEINROWSERVER_PLAYER_H
