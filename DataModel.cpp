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

	project->set_time(0);
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

void DataModel::setProjectTime()
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
	if (minTime == this->project->time()) {
		return;
	}
	this->project->set_time(minTime);//time永远与最后元素齐平
	this->viewFunc();
}

uint32_t DataModel::getProjectTime()
{
	return this->project->time();
}

void DataModel::setProjectBeat(uint32_t beat)
{
	if (beat > 0) {
		if (beat == this->project->beat()) {
			return;
		}
		this->project->set_beat(beat);
		this->viewFunc();
	}
}

uint32_t DataModel::getProjectBeat()
{
	return this->project->beat();
}

void DataModel::setProjectTempo(double tempo)
{
	if (tempo > 0) {
		if (tempo == this->project->tempo()) {
			return;
		}
		this->project->set_tempo(tempo);
		for (int i = 0; i < this->project->tracks_size(); i++) {
			this->renderFunc(i, 0, this->project->time());
		}
		this->viewFunc();
	}
}

double DataModel::getProjectTempo()
{
	return this->project->tempo();
}

void DataModel::setProjectSRate(uint64_t sRate)
{
	if (sRate > 0) {
		if (sRate == this->project->srate()) {
			return;
		}
		this->project->set_srate(sRate);
		for (int i = 0; i < this->project->tracks_size(); i++) {
			this->renderFunc(i, 0, this->project->time());
		}
		this->viewFunc();
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
	std::string dictionary = Package::getPackage().getLibraryDictionaryDefault(library);
	{
		bool flag = false;
		for (auto& i : Package::getPackage().getDictionaryAvailable()) {
			if (i == dictionary) {
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
	track->set_dictionary(dictionary);
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

	this->viewFunc();
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

	this->viewFunc();
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
	this->viewFunc();
}

int DataModel::countTrack()
{
	return this->project->tracks_size();
}

void DataModel::setTrackName(int trackIndex, std::string name)
{
	if (name.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		this->project->mutable_tracks(trackIndex)->set_name(name);
		this->viewFunc();
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
		this->viewFunc();
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
		std::string libraryCurrent = this->project->tracks(trackIndex).library();
		if (library == libraryCurrent) {
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
		std::string dictionary = Package::getPackage().getLibraryDictionaryDefault(library);
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getDictionaryAvailable()) {
				if (i == dictionary) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		std::string engine = Package::getPackage().getEngineName(library);
		std::string engineCurrent = Package::getPackage().getEngineName(libraryCurrent);
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
		this->project->mutable_tracks(trackIndex)->set_dictionary(dictionary);
		this->project->mutable_tracks(trackIndex)->set_timbrea(timbre);
		this->project->mutable_tracks(trackIndex)->set_timbreb(timbre);

		if (engine != engineCurrent) {
			auto epl = Package::getPackage().getEngineParam(engine);//获取新引擎参数表
			auto ckF = [epl](std::string name)->bool {
				bool flag = false;
				for (auto& i : epl) {
					if (i.name == name) {
						flag = true;
						break;
					}
				}
				return flag;
			};//检查参数是否存在于引擎的列表中
			std::set<std::string> paramL;//已存在的参数
			for (auto it = this->project->mutable_tracks(trackIndex)->mutable_params()->begin(); it != this->project->mutable_tracks(trackIndex)->mutable_params()->end(); it++) {
				if ((*it).patterns_size() == 0) {
					if (!ckF((*it).name())) {
						it = this->project->mutable_tracks(trackIndex)->mutable_params()->erase(it);
						continue;
					}
				}
				paramL.insert((*it).name());
			}//后侧迭代器在移除元素时会失效
			for (auto& p : epl) {
				if (paramL.count(p.name) == 0) {
					infinity::TrackParam* param = this->project->mutable_tracks(trackIndex)->add_params();
					param->set_name(p.name);
					param->set_vmax(p.vMax);
					param->set_vmin(p.vMin);
					param->set_vdefault(p.vDefault);

					param->set_color(this->project->tracks(trackIndex).color());
				}
			}//添加参数
		}//调整轨道参数

		if (engine != engineCurrent) {
			auto epl = Package::getPackage().getEngineNoteParam(engine);//获取新引擎参数表
			auto ckF = [epl](std::string name)->bool {
				bool flag = false;
				for (auto& i : epl) {
					if (i.name == name) {
						flag = true;
						break;
					}
				}
				return flag;
			};//检查参数是否存在于引擎的列表中
			for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);

				std::set<std::string> paramL;//已存在的参数
				for (auto it = note->mutable_params()->begin(); it != note->mutable_params()->end(); it++) {
					if (!ckF((*it).name())) {
						it = note->mutable_params()->erase(it);
						continue;
					}
					paramL.insert((*it).name());
				}//后侧迭代器在移除元素时会失效
				for (auto& p : epl) {
					if (paramL.count(p.name) == 0) {
						infinity::NoteParam* param = note->add_params();
						param->set_name(p.name);
						param->set_vmax(p.vMax);
						param->set_vmin(p.vMin);
						param->set_vdefault(p.vDefault);
						param->set_value(p.vDefault);
					}
				}//添加参数
			}
		}//调整音符参数

		if (Package::getPackage().getEngineSplit(engine)) {
			for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = this->eSplitFunc(engine, dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}
		}//调用引擎分词器
		else {
			for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = Package::getPackage().getDictionaryPhoneme(dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}
		}//使用字典分词

		this->renderFunc(trackIndex, 0, this->project->time());
		this->viewFunc();
	}
}

std::string DataModel::getTrackLibrary(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).library();
	}
	return std::string();
}

void DataModel::setTrackDictionary(int trackIndex, std::string dictionary)
{
	if (dictionary.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (dictionary == this->project->tracks(trackIndex).dictionary()) {
			return;
		}
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getDictionaryAvailable()) {
				if (i == dictionary) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		std::string engine = Package::getPackage().getEngineName(this->project->tracks(trackIndex).library());
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

		this->project->mutable_tracks(trackIndex)->set_dictionary(dictionary);

		if (Package::getPackage().getEngineSplit(engine)) {
			for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = this->eSplitFunc(engine, dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}
		}//调用引擎分词器
		else {
			for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = Package::getPackage().getDictionaryPhoneme(dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}
		}//使用字典分词

		this->renderFunc(trackIndex, 0, this->project->time());
		this->viewFunc();
	}
}

std::string DataModel::getTrackDictionary(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).dictionary();
	}
	return std::string();
}


void DataModel::setTrackTimbreA(int trackIndex, std::string timbre)
{
	if (timbre.empty()) {
		return;
	}
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		std::string timbreNow = this->project->tracks(trackIndex).timbrea();
		if (timbre == timbreNow) {
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

		for (int i = 0; i < this->project->tracks(trackIndex).notes_size(); i++) {
			if (this->project->tracks(trackIndex).notes(i).timbre() != timbreNow) {
				continue;
			}//修改过音色的音符不受影响
			this->project->mutable_tracks(trackIndex)->mutable_notes(i)->set_timbre(timbre);
		}//音色A决定音符主音色

		this->renderFunc(trackIndex, 0, this->project->time());
		this->viewFunc();
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

		this->renderFunc(trackIndex, 0, this->project->time());
		this->viewFunc();
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

		this->viewFunc();
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
		this->viewFunc();
	}
}

bool DataModel::getTrackSolo(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).solo();
	}
	return false;
}

void DataModel::addNote(int trackIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pitch, std::string name)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (length == 0) {
			return;
		}
		if (startTick >= 480) {
			startBeat += startTick / 480;
			startTick %= 480;
		}
		std::string dictionary = Package::getPackage().getLibraryDictionaryDefault(this->project->tracks(trackIndex).library());
		{
			bool flag = false;
			for (auto& i : Package::getPackage().getDictionaryAvailable()) {
				if (i == dictionary) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				return;
			}
		}
		std::string engine = Package::getPackage().getEngineName(this->project->tracks(trackIndex).library());
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

		infinity::Note* note = nullptr;
		if (this->project->tracks(trackIndex).notes_size() > 0) {
			if (DataModel::Utils::getTick(startBeat, startTick) < DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(0).startbeat(), this->project->tracks(trackIndex).notes(0).starttick())) {
				this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾建立空element
				for (int i = this->project->tracks(trackIndex).notes_size() - 2; i >= 0 ; i--) {
					this->project->mutable_tracks(trackIndex)->mutable_notes(i + 1)->CopyFrom(this->project->tracks(trackIndex).notes(i));
				}//element集体后移
				note = this->project->mutable_tracks(trackIndex)->mutable_notes(0);//腾出头element
			}
			else if (DataModel::Utils::getTick(startBeat, startTick) >= DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(this->project->tracks(trackIndex).notes_size() - 1).startbeat(), this->project->tracks(trackIndex).notes(this->project->tracks(trackIndex).notes_size() - 1).starttick())) {
				note = this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾
			}
			else {
				this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾建立空element
				for (int i = this->project->tracks(trackIndex).notes_size() - 2; i > 0; i--) {
					this->project->mutable_tracks(trackIndex)->mutable_notes(i + 1)->CopyFrom(this->project->tracks(trackIndex).notes(i));//element后移
					if (
						DataModel::Utils::getTick(startBeat, startTick) >= DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i - 1).startbeat(), this->project->tracks(trackIndex).notes(i - 1).starttick()) &&
						DataModel::Utils::getTick(startBeat, startTick) < DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i + 1).startbeat(), this->project->tracks(trackIndex).notes(i + 1).starttick())
						) {//如果当前element符合要求
						note = this->project->mutable_tracks(trackIndex)->mutable_notes(i);//移动element空出位置即是插入位置
					}
				}
			}
		}
		else {
			note = this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//唯一一个
		}

		note->set_startbeat(startBeat);
		note->set_starttick(startTick);
		note->set_length(length);
		note->set_pitch(pitch);

		note->set_name(name);
		note->set_timbre(this->project->tracks(trackIndex).timbrea());

		if (Package::getPackage().getEngineSplit(engine)) {
			std::pair<std::map<std::string, int64_t>, bool> phonemeM = this->eSplitFunc(engine, dictionary, name);
			for (auto& p : phonemeM.first) {
				infinity::utils::Pair* pair = note->add_phonemes();
				pair->set_key(p.first);
				pair->set_value(p.second);
			}
			note->set_consonant(phonemeM.second);
		}//调用引擎分词器
		else {
			std::pair<std::map<std::string, int64_t>, bool> phonemeM = Package::getPackage().getDictionaryPhoneme(dictionary, name);
			for (auto& p : phonemeM.first) {
				infinity::utils::Pair* pair = note->add_phonemes();
				pair->set_key(p.first);
				pair->set_value(p.second);
			}
			note->set_consonant(phonemeM.second);
		}//使用字典分词

		auto epl = Package::getPackage().getEngineNoteParam(engine);//获取引擎参数表
		for (auto& p : epl) {
			infinity::NoteParam* param = note->add_params();
			param->set_name(p.name);
			param->set_vmax(p.vMax);
			param->set_vmin(p.vMin);
			param->set_vdefault(p.vDefault);
			param->set_value(p.vDefault);
		}//添加参数

		std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);
		this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
		this->viewFunc();
	}
}

void DataModel::removeNote(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			auto it = this->project->mutable_tracks(trackIndex)->mutable_notes()->begin() + noteIndex;
			uint32_t startBeat = (*it).startbeat();
			uint32_t startTick = (*it).starttick();
			std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, (*it).length());
			this->project->mutable_tracks(trackIndex)->mutable_notes()->erase(it);

			this->setProjectTime();//调整时长

			this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			this->viewFunc();
		}
	}
}

int DataModel::countNote(int trackIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		return this->project->tracks(trackIndex).notes_size();
	}
	return -1;
}

void DataModel::setNotePlace(int trackIndex, int noteIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pitch)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			if (length == 0) {
				return;
			}
			if (startTick >= 480) {
				startBeat += startTick / 480;
				startTick %= 480;
			}
			uint32_t currentStartBeat = this->project->tracks(trackIndex).notes(noteIndex).startbeat();
			uint32_t currentStartTick = this->project->tracks(trackIndex).notes(noteIndex).starttick();
			uint64_t currentLength = this->project->tracks(trackIndex).notes(noteIndex).length();

			if (
				currentStartBeat == startBeat &&
				currentStartTick == startTick &&
				currentLength == length
				) {
				return;
			}

			std::pair<uint32_t, uint32_t> currentEP = DataModel::Utils::getEP(currentStartBeat, currentStartTick, currentLength);
			std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);

			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_startbeat(startBeat);
			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_starttick(startTick);
			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_length(length);
			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_pitch(pitch);

			if (noteIndex > 0) {
				for (int i = noteIndex; i > 0; i--)
				{
					if (DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i).startbeat(), this->project->tracks(trackIndex).notes(i).starttick()) < DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i - 1).startbeat(), this->project->tracks(trackIndex).notes(i - 1).starttick())) {
						infinity::Note temp(this->project->tracks(trackIndex).notes(i));
						this->project->mutable_tracks(trackIndex)->mutable_notes(i)->CopyFrom(this->project->tracks(trackIndex).notes(i - 1));
						this->project->mutable_tracks(trackIndex)->mutable_notes(i - 1)->CopyFrom(temp);
					}
					else {
						break;
					}
				}
			}
			if (noteIndex < this->project->tracks(trackIndex).notes_size() - 1) {
				for (int i = noteIndex; i < this->project->tracks(trackIndex).notes_size(); i++)
				{
					if (DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i).startbeat(), this->project->tracks(trackIndex).notes(i).starttick()) > DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(i + 1).startbeat(), this->project->tracks(trackIndex).notes(i + 1).starttick())) {
						infinity::Note temp(this->project->tracks(trackIndex).notes(i));
						this->project->mutable_tracks(trackIndex)->mutable_notes(i)->CopyFrom(this->project->tracks(trackIndex).notes(i + 1));
						this->project->mutable_tracks(trackIndex)->mutable_notes(i + 1)->CopyFrom(temp);
					}
					else {
						break;
					}
				}
			}//排序

			this->setProjectTime();//调整时长

			uint64_t CST = DataModel::Utils::getTick(currentStartBeat, currentStartTick);
			uint64_t CET = DataModel::Utils::getTick(currentEP.first, currentEP.second);
			uint64_t ST = DataModel::Utils::getTick(startBeat, startTick);
			uint64_t ET = DataModel::Utils::getTick(EP.first, EP.second);

			if (CST <= ET && ST <= CET) {
				uint64_t MST = std::min(CST, ST);
				uint64_t MET = std::max(CET, ET);
				std::pair<uint32_t, uint32_t> SB = DataModel::Utils::getBeat(MST);
				std::pair<uint32_t, uint32_t> EB = DataModel::Utils::getBeat(MET);

				this->renderFunc(trackIndex, SB.second > 0 ? SB.first + 1 : SB.first, EB.second > 0 ? EB.first + 1 : EB.first);
			}//前后变化区段重叠
			else {
				this->renderFunc(trackIndex, currentStartTick > 0 ? currentStartBeat + 1 : currentStartBeat, currentEP.second > 0 ? currentEP.first + 1 : currentEP.first);
				this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			}//前后变化区段分离

			this->viewFunc();
		}
	}
}

uint32_t DataModel::getNoteStartBeat(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).startbeat();
		}
	}
	return 0;
}

uint32_t DataModel::getNoteStartTick(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).starttick();
		}
	}
	return 0;
}

uint64_t DataModel::getNoteLength(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).length();
		}
	}
	return 0;
}

uint32_t DataModel::getNotePitch(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).pitch();
		}
	}
	return 0;
}

void DataModel::setNoteName(int trackIndex, int noteIndex, std::string name)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			if (name.empty()) {
				return;
			}

			if (name == this->project->tracks(trackIndex).notes(noteIndex).name()) {
				return;
			}

			std::string dictionary = this->project->tracks(trackIndex).dictionary();
			{
				bool flag = false;
				for (auto& i : Package::getPackage().getDictionaryAvailable()) {
					if (i == dictionary) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					return;
				}
			}
			std::string engine = Package::getPackage().getEngineName(this->project->tracks(trackIndex).library());
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

			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_name(name);

			if (Package::getPackage().getEngineSplit(engine)) {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = this->eSplitFunc(engine, dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}//调用引擎分词器
			else {
				infinity::Note* note = this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex);
				std::pair<std::map<std::string, int64_t>, bool> phonemeM = Package::getPackage().getDictionaryPhoneme(dictionary, note->name());
				note->clear_phonemes();
				for (auto& p : phonemeM.first) {
					infinity::utils::Pair* pair = note->add_phonemes();
					pair->set_key(p.first);
					pair->set_value(p.second);
				}
				note->set_consonant(phonemeM.second);
			}//使用字典分词

			uint32_t startBeat = this->project->tracks(trackIndex).notes(noteIndex).startbeat();
			uint32_t startTick = this->project->tracks(trackIndex).notes(noteIndex).starttick();
			uint64_t length = this->project->tracks(trackIndex).notes(noteIndex).length();

			std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);
			this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			this->viewFunc();
		}
	}
}

std::string DataModel::getNoteName(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).name();
		}
	}
	return std::string();
}

void DataModel::setNoteTimbre(int trackIndex, int noteIndex, std::string timbre)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			if (timbre.empty()) {
				return;
			}
			if (timbre == this->project->tracks(trackIndex).notes(noteIndex).timbre()) {
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

			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_timbre(timbre);

			uint32_t startBeat = this->project->tracks(trackIndex).notes(noteIndex).startbeat();
			uint32_t startTick = this->project->tracks(trackIndex).notes(noteIndex).starttick();
			uint64_t length = this->project->tracks(trackIndex).notes(noteIndex).length();

			std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);
			this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			this->viewFunc();
		}
	}
}

std::string DataModel::getNoteTimbre(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).timbre();
		}
	}
	return std::string();
}

void DataModel::setNotePhonemes(int trackIndex, int noteIndex, std::vector<int64_t>& phonemes)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			if (phonemes.empty()) {
				return;
			}

			std::vector<std::pair<std::string, int64_t>> currentPhonemes;
			for (auto& p : this->project->tracks(trackIndex).notes(noteIndex).phonemes()) {
				currentPhonemes.push_back(std::make_pair(p.key(), p.value()));
			}

			bool consonant = this->project->tracks(trackIndex).notes(noteIndex).consonant();

			if (phonemes.size() != currentPhonemes.size()) {
				return;
			}

			if (consonant) {
				if (phonemes.at(0) > 0) {
					return;
				}
			}
			else {
				if (phonemes.at(0) == 0) {
					return;
				}
			}//检查头辅音

			{
				int64_t minTemp = phonemes.at(0);
				for (int i = 1; i < phonemes.size(); i++) {
					if (phonemes.at(i) < minTemp || phonemes.at(i) < 0) {
						return;
					}
					minTemp = phonemes.at(i);
				}
			}//递增检查

			{
				int64_t endMax = this->project->tracks(trackIndex).notes(noteIndex).length();
				if (noteIndex < this->project->tracks(trackIndex).notes_size() - 1) {
					uint64_t endTick = DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(noteIndex + 1).startbeat(), this->project->tracks(trackIndex).notes(noteIndex + 1).starttick()) - this->project->tracks(trackIndex).notes(noteIndex + 1).phonemes(0).value();
					int64_t endLength = endTick - DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(noteIndex).startbeat(), this->project->tracks(trackIndex).notes(noteIndex).starttick());
					endMax = std::min(endMax, endLength);
				}
				if (phonemes.at(phonemes.size() - 1) > endMax) {
					return;
				}
			}//检查尾音出界

			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->mutable_phonemes()->Clear();
			for (int i = 0; i < phonemes.size(); i++) {
				infinity::utils::Pair* pair = this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->mutable_phonemes()->Add();
				pair->set_key(currentPhonemes.at(i).first);
				pair->set_value(phonemes.at(i));
			}

			bool overlap = false;
			if (consonant) {
				if (noteIndex > 0) {
					if (phonemes.at(0) != currentPhonemes.at(0).second) {
						uint64_t TST = DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(noteIndex).startbeat(), this->project->tracks(trackIndex).notes(noteIndex).starttick());
						uint64_t LET = DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(noteIndex - 1).startbeat(), this->project->tracks(trackIndex).notes(noteIndex - 1).starttick()) + this->project->tracks(trackIndex).notes(noteIndex - 1).length();
						if (
							TST - currentPhonemes.at(0).second < LET ||
							TST - phonemes.at(0) < LET
							) {
							overlap = true;
						}
					}
				}
			}//检查与前音符重叠

			if (overlap) {
				uint32_t startBeat = this->project->tracks(trackIndex).notes(noteIndex - 1).startbeat();
				uint32_t startTick = this->project->tracks(trackIndex).notes(noteIndex - 1).starttick();
				uint64_t lengthAll = DataModel::Utils::getTick(this->project->tracks(trackIndex).notes(noteIndex).startbeat(), this->project->tracks(trackIndex).notes(noteIndex).starttick()) - DataModel::Utils::getTick(startBeat, startTick) + this->project->tracks(trackIndex).notes(noteIndex).length();

				std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, lengthAll);
				this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			}
			else {
				uint32_t startBeat = this->project->tracks(trackIndex).notes(noteIndex).startbeat();
				uint32_t startTick = this->project->tracks(trackIndex).notes(noteIndex).starttick();
				uint64_t length = this->project->tracks(trackIndex).notes(noteIndex).length();

				std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);
				this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			}

			this->viewFunc();
		}
	}
}

std::vector<std::pair<std::string, int64_t>> DataModel::getNotePhonemes(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			std::vector<std::pair<std::string, int64_t>> phonemes;
			for (auto& p : this->project->tracks(trackIndex).notes(noteIndex).phonemes()) {
				phonemes.push_back(std::make_pair(p.key(), p.value()));
			}
			return phonemes;
		}
	}
	return std::vector<std::pair<std::string, int64_t>>();
}

void DataModel::setNoteFlags(int trackIndex, int noteIndex, std::string flags)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			if (flags == this->project->tracks(trackIndex).notes(noteIndex).flags()) {
				return;
			}
			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_flags(flags);

			uint32_t startBeat = this->project->tracks(trackIndex).notes(noteIndex).startbeat();
			uint32_t startTick = this->project->tracks(trackIndex).notes(noteIndex).starttick();
			uint64_t length = this->project->tracks(trackIndex).notes(noteIndex).length();

			std::pair<uint32_t, uint32_t> EP = DataModel::Utils::getEP(startBeat, startTick, length);
			this->renderFunc(trackIndex, startTick > 0 ? startBeat + 1 : startBeat, EP.second > 0 ? EP.first + 1 : EP.first);
			this->viewFunc();
		}
	}
}

std::string DataModel::getNoteFlags(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).flags();
		}
	}
	return std::string();
}

bool DataModel::getNoteConsonant(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).consonant();
		}
	}
	return false;
}

void DataModel::setNoteGroup(int trackIndex, int noteIndex, int32_t group)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			this->project->mutable_tracks(trackIndex)->mutable_notes(noteIndex)->set_group(group);
		}
	}
}

int32_t DataModel::getNoteGroup(int trackIndex, int noteIndex)
{
	if (trackIndex >= 0 && trackIndex < this->project->tracks_size()) {
		if (noteIndex >= 0 && noteIndex < this->project->tracks(trackIndex).notes_size()) {
			return this->project->tracks(trackIndex).notes(noteIndex).group();
		}
	}
	return -1;
}

//Utils

std::pair<uint32_t, uint32_t> DataModel::Utils::getEP(uint32_t startBeat, uint32_t startTick, uint64_t length)
{
	length += startTick;
	startBeat += std::floor(length / 480.0);
	length %= 480;
	return std::make_pair(startBeat, static_cast<uint32_t>(length));
}

uint64_t DataModel::Utils::getTick(uint32_t startBeat, uint32_t startTick)
{
	return static_cast<uint64_t>(startBeat) * 480 + startTick;
}

std::pair<uint32_t, uint32_t> DataModel::Utils::getBeat(uint64_t tick)
{
	return std::make_pair((uint32_t)(tick / 480), (uint32_t)(tick % 480));
}
