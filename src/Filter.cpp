#include "Filter.h"

template<>
int ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsInt(i);
}

template<>
double ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsDouble(i);
}

template<>
float ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsFloat(i);
}

template<>
bool ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsBool(i);
}

template<>
char ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsChar(i);
}

template<>
long long ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsInt64(i);
}

template<>
long ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return m.getArgAsInt64(i);
}

template<>
ofBuffer ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return std::move(m.getArgAsBlob(i));
}

template<>
std::string ofxSimpleOsc::Filter::get(const ofxOscMessage& m, size_t i) {
    return std::move(m.getArgAsString(i));
}
