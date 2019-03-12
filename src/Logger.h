#pragma once

#include "ofxOsc.h"
#include <string>
#include <cctype>

namespace ofxSimpleOsc {

	class Logger {
	public:
		std::string toString(const ofxOscMessage & m, bool print_args)
		{
			std::stringstream ss;

			ss << m.getAddress();

			int num_args = m.getNumArgs();
			for (int i = 0; i < num_args; ++i) {
				auto v = getOscArg(m, i);
				ss << " " + v;
			}

			ss << "";

			return std::move(ss.str());
		}

		void log(const ofxOscMessage & m, bool print_args, const std::string& log_module = "ofxSimpleOsc::Logger")
		{
			std::string s = toString(m, print_args);
			ofLogNotice(log_module) << s;
		}

	private:
		std::string getOscArg(const ofxOscMessage& m, size_t i)
		{
			auto type = m.getArgType(i);

			switch (type) {
			case OFXOSC_TYPE_FLOAT:
				return ofToString(m.getArgAsFloat(i), 3);
			case OFXOSC_TYPE_INT32:
				return ofToString(m.getArgAsInt32(i));
			case OFXOSC_TYPE_INT64:
				return ofToString(m.getArgAsInt64(i));
			case OFXOSC_TYPE_DOUBLE:
				return ofToString(m.getArgAsDouble(i), 3);
			case OFXOSC_TYPE_TRUE:
				return "true";
			case OFXOSC_TYPE_FALSE:
				return "false";
			case OFXOSC_TYPE_CHAR:
			{
				char c = m.getArgAsChar(i);
				std::string s(1, c);
				return s;
			}
			case OFXOSC_TYPE_STRING:
				return m.getArgAsString(i);
			default:
			{
				auto loglevel = ofGetLogLevel();
				ofSetLogLevel(ofLogLevel::OF_LOG_SILENT);
				std::string s = m.getArgAsString(i);
				ofSetLogLevel(loglevel);
				return s;
			}
			}
		}

		bool is_int(const std::string & s)
		{
			return !s.empty() && std::find_if(s.begin(),
				s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
		}

		bool is_float(const std::string & s)
		{
			std::string::const_iterator it = s.begin();
			bool decimalPoint = false;
			int minSize = 0;
			if (s.size() > 0 && (s[0] == '-' || s[0] == '+')) {
				it++;
				minSize++;
			}
			while (it != s.end()) {
				if (*it == '.') {
					if (!decimalPoint) decimalPoint = true;
					else break;
				}
				else if (!std::isdigit(*it) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint)) {
					break;
				}
				++it;
			}
			return s.size() > minSize && it == s.end();
		}

		bool is_double(const std::string & s)
		{
			return is_type<double>(s);
		}

		template<typename T>
		bool is_type(const std::string & s)
		{
			T target;
			stringstream ss;
			ss << s;
			ss >> target;
			return ss.good();
		}

		std::vector<std::string> split(const std::string& s, char delimiter)
		{
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(s);
			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
			return tokens;
		}

	};

	static Logger logger = Logger();
}