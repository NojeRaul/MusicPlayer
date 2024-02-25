#include "Song.h"
#include <vector>
#include<string>
#include <sstream>

Song::Song() :artist{ '\0' }, song{ '\0' }, lyrics{ '\0' } {}

//Song::Song(std::string artist, std::string title, std::string lyrics)
//{
//	this->artist = artist;
//	this->song = title;
//
//	std::stringstream ss(lyrics);
//
//	std::string word;
//	while (ss >> word)
//	{
//		this->lyrics.push_back(word);
//	}
//}

Song::Song(std::string artist, std::string title, std::string link,std::string lyrics)
{
	this->artist = artist;
	this->song = title;
	this->link = link;
	this->lyrics = lyrics;
}

std::string Song::getArtist() const
{
	return artist;
}
std::string Song::getTitle() const
{
	return song;
}

std::string Song::getLyrics()
{
	return this->lyrics;
}

std::string Song::getLink() const
{
	return this->link;
}

void Song::setLyrics(std::string lyrics)
{
	this->lyrics = lyrics;
}

