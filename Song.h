#pragma once
#include<vector>
#include<string>
#include <ostream>
class Song {

public:
	Song();
	//Song(std::string artist, std::string title, std::string lyrics);
	Song(std::string artist, std::string title,std::string link,std::string lyrics);
	std::string getArtist() const;
	std::string getTitle() const;
	void setLyrics(std::string lyrics);
	std::string getLink() const;
	std::string getLyrics();

	friend class Repository;

protected:
	std::string artist;
	std::string song;
	std::string link;
	std::string lyrics;
};