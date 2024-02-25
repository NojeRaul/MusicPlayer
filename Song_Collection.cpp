#include "song.h"
#include "SongColection.h"
#include <fstream>
#include <exception>
#include <string>
#include <set>
#include <ostream>
#include <algorithm>
#include <exception>
#include<vector>
#include "SongException.h"

Repository::Repository()
{
	
}

std::ostream& operator<<(std::ostream& os, std::set<std::string> set)
{
	return os;
}


void Repository::addSong(Song& s)
{
	for (auto it = songs.begin(); it != songs.end(); ++it) 
		if (it->getLink() == s.getLink() && it->getArtist() == s.getArtist() && it->getTitle() == s.getTitle())
		{
			SongException exept ("The song already exists");
			throw exept;
		}
		
	songs.push_back(s);
}

const Song& Repository::find(std::string Title, std::string Artist)
{
	auto it = std::find_if(this->songs.begin(), this->songs.end(), [Title, Artist](const Song& s) {return s.getTitle() == Title && s.getArtist() == Artist; });
	if (it == this->songs.end())
		throw std::exception("The song does not exist");
	return *it;

}


FileRepository::FileRepository(const std::string& filename)
{
	this->filename = filename;
	load();
}
void FileRepository::load()
{
	std::ifstream in(filename);
	if (!in.is_open())
		throw std::runtime_error("Could not open file");
	{
		std::string line;
		while (std::getline(in, line)) {

			//getting the artist
			std::string artist = line;

			//getting the title
			std::getline(in, line);
			std::string title = line;

			//getting the link
			std::getline(in, line);
			std::string link = line;

			//getting the lyrics
			std::getline(in, line);
			std::string lyrics = line;

			Song song{ artist, title, link,lyrics };
			this->songs.push_back(song);
		}
	}
}
void Repository::deleteSong(Song& s)
{
	bool ok=0;
	for (auto it = songs.begin(); it != songs.end(); ++it) {
		if (it->getLink() == s.getLink()) {
			songs.erase(it);
			ok=1;
			break;
		}
	}
	if (ok == 0)
	{
		SongException exept("The song does not exist");
		throw exept;
	}
}

void FileRepository::save()
{
	std::ofstream out(filename);
	if (!out.is_open())
		throw std::runtime_error("Could not open file");
	for (auto iterator = this->songs.begin(); iterator < this->songs.end(); iterator++)
	{
		out << iterator->getArtist() << "\n";
		out << iterator->getTitle() << "\n";
		out << iterator->getLink() << "\n";
		out << iterator->getLyrics()
			<< "\n";
	}
	out.close();
}
//auto it = std::find_if(this->songs.begin(), this->songs.end(), [s](const Song& s1) {
//	return s1.getTitle() == s.getTitle() && s1.getArtist() == s.getArtist();
//	}); */
//if (it == this->songs.end())
//throw std::runtime_error("The song does not exist");
//this->songs.erase(it);