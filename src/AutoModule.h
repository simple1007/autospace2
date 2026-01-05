#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"     // DOM 파서
#include "rapidjson/error/en.h"
#include <unordered_map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>  // << stringstream을 위해 필요
#ifdef WIN322
#include <windows.h> // SetConsoleOutputCP 사용을 위해
#endif
#include <locale.h>    // setlocale 사용을 위해
#include <utf8cpp/utf8.h> // 다운로드한 utf8.h 헤더 포함
#include <chrono>
using namespace std;
using namespace rapidjson;


int get_count(const unordered_map<wstring, unordered_map<wstring, int>>& dict,const wstring& word, int n);


wstring tri_to_string(vector<wchar_t> text_arr, int i0, int i1, int i2, int i3);
string read_file(const string& filename);

Document read_json(const string& path);

bool hasKey(const unordered_map<wstring, int>& dict_json, const string& key);

bool hasKeyInt(const unordered_map<wstring, int>& dict_json, const wstring& key);


int json_parsing_error(const Document& d);

int makedict(const string& path, unordered_map<wstring, unordered_map<wstring, int>>& bigram, unordered_map<wstring, unordered_map<wstring, int>>& trigram);
class AutoModule
{
public:
	unordered_map<wstring, unordered_map<wstring, int>> bigram;
	unordered_map<wstring, unordered_map<wstring, int>> trigram;
    //Value::Object unigram = json["unigram"].GetObj();
    //Value::Object bigram = json["bigram"].GetObj();
    //Value::Object trigram = json["trigram"].GetObj();
	//AutoModule();
	//Document *dict = nullptr;
	// 2. 실제 객체 대신, 구현 구조체에 대한 포인터(스마트 포인터)를 멤버로 가집니다.
	void load_dict();
	bool chk_space(wchar_t t);
	//int make_count(int spaceidx, string zero, string one);
	float calc_prob(int count, int totalcount);
	wstring get_type(const wstring& text);
	void bi_make_count(int spaceidx, const wstring& one, int& r0, int& r1);
	void tri_make_count(int spaceidx, const wstring& one, int& r0, int& r1);
	/*int get_count(const string& word,const string& key, int n);
	bool chk_ngram(const string& ngram,int n);*/
	float calc_bigram(const wstring& text, int i);
	float calc_trigram(const wstring& text, int i);
	//AutoModule(const string& path);
	//AutoModule();
	//~AutoModule();
	//AutoModule(const AutoModule&) = delete;
	//AutoModule& operator=(const AutoModule&) = delete;
};

