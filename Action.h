#pragma once
#include "SongColection.h"
#include "Song.h"
#include <stack>
#include <memory>

class Action {

	friend class Controller;
public:
	virtual void apply() = 0;
	virtual ~Action() {};
};


class AddAction : public Action {

public:
	AddAction(Repository& r, Song &s);
	void apply() override;
	~AddAction() override = default;
private:
	Repository& repo;
	Song s;
};


class ActionDelete : public Action {

public:
	ActionDelete(Repository& r, Song &s);
	void apply() override;
	~ActionDelete() override = default;
private:
	Repository& repo;
	Song s;
};