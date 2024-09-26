#include <iostream>
#include "Note.h"
#include "FretBoard.h"
#include "Application.h"
#include "HighWay.h"
#include "SongAudio.h"
#include "Menu.h"
#include "Engine.h"

int main() {
    Engine engine;
    /*sf::Texture noteSheet;
    if (!noteSheet.loadFromFile("images/new note sprites.png")){
        exit(24);
    }
    sf::Texture fretSprites;
    if (!fretSprites.loadFromFile("images/fret sprites.png")){
        exit(24);
    }

    Note note1(noteSheet, 0, 0, 3);
    Note note2(noteSheet, 1, 0, 4);
    Note note3(noteSheet, 2, 0, 5);
    Note note4(noteSheet, 3, 0, 6);
    Note note5(noteSheet, -1, 0, 7);


    HighWay highway;
    highway.addNote(note5);
    highway.addNote(note4);
    highway.addNote(note3);
    highway.addNote(note2);
    highway.addNote(note1);
    highway.removeNoteFrom(4);
    highway.removeNoteFrom(3);
    highway.removeNoteFrom(2);
    highway.removeNoteFrom(1);
    highway.removeNoteFrom(0);*/

    /*Menu menu;
    //menu.getFileNames();
    //menu.chooseSong();

    /*SongAudio songAudio;
    songAudio.playAllMusic();*/

    //Application::addComponent(menu);
    //Application::run();

    Application application;
    application.run();

    /*HighWay highWay;
    highWay.populateNoteHighways();

    std::cout << highWay;*/




    return 0;
}
