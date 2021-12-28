#include "DataModel.h"

DataModel DataModel::_model;

DataModel& DataModel::getModel()
{
	return DataModel::_model;
}

DataModel::DataModel()
{
	project = new(std::nothrow) infinity::Project;
	if (project == nullptr) {
		exit(-1);
	}

	project->set_time(40);
	project->set_beat(4);
	project->set_tempo(120.00);
	project->set_srate(48000);
	project->set_editor("Infinity Studio 0");
}

DataModel::~DataModel()
{
	delete project;
	project = nullptr;
}

void DataModel::setProjectTime(uint32_t time)
{
	uint32_t minTime = 0;
	for (auto& i : this->project->tracks()) {
		if (i.isvoice()) {
			for (auto& n : i.notes()) {
				std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(n.startbeat(), n.starttick(), n.length());
				minTime = std::max(minTime, EP.second == 0 ? EP.first : EP.first + 1);
			}
		}//人声轨判断最后音符
		else {
			if (i.waves_size() > 0) {
				auto& p = i.waves().Get(i.waves_size() - 1);
				std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(p.startbeat(), p.starttick(), p.length());
				minTime = std::max(minTime, EP.second == 0 ? EP.first : EP.first + 1);
			}
		}//波形轨判断最后片段（不重叠
		for (auto& p : i.params()) {
			if (p.patterns_size() > 0) {
				auto& pp = p.patterns().Get(p.patterns_size() - 1);
				std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(pp.startbeat(), pp.starttick(), pp.length());
				minTime = std::max(minTime, EP.second == 0 ? EP.first : EP.first + 1);
			}
		}//轨道参数片段也参与判断（同参数不重叠
		for (auto& e : i.effectors()) {
			for (auto& p : e.params()) {
				if (p.patterns_size() > 0) {
					auto& pp = p.patterns().Get(p.patterns_size() - 1);
					std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(pp.startbeat(), pp.starttick(), pp.length());
					minTime = std::max(minTime, EP.second == 0 ? EP.first : EP.first + 1);
				}
			}//效果器也参与判断（同参数不重叠
		}
	}
	time = std::max(minTime, time);//总时长不得短于最后元素
	this->project->set_time(time);
}

uint32_t DataModel::getProjectTime()
{
	return this->project->time();
}

void DataModel::setProjectBeat(uint32_t beat)
{
	if (beat > 0) {
		this->project->set_beat(beat);
	}
}

uint32_t DataModel::getProjectBeat()
{
	return this->project->beat();
}

void DataModel::setProjectTempo(double tempo)
{
	if (tempo > 0) {
		this->project->set_tempo(tempo);
	}
}

double DataModel::getProjectTempo()
{
	return this->project->tempo();
}

void DataModel::setProjectSRate(uint64_t sRate)
{
	if (sRate > 0) {
		this->project->set_srate(sRate);
	}
}

uint64_t DataModel::getProjectSRate()
{
	return this->project->srate();
}

void DataModel::setProjectEditor(std::string editor)
{
	if (!editor.empty()) {
		this->project->set_editor(editor);
	}
}

std::string DataModel::getProjectEditor()
{
	return this->project->editor();
}

void DataModel::addProjectAuthor(std::string author)
{
	if (!author.empty()) {
		if (this->project->authors_size() > 0) {
			if (this->project->authors(this->project->authors_size() - 1) == author) {
				return;
			}
		}
		this->project->add_authors(author);
	}
}

std::list<std::string> DataModel::getProjectAuthors()
{
	std::list<std::string> result(this->project->authors().begin(), this->project->authors().end());
	return result;
}

//Utils

std::pair<uint32_t, uint32_t> DataModel::Utils::getEP(uint32_t startBeat, uint32_t startTick, uint64_t length)
{
	length += startTick;
	startBeat += std::floor(length / 480.0);
	length %= 480;
	return std::make_pair(startBeat, static_cast<uint32_t>(length));
}
