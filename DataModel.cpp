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
			if (DataModel::Utils::SP(startBeat, startTick) < DataModel::Utils::SP(this->project->tracks(trackIndex).notes(0).startbeat(), this->project->tracks(trackIndex).notes(0).starttick())) {
				this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾建立空element
				for (int i = this->project->tracks(trackIndex).notes_size() - 2; i >= 0 ; i--) {
					this->project->mutable_tracks(trackIndex)->mutable_notes(i + 1)->CopyFrom(this->project->tracks(trackIndex).notes(i));
				}//element集体后移
				note = this->project->mutable_tracks(trackIndex)->mutable_notes(0);//腾出头element
			}
			else if (DataModel::Utils::SP(startBeat, startTick) >= DataModel::Utils::SP(this->project->tracks(trackIndex).notes(this->project->tracks(trackIndex).notes_size() - 1).startbeat(), this->project->tracks(trackIndex).notes(this->project->tracks(trackIndex).notes_size() - 1).starttick())) {
				note = this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾
			}
			else {
				this->project->mutable_tracks(trackIndex)->mutable_notes()->Add();//末尾建立空element
				for (int i = this->project->tracks(trackIndex).notes_size() - 2; i > 0; i--) {
					this->project->mutable_tracks(trackIndex)->mutable_notes(i + 1)->CopyFrom(this->project->tracks(trackIndex).notes(i));//element后移
					if (
						DataModel::Utils::SP(startBeat, startTick) >= DataModel::Utils::SP(this->project->tracks(trackIndex).notes(i - 1).startbeat(), this->project->tracks(trackIndex).notes(i - 1).starttick()) &&
						DataModel::Utils::SP(startBeat, startTick) < DataModel::Utils::SP(this->project->tracks(trackIndex).notes(i + 1).startbeat(), this->project->tracks(trackIndex).notes(i + 1).starttick())
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

void DataModel::setNotePlace(int trackIndex, int noteIndex, uint32_t startBeat, uint32_t startTick, uint64_t length)
{

}

//Utils

std::pair<uint32_t, uint32_t> DataModel::Utils::getEP(uint32_t startBeat, uint32_t startTick, uint64_t length)
{
	length += startTick;
	startBeat += std::floor(length / 480.0);
	length %= 480;
	return std::make_pair(startBeat, static_cast<uint32_t>(length));
}

uint64_t DataModel::Utils::SP(uint32_t startBeat, uint32_t startTick)
{
	return static_cast<uint64_t>(startBeat) * 480 + startTick;
}