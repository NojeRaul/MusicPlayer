#pragma once
#include "Song.h"
#include <vector>
class Playlist {
public:

	Playlist();
	void addToPlaylist(Song s);
	void removeFromPlaylist(Song s);
	Playlist generateRandom();
	void clear();

private:
	std::vector<Song> list;
};