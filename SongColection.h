#pragma once
#include "song.h"
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <ostream>
#include <assert.h>

class Repository {


public:

	Repository();
	virtual ~Repository()=default;
	std::vector<Song> getSongs() { return this->songs; }
	const Song& find(std::string title, std::string artist);
	virtual void addSong(Song& s);
	virtual void deleteSong(Song& s);
	int size() { return this->songs.size(); }

protected:

	std::string text;
	std::vector<Song> songs;
};

class FileRepository:public Repository {
private:
	std::string filename;

public:

	FileRepository(const std::string& filename);
	void load();
	void save();
	void addSong(Song& s) override {
		Repository::addSong(s);
		save();
	}
	void deleteSong(Song& s) override {
		Repository::deleteSong(s);
		save();
	}

};


class TestRepository {

public:

    void testAddAndDeleteSong() {
        Repository repo;
        Song song("Title", "Artist","Link","Lyrics");

        repo.addSong(song);
        assert(repo.size() == 1); // The repository size should be 1 after adding a song

        repo.deleteSong(song);
        assert(repo.size() == 0); // The repository size should be 0 after deleting the song
    }

    void testFindSong() {
        Repository repo;
        Song song("Title", "Artist","Link", "Lyrics");

        repo.addSong(song);
        const Song& foundSong = repo.find("Title", "Artist");
        assert(foundSong.getTitle() == "Title");
        assert(foundSong.getArtist() == "Artist");
    }

    void runAllTests() {
        testAddAndDeleteSong();
        testFindSong();
    }

};