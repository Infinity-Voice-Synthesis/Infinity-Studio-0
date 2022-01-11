#pragma once

#include <algorithm>
#include <string>
#include <list>
#include <functional>
#include <set>
#include <mutex>

#include "Package.h"

#include "Pb/project.pb.h"

class DataModel
{
	DataModel();
	~DataModel();

	static DataModel _model;
	
public:
	static DataModel& getModel();

	void setProjectTime();
	uint32_t getProjectTime();
	void setProjectBeat(uint32_t beat);
	uint32_t getProjectBeat();
	void setProjectTempo(double tempo);
	double getProjectTempo();
	void setProjectSRate(uint64_t sRate);
	uint64_t getProjectSRate();
	void setProjectBit(uint32_t bit);
	uint32_t getProjectBit();
	void setProjectQuantize(uint32_t quantize);
	uint32_t getProjectQuantize();
	void setProjectEditor(std::string editor);
	std::string getProjectEditor();
	void addProjectAuthor(std::string author);
	std::list<std::string> getProjectAuthors();
	//项目属性

	void addTrack(std::string name, std::string color);
	void removeTrack(int trackIndex);
	int countTrack();
	//轨道数量

	void setTrackName(int trackIndex, std::string name);
	std::string getTrackName(int trackIndex);
	void setTrackColor(int trackIndex, std::string color);
	std::string getTrackColor(int trackIndex);
	void setTrackMute(int trackIndex, bool mute);
	bool getTrackMute(int trackIndex);
	void setTrackSolo(int trackIndex, bool solo);
	bool getTrackSolo(int trackIndex);
	void setTrackGain(int trackIndex, double gain);
	double getTrackGain(int trackIndex);
	void setTrackPan(int trackIndex, double pan);
	double getTrackPan(int trackIndex);
	void setTrackMix(int trackIndex, double mix);
	double getTrackMix(int trackIndex);
	//轨道属性

	void addContainer(int trackIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pattern);
	void removeContainer(int trackIndex, int containerIndex);
	int countContainer(int trackIndex);
	//容器数量

	void setContainerPlace(int trackIndex, int containerIndex, uint32_t startBeat, uint32_t startTick, uint64_t length);
	uint32_t getContainerStartBeat(int trackIndex, int containerIndex);
	uint32_t getContainerStartTick(int trackIndex, int containerIndex);
	uint64_t getContainerLength(int trackIndex, int containerIndex);
	void setContainerPattern(int trackIndex, int containerIndex, uint32_t pattern);
	uint32_t getContainerPattern(int trackIndex, int containerIndex);
	//容器属性
	
	//void setTrackLibrary(int trackIndex, std::string library);
	//std::string getTrackLibrary(int trackIndex);
	//void setTrackDictionary(int trackIndex, std::string dictionary);
	//std::string getTrackDictionary(int trackIndex);
	//void setTrackTimbreA(int trackIndex, std::string timbre);
	//std::string getTrackTimbreA(int trackIndex);
	//void setTrackTimbreB(int trackIndex, std::string timbre);
	//std::string getTrackTimbreB(int trackIndex);
	
	////轨道属性

	//void addNote(int trackIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pitch, std::string name);
	//void removeNote(int trackIndex, int noteIndex);
	//int countNote(int trackIndex);
	////音符数量

	//void setNotePlace(int trackIndex, int noteIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pitch);
	//uint32_t getNoteStartBeat(int trackIndex, int noteIndex);
	//uint32_t getNoteStartTick(int trackIndex, int noteIndex);
	//uint64_t getNoteLength(int trackIndex, int noteIndex);
	//uint32_t getNotePitch(int trackIndex, int noteIndex);
	//void setNoteName(int trackIndex, int noteIndex, std::string name);
	//std::string getNoteName(int trackIndex, int noteIndex);
	//void setNoteTimbre(int trackIndex, int noteIndex, std::string timbre);
	//std::string getNoteTimbre(int trackIndex, int noteIndex);
	//void setNotePhonemes(int trackIndex, int noteIndex, std::vector<int64_t>& phonemes);
	//std::vector<std::pair<std::string, int64_t>> getNotePhonemes(int trackIndex, int noteIndex);
	//void setNoteFlags(int trackIndex, int noteIndex, std::string flags);
	//std::string getNoteFlags(int trackIndex, int noteIndex);
	//bool getNoteConsonant(int trackIndex, int noteIndex);
	//void setNoteGroup(int trackIndex, int noteIndex, int32_t group);//inside port
	//int32_t getNoteGroup(int trackIndex, int noteIndex);
	////音符属性
	
	//音符参数数量
	
	//删除参数样式时需检查当前参数是否属于当前引擎，如不属于，则删除参数且该参数不渲染
private:
	org::infinity::idm::Project* project = nullptr;
	std::mutex modelMutex;

	class Utils {
	public:
		static std::pair<uint32_t,uint32_t> getEP(uint32_t startBeat, uint32_t startTick, uint64_t length);
		static uint64_t getTick(uint32_t startBeat, uint32_t startTick);
		static std::pair<uint32_t, uint32_t> getBeat(uint64_t tick);
	};

	//std::function<void(int, uint32_t, uint32_t)> renderFunc;//渲染
	std::function<void(int)> renderFunc;//渲染
	std::function<void(void)> viewFunc;//刷新界面

	std::function<std::pair<std::map<std::string, int64_t>, bool>(std::string, std::string, std::string)> eSplitFunc;//调用引擎分词

};
