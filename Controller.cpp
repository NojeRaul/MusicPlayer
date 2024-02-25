#include "Controller.h"
#include "SongColection.h"
#include "Playlist.h"
#include "Action.h"
#include <algorithm>

AddAction::AddAction(Repository& r, Song &s) :repo { r }, s{ s } {}
ActionDelete::ActionDelete(Repository& r, Song &s) :repo { r }, s{ s } {}

Controller::Controller(Repository& col) :colection{ col }
{
	//this->redoStack = std::stack<std::unique_ptr <Action>>();
}
void Controller::addSong(std::string artist, std::string title, std::string link,std::string lyrics)
{
		Song s{ artist, title, link,lyrics };
		std::unique_ptr<AddAction> addAction = std::make_unique<AddAction>(colection, s);
		undoStack.push(std::move(addAction));
		colection.addSong(s);
}
void Controller::remove(std::string artist, std::string title, std::string link,std::string lyrics)
{
	Song s{ artist, title, link,lyrics };
	std::unique_ptr<ActionDelete> deleteAction = std::make_unique<ActionDelete>(colection, s);
	undoStack.push(std::move(deleteAction));
	colection.deleteSong(s);
}

void Controller::undo()
{
	if (!undoStack.empty())
		this->undoStack.top()->apply();
	else
		throw std::exception("UndoStack empty");
	this->redoStack.push(std::move(this->undoStack.top()));
	this->undoStack.pop();
}
void Controller::redo()
{
	if (!redoStack.empty())
		this->redoStack.top()->apply();
	else
		throw std::exception("RedoStack empty");
	this->undoStack.push(std::move(this->redoStack.top()));
	this->redoStack.pop();
}
void AddAction::apply() 
{
	this->repo.deleteSong(s);
}

void ActionDelete::apply()
{
	this->repo.addSong(s);
}

Repository& Controller::sort(std::string order)
{

	if (this->colection.size() >= 2)
	{
		if (order == "asc") {
			std::sort(colection.getSongs().begin(), colection.getSongs().end(),
				[](const Song& obj1, const Song& obj2) {
					return obj1.getArtist() < obj2.getArtist();
				});
		}
		else if (order == "desc") {
			std::sort(colection.getSongs().begin(), colection.getSongs().end(),
				[](const Song& obj1, const Song& obj2) {
					return obj1.getArtist() > obj2.getArtist();
				});
		}
		else {
			// Handle invalid order
			// You can throw an exception or handle the error as needed
		}
	}
	return this->colection;
	
}

int Controller::size()
{
	return this->colection.size();
}