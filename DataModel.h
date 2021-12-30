﻿#pragma once

#include <algorithm>
#include <string>
#include <list>
#include <functional>
#include <set>

#include "Package.h"

#include "Pb/project.pb.h"

class DataModel
{
	DataModel();
	~DataModel();

	static DataModel _model;
	
public:
	static DataModel& getModel();

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
	//项目属性

	void addVoiceTrack(std::string name, std::string color, std::string library);
	void addWaveTrack(std::string name, std::string color);
	void removeTrack(int trackIndex);
	//轨道数量

	void setTrackName(int trackIndex, std::string name);
	std::string getTrackName(int trackIndex);
	void setTrackColor(int trackIndex, std::string color);
	std::string getTrackColor(int trackIndex);
	void setTrackLibrary(int trackIndex, std::string library);
	std::string getTrackLibrary(int trackIndex);
	void setTrackDictionary(int trackIndex, std::string dictionary);
	std::string getTrackDictionary(int trackIndex);
	void setTrackTimbreA(int trackIndex, std::string timbre);
	std::string getTrackTimbreA(int trackIndex);
	void setTrackTimbreB(int trackIndex, std::string timbre);
	std::string getTrackTimbreB(int trackIndex);
	void setTrackMute(int trackIndex, bool mute);
	bool getTrackMute(int trackIndex);
	void setTrackSolo(int trackIndex, bool solo);
	bool getTrackSolo(int trackIndex);
	//轨道属性

	void addNote(int trackIndex, uint32_t startBeat, uint32_t startTick, uint64_t length, uint32_t pitch, std::string name);
	
	//删除参数样式时需检查当前参数是否属于当前引擎，如不属于，则删除参数且该参数不渲染
private:
	infinity::Project* project = nullptr;

	class Utils {
	public:
		static std::pair<uint32_t,uint32_t> getEP(uint32_t startBeat, uint32_t startTick, uint64_t length);
		static uint64_t SP(uint32_t startBeat, uint32_t startTick);
	};

	std::function<void(int, uint32_t, uint32_t)> renderFunc;//渲染
	std::function<void(void)> viewFunc;//刷新界面

	std::function<std::pair<std::map<std::string, int64_t>, bool>(std::string, std::string, std::string)> eSplitFunc;//调用引擎分词

};
