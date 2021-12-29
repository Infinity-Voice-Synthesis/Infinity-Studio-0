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

void DataModel::addVoiceTrack(std::string name, std::string color, std::string library)
{
	if (name.empty()) {
		return;
	}
	if (color.empty()) {
		return;
	}
	if (library.empty()) {
		return;
	}
	{
		bool flag = false;
		for (auto& i : Package::getPackage().getLibraryAvailable()) {
			if (i == library) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			return;
		}
	}
	std::string engine = Package::getPackage().getEngineName(library);
	{
		bool flag = false;
		for (auto& i : Package::getPackage().getEngineAvailable()) {
			if (i == engine) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			return;
		}
	}

	std::string timbre = Package::getPackage().getLibraryTimbreDefault(library);

	bool haveSolo = false;
	for (auto& t : this->project->tracks()) {
		if (t.solo()) {
			haveSolo = true;
			break;
		}
	}

	infinity::Track* track = this->project->add_tracks();
	track->set_name(name);
	track->set_color(color);
	track->set_library(library);
	track->set_timbrea(timbre);
	track->set_timbreb(timbre);
	track->set_isvoice(true);
	track->set_solo(false);
	track->set_mute(!haveSolo);

	for (auto& p : Package::getPackage().getEngineParam(engine)) {
		infinity::TrackParam* param = track->add_params();
		param->set_name(p.name);
		param->set_vmax(p.vMax);
		param->set_vmin(p.vMin);
		param->set_vdefault(p.vDefault);

		param->set_color(color);
	}

}

void DataModel::addWaveTrack(std::string name, std::string color)
{
	if (name.empty()) {
		return;
	}
	if (color.empty()) {
		return;
	}
	bool haveSolo = false;
	for (auto& t : this->project->tracks()) {
		if (t.solo()) {
			haveSolo = true;
			break;
		}
	}

	infinity::Track* track = this->project->add_tracks();
	track->set_name(name);
	track->set_color(color);
	track->set_isvoice(false);
	track->set_solo(false);
	track->set_mute(!haveSolo);
}

void DataModel::removeTrack(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (this->project->tracks_size() == 1) {
			return;
		}
		auto it = this->project->mutable_tracks()->begin() + trackIndex;
		this->project->mutable_tracks()->erase(it);
	}
}

void DataModel::setTrackName(int trackIndex, std::string name)
{
	if (name.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		this->project->mutable_tracks(trackIndex)->set_name(name);
	}
}

std::string DataModel::getTrackName(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).name();
	}
	return std::string();
}

void DataModel::setTrackColor(int trackIndex, std::string color)
{
	if (color.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		this->project->mutable_tracks(trackIndex)->set_color(color);
	}
}

std::string DataModel::getTrackColor(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).color();
	}
	return std::string();
}

void DataModel::setTrackLibrary(int trackIndex, std::string library)
{
	if (library.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (library == this->project->tracks(trackIndex).library()) {
			return;
		}
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getLibraryAvailable()) {
				if (i == library) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		std::string engine = Package::getPackage().getEngineName(library);
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getEngineAvailable()) {
				if (i == engine) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}

		std::string timbre = Package::getPackage().getLibraryTimbreDefault(library);

		this->project->mutable_tracks(trackIndex)->set_library(library);
		this->project->mutable_tracks(trackIndex)->set_timbrea(timbre);
		this->project->mutable_tracks(trackIndex)->set_timbreb(timbre);
	}
}

std::string DataModel::getTrackLibrary(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).library();
	}
	return std::string();
}

void DataModel::setTrackTimbreA(int trackIndex, std::string timbre)
{
	if (timbre.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (timbre == this->project->tracks(trackIndex).timbrea()) {
			return;
		}
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getLibraryTimbre(this->project->tracks(trackIndex).library())) {
				if (i == timbre) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		this->project->mutable_tracks(trackIndex)->set_timbrea(timbre);
	}
}

std::string DataModel::getTrackTimbreA(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).timbrea();
	}
	return std::string();
}

void DataModel::setTrackTimbreB(int trackIndex, std::string timbre)
{
	if (timbre.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (timbre == this->project->tracks(trackIndex).timbreb()) {
			return;
		}
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getLibraryTimbre(this->project->tracks(trackIndex).library())) {
				if (i == timbre) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		this->project->mutable_tracks(trackIndex)->set_timbreb(timbre);
	}
}

std::string DataModel::getTrackTimbreB(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).timbreb();
	}
	return std::string();
}

void DataModel::setTrackMute(int trackIndex, bool mute)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (mute == this->project->tracks(trackIndex).mute()) {
			return;
		}//未作改动
		if (this->project->tracks(trackIndex).solo()) {
			return;
		}//当前轨solo，mute不可改动，必为false
		if (!mute) {
			bool haveSolo = false;
			for (auto& t : this->project->tracks()) {
				if (t.solo()) {
					haveSolo = true;
					return;
				}
			}
		}//存在其他轨solo，当前mute不可改动，必为true
		this->project->mutable_tracks(trackIndex)->set_mute(mute);
	}
}

bool DataModel::getTrackMute(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).mute();
	}
	return false;
}

void DataModel::setTrackSolo(int trackIndex, bool solo)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (solo == this->project->tracks(trackIndex).solo()) {
			return;
		}//未作改动
		this->project->mutable_tracks(trackIndex)->set_solo(solo);
		if (solo) {
			this->project->mutable_tracks(trackIndex)->set_mute(false);//关闭当前轨mute
			for (int i = 0; i < this->project->tracks_size(); i++) {
				if (!this->project->tracks(i).solo()) {
					this->project->mutable_tracks(i)->set_mute(true);
				}
			}//将所有非solo轨设为mute
		}
		else  {
			bool haveSolo = false;
			for (auto& t : this->project->tracks()) {
				if (t.solo()) {
					haveSolo = true;
					break;
				}
			}//判断是否还存在solo
			if (haveSolo) {
				this->project->mutable_tracks(trackIndex)->set_mute(true);
			}//有solo，当前轨设为mute
			else {
				for (int i = 0; i < this->project->tracks_size(); i++) {
					if (this->project->tracks(i).mute()) {
						this->project->mutable_tracks(i)->set_mute(false);
					}
				}
			}//无solo，所有轨取消mute
		}
	}
}

bool DataModel::getTrackSolo(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).solo();
	}
	return false;
}


//Utils

std::pair<uint32_t, uint32_t> DataModel::Utils::getEP(uint32_t startBeat, uint32_t startTick, uint64_t length)
{
	length += startTick;
	startBeat += std::floor(length / 480.0);
	length %= 480;
	return std::make_pair(startBeat, static_cast<uint32_t>(length));
}
