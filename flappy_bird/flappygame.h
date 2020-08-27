#ifndef FLAPPY_GAME_H
#define FLAPPY_GAME_H

class FlappyTheBird
{
public:
    int score;

    FlappyTheBird(void);

    void updateWithInput();
    void startup_bird();
    void show_bird();
    int updateWithoutInput();
private:
    int high, width;         // The border
    int bird_x, bird_y;      // The bird coordinates
    int bar_y;               // Baffle coordinates
    int bar_xTop, bar_xDown; // Upper and lower coordinates of the baffle opening
};

#endif /* EXTRA_STUFF_H */