#include "SettingsParser.h"

SettingsParser::SettingsParser() : m_size(0), m_isChanged(false)
{}

SettingsParser::~SettingsParser()
{
	saveToFile();
}


bool SettingsParser::loadFile(const std::string& filename)
{
	m_data.clear();
	m_size = 0;
	m_filename = filename;
	return read();
}


bool SettingsParser::saveToFile() const
{
	if (m_isChanged)
		return write();
	return true;
}


bool SettingsParser::read()
{
	std::ifstream in(m_filename);
	if (!in.is_open())
	{
		std::cerr << "Error: Unable to open settings file: \"" << m_filename << "\" for reading!" << std::endl;
		return false;
	}
	std::string line, param, value;
	while (!in.eof())
	{
		std::getline(in, line);
		if (line.size() > 0 && line[0] != '#')
		{
			size_t j = 0;
			size_t length = line.size();
			while (line[j] != ' ') j++;
			param = line.substr(0, j);
			while (line[j] == ' ' || line[j] == '=') j++;
			int a = j;
			while (j < length && (line[j] != ' ' || line[j] != '\n')) j++;
			int b = j;
			value = line.substr(a, b);
		}
		else
		{
			param = line;
			value = "";
		}
		m_data.push_back(make_pair(param, value));
		m_size++;
	}
	in.close();
	m_isChanged = false;
	return true;
}


bool SettingsParser::write() const
{
	std::ofstream out(m_filename);
	if (!out.is_open())
	{
		std::cerr << "Error: Unable to open settings file: \"" << m_filename << "\" for writing!" << std::endl;
		return false;
	}
	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_data[i].first[0] == '#' || m_data[i].first[0] == 0)
			out << m_data[i].first << std::endl;
		else
			out << m_data[i].first << " = " << m_data[i].second << std::endl;
	}
	out.close();
	return true;
}


bool SettingsParser::isChanged() const
{
	return m_isChanged;
}


int SettingsParser::findIndex(const std::string& param) const
{
	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_data[i].first[0] == '#')
			continue;
		if (m_data[i].first == param)
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}


void SettingsParser::get(const std::string& param, std::string &value) const
{
	int i = findIndex(param);
	if (i > -1)
	{
		value = m_data[i].second;
	}
}


void SettingsParser::get(const std::string& param, bool &value) const
{
	int i = findIndex(param);
	if (i > -1)
	{
		value = ((m_data[i].second == "TRUE") ? true : false);
	}
}


void SettingsParser::get(const std::string& param, char &value) const
{
	int i = findIndex(param);
	if (i > -1)
	{
		value = m_data[i].second[0];
	}
}


void SettingsParser::get(const std::string& param, int &value) const
{
	int i = findIndex(param);
	if (i > -1)
	{
		std::stringstream ss(m_data[i].second);
		ss >> value;
	}
}


void SettingsParser::get(const std::string& param, float &value) const
{
	int i = findIndex(param);
	if (i > -1)
	{
		std::stringstream ss(m_data[i].second);
		ss >> value;
	}
}


void SettingsParser::set(const std::string& param, std::string value)
{
	int i = findIndex(param);
	if (i > -1)
	{
		m_data[i].second = value;
	}

	m_isChanged = true;
}


void SettingsParser::set(const std::string& param, bool value)
{
	int i = findIndex(param);
	if (i > -1)
	{
		m_data[i].second = (value) ? "TRUE" : "FALSE";
	}

	m_isChanged = true;
}


void SettingsParser::set(const std::string& param, char value)
{
	int i = findIndex(param);
	if (i > -1)
	{
		std::string tmp = "";
		tmp = value;
		m_data[i].second = tmp;
	}

	m_isChanged = true;
}


void SettingsParser::set(const std::string& param, int value)
{
	int i = findIndex(param);
	if (i > -1)
	{
		std::stringstream ss;
		ss << value;
		m_data[i].second = ss.str();
	}

	m_isChanged = true;
}


void SettingsParser::set(const std::string& param, float value)
{
	int i = findIndex(param);
	if (i > -1)
	{
		std::stringstream ss;
		ss << value;
		m_data[i].second = ss.str();
	}

	m_isChanged = true;
}