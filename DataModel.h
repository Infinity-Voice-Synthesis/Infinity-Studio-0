#pragma once

#include <algorithm>
#include <string>
#include <list>

#include "Pb/project.pb.h"

class DataModel
{
	DataModel();
	~DataModel();

	static DataModel _model;
	static DataModel& getModel();

public:
	void setProjectTime(uint32_t time);
	uint32_t getProjectTime();
	void setProjectBeat(uint32_t beat);
	uint32_t getProjectBeat();
	void setProjectTempo(double tempo);
	double getProjectTempo();
	void setProjectSRate(uint64_t sRate);
	uint64_t getProjectSRate();
	void setProjectEditor(std::string editor);
	std::string getProjectEditor();
	void addProjectAuthor(std::string author);
	std::list<std::string> getProjectAuthors();

private:
	infinity::Project* project = nullptr;

	class Utils {
	public:
		static std::pair<uint32_t,uint32_t> getEP(uint32_t startBeat, uint32_t startTick, uint64_t length);
	};

};
