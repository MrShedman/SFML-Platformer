#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SettingsParser
{
public:
	SettingsParser();
	~SettingsParser();

	bool loadFile(const std::string& filename);
	bool saveToFile() const;

	bool isChanged() const;

	void get(const std::string& param, std::string &value) const;
	void get(const std::string& param, bool &value) const;
	void get(const std::string& param, char &value) const;
	void get(const std::string& param, int &value) const;
	void get(const std::string& param, float &value) const;

	void set(const std::string& param, std::string value);
	void set(const std::string& param, bool value);
	void set(const std::string& param, char value);
	void set(const std::string& param, int value);
	void set(const std::string& param, float value);


private:
	int findIndex(const std::string& param) const;
	bool read();
	bool write() const;

	bool m_isChanged;
	std::string m_filename;
	std::vector<std::pair<std::string, std::string> > m_data;
	size_t m_size;
};