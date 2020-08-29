# GemWuenak
Final Project Algorithm Bootcamp Batch 3

Windows only (Karena memakai module `windows.h`)<br>
**N4O**: Niatnya mau bikin biar bisa di Windows/Linux/MacOS, tapi butuh library `ncurses` dan implementasi beberapa function lagi.

## Compiling and Running
`g++ main.cpp pong/ponggame.cpp flappy_bird/flappy_menu.cpp flappy_bird/flappygame.cpp flappy_bird/highscore.cpp kartu41/kartu41.cpp kartu41/kartu41_menu.cpp extras/extra.cpp -o GemWuenak`<br>
`./GemWuenak`

Compiling project in Dev-C++: [Video](https://cdn.discordapp.com/attachments/741333670241239051/749134631361708042/dPSVjACN8N.mp4)<br>
Example used are from commit [`30f9bf1`](https://github.com/noaione/GemWuenak/commit/30f9bf1c9b252174dbe59616b0a75d411bf8ec31)

To get debug/extra output, add `-DDEBUGGAME` flags. `(mainly for Kartu41)`<br>
If you're having problem with the output (garbled), add `-DFALLBACKASCII` flags when compiling.

## Credits
- **RoARene317** (@HerendraTJ)
    - Base code Pong game
- **Ashborne** (@4shb0rne)
    - Base code Flappy Bird
    - Base Highscore implementation
    - Main menu implementation.
- **YouCanCallMeMatt** (@Demonsta18)
    - Game Tester
    - Debugger and modifying code
- **N4O** (@noaione)
    - Kartu41 C++ Code
    - Unification
    - Adding header file to almost everything.
    - All Extras code
    - Reimplement main Flappy Bird code to Class.
    - Main main menu implementation.
- **kisanak** (@kisanakz)
    - Kartu41 original code and Idea
- **PsychSylv**
    - ASCII Art
- **Machiaveliz** (@Machiaveliz)
    - ASCII Art
- **RedDotSight** (@Randomizer23)
    - Menu part
- **Yamada Masaya** (@yamadamasaya123)
    - Base menu for Kartu 41
- **astrid.dr**
    - PPT
- **sherly**
    - TO BE ADDED
- **Kristo Amadeus**
    - TO BE ADDED
