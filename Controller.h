#pragma once
#include "SongColection.h"
#include "Song.h"
#include <stack>
#include <memory>
#include "Action.h"
#include <iostream>
#include <cassert>


class Controller {

	friend class Action;
public:

	Controller(Repository& col);
	Controller(Controller& control) = delete;
	void addSong(std::string artist, std::string title,std::string link,std::string lyrics);
	void remove(std::string artist, std::string title, std::string link,std::string lyrics);
	void undo();
	void redo();
    int size();
	Repository& sort(std::string order);

	Repository& getSongs() { return this->colection; }
private:
	Repository &colection;
	std::stack<std::unique_ptr <Action>> undoStack;
	std::stack<std::unique_ptr <Action>> redoStack;	
	

};

class TestController {

public:
    void testAddSong() {
        Repository repository;
        Controller controller(repository);

        controller.addSong("Artist1", "Song1", "Link1","Lyrics");

        Repository& songs = controller.getSongs();
        assert(songs.size() == 1);
        assert(songs.getSongs().at(0).getArtist() == "Artist1");
        assert(songs.getSongs().at(0).getTitle() == "Song1");
        assert(songs.getSongs().at(0).getLink()=="Link1");
    }

    void testRemoveSong() {
        Repository repository;
        Controller controller(repository);

        controller.addSong("Artist1", "Song1", "Link1", "Lyrics");
        controller.remove("Artist1", "Song1", "Link1", "Lyrics");

        Repository& songs = controller.getSongs();

        assert(songs.size() == 0);
    }
    void testSort() {
        //test the sort function
        Repository repository;
        Controller controller(repository);

        controller.addSong("Michael Jackson", "Song1", "Link1", "Lyrics");
        controller.addSong("Pink Floyd", "Song2", "Link2", "Lyrics");

        Repository& songs = controller.getSongs();
        assert(songs.getSongs().at(0).getArtist() == "Michael Jackson");
        assert(songs.getSongs().at(1).getArtist() == "Pink Floyd");

       Repository& sortedSongs1 = controller.sort("desc");
        assert(sortedSongs1.getSongs().at(0).getArtist() == "Pink Floyd");
        assert(sortedSongs1.getSongs().at(0).getArtist() == "Michael Jackson");

        Repository& sortedSongs2 = controller.sort("asc");
        assert(sortedSongs2.getSongs().at(0).getArtist() == "Michael Jackson");
        assert(sortedSongs2.getSongs().at(0).getArtist() == "Pink Floyd");
    }

    void testAll()
    {
		testAddSong();
		testRemoveSong();
        testSort();
	}

};
