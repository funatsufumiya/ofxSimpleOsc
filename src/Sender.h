#pragma once

#include <string>
#include "ofxOsc.h"
#include "ofMain.h"

namespace ofxSimpleOsc {
	class Sender {
	protected:
		ofxOscSender sender;
		ofxOscMessage temp_message;

		void sendImpl(ofxOscMessage& message)
		{
			sender.sendMessage(message);
		}

		template<class Head, class ...Tail>
		void sendImpl(ofxOscMessage& message, const Head & head, const Tail & ...tail)
		{
			addArg(message, head);
			sendImpl(message, tail...);
		}

		template<class Head>
		void sendImpl(ofxOscMessage& message, const Head & head)
		{
			addArg(message, head);
			sendImpl(message);
		}

		template <typename T>
		void addArg(ofxOscMessage& m, T arg);

		template<>
		void addArg(ofxOscMessage & m, const ofColor& c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, ofColor c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, const ofFloatColor& c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, ofFloatColor c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, const ofShortColor& c)
		{
			m.addIntArg(c.r);
			m.addIntArg(c.g);
			m.addIntArg(c.b);
			m.addIntArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, ofShortColor c)
		{
			m.addIntArg(c.r);
			m.addIntArg(c.g);
			m.addIntArg(c.b);
			m.addIntArg(c.a);
		}

		template<>
		void addArg(ofxOscMessage & m, const ofRectangle& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.width);
			m.addFloatArg(r.height);
		}

		template<>
		void addArg(ofxOscMessage & m, ofRectangle r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.width);
			m.addFloatArg(r.height);
		}

		template<>
		void addArg(ofxOscMessage & m, const ofQuaternion& r)
		{
			m.addFloatArg(r.x());
			m.addFloatArg(r.y());
			m.addFloatArg(r.z());
			m.addFloatArg(r.w());
		}

		template<>
		void addArg(ofxOscMessage & m, ofQuaternion r)
		{
			m.addFloatArg(r.x());
			m.addFloatArg(r.y());
			m.addFloatArg(r.z());
			m.addFloatArg(r.w());
		}

		template<>
		void addArg(ofxOscMessage & m, const ofVec2f& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
		}

		template<>
		void addArg(ofxOscMessage & m, ofVec2f r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
		}

		template<>
		void addArg(ofxOscMessage & m, const ofVec3f& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.z);
		}

		template<>
		void addArg(ofxOscMessage & m, ofVec3f r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.z);
		}

		template<>
		void addArg(ofxOscMessage & m, int arg)
		{
			m.addIntArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, long arg)
		{
			m.addInt64Arg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, long long arg)
		{
			m.addInt64Arg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, float arg)
		{
			m.addFloatArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, double arg)
		{
			m.addDoubleArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, bool arg)
		{
			m.addBoolArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, char arg)
		{
			m.addCharArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, const string& arg)
		{
			m.addStringArg(arg);
		}

		template<>
		void addArg(ofxOscMessage & m, char const * arg)
		{
			m.addStringArg(arg);
		}

	public:
		Sender(){}
		~Sender(){
			sender.clear();
		}

		void setup(const std::string& host, int port)
		{
			sender.setup(host, port);
		}

		void send(ofxOscMessage & message, bool wrap_in_bundle)
		{
			sender.sendMessage(message, wrap_in_bundle);
		}

		template<class ...Args>
		void send(const std::string& address, const Args&... args)
		{
			temp_message.clear();
			temp_message.setAddress(address);

			sendImpl(temp_message, args...);
		}

		template<class Arg>
		void send(const std::string& address, const Arg& arg)
		{
			temp_message.clear();
			temp_message.setAddress(address);

			sendImpl(temp_message, arg);
		}

		void send(const std::string& address)
		{
			temp_message.clear();
			temp_message.setAddress(address);
			sender.sendMessage(temp_message);
		}
	};
};