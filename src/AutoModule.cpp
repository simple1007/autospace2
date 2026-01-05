#include "AutoModule.h"
#include <clocale>
#include <cstdlib>
#include "utils.h"
//#include <clocale>
#include <codecvt>
//#include <chrono>
//#include "rapidjson/"

//using namespace std;

// 네임스페이스
//using namespace rapidjson;
using namespace std;

wstring tri_to_string(vector<wchar_t> text_arr, int i0, int i1, int i2, int i3) {
    vector<wchar_t> text_tmp;
    if (i0 != -1)
        text_tmp.push_back(text_arr[i0]);
    else
        text_tmp.push_back(L' ');
        if (i1 != -1)
            text_tmp.push_back(text_arr[i1]);
        else
            text_tmp.push_back(L' ');
        if (i2 != -1)
            text_tmp.push_back(text_arr[i2]);
        else
            text_tmp.push_back(L' ');
        if (i3 != -1)
            text_tmp.push_back(text_arr[i3]);
        else
            text_tmp.push_back(L' ');
        wstring res(text_tmp.begin(), text_tmp.end());
        //wcout << res << endl;
        return res;
}
string read_file(const string& filename) {
    //std::string filename = "autospace_with_kcc.json";
    // 1. ifstream 객체 생성 및 파일 열기
    std::ifstream file_in(filename);

    // 2. 파일이 성공적으로 열렸는지 확인
    if (!file_in.is_open()) {
        return "Error: " + filename + " 파일을 열 수 없습니다."; // 오류 코드로 프로그램 종료
    }
    stringstream buffer;
    buffer << file_in.rdbuf();
    file_in.close();

    //cout << res << endl;
    string res = buffer.str();
    //const char* resc = res.c_str();
        //buffer.
    //cout << "sddfasf" << endl;
    //cout << string(resc) << endl;
    return  res;
}

Document read_json(const string& path) {
    string dict_str = read_file(path);
    Document dict_json;

    dict_json.Parse(dict_str.c_str());
    return dict_json;
    //return d;
    //cout << "eeerrrr" << endl;
}

bool hasKey(const unordered_map<wstring, int>& dict_json, const wstring& key) {
    //if (dict_json/*.HasMember(key) && dict_json[key].IsObject()) {
    //    return true;
    //}*/
    //string key_ = ws2s(key);
    if (dict_json.count(key) > 0) {
        return true;
    }

    return false;
}

bool hasKeyInt(const unordered_map<wstring, int>& dict_json, const wstring& key) {
    //if (dict_json/*.HasMember(key) && dict_json[key].IsObject()) {
    //    return true;
    //}*/
    //string key_ = ws2s(key);
    if (dict_json.count(key) > 0) {
        return true;
    }

    return false;
}


int json_parsing_error(const Document& d) {

    //cout << "eeerrrr" << endl;
    if (d.HasParseError()) {
        std::cerr << "JSON parse error: "
            << GetParseError_En(d.GetParseError())
            << " (Offset: " << d.GetErrorOffset() << ")"
            << std::endl;
        return 1;
    }
    return 0;
}

int makedict(const string& path, unordered_map<wstring, unordered_map<wstring, int>>& bigram, unordered_map<wstring, unordered_map<wstring, int>>& trigram) {
    setlocale(LC_ALL, "");
    Document json = read_json(path);
    int error = json_parsing_error(json);
    Value::Object bigram_ = json["bigram"].GetObj();
    Value::Object trigram_ = json["trigram"].GetObj();
    //vector<string> res;
    //std::unordered_map<wstring, std::unordered_map<std::wstring, int> > scores;
    //bigram_.begin
    auto start = get_startt();
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    //std::locale::global(std::locale("")); // 시스템 기본 로케일 설정
#ifdef WIN32
    std::wofstream bifile(L"bigram.txt");
#else
    std::wofstream bifile("bigram.txt");
#endif
    bifile.imbue(utf8_locale);
    //std::wofstream bifile;
    //bifile.open("bigram.txt", std::ios_base::out | std::ios_base::binary);

    // UTF-8 BOM (Byte Order Mark) 추가
    //myFile.write("\xEF\xBB\xBF", 3);

    //std::string myString = "안녕하세요, UTF-8 파일입니다.";
    //bifile.imbue(std::locale(""));
    //myFile.close();

    for (rapidjson::Value::MemberIterator itr = bigram_.begin(); itr != bigram_.end(); ++itr) {
    //    //cout << itr->name.GetString() << endl;
    //    if 
    //    exit(1);
        string key1(itr->name.GetString());
        wstring key1_ = s2ws(key1);
        //wcout << s2ws(key1) << endl;
        //res.push_back(key1);
        Value::Object val = itr->value.GetObj();
        for (rapidjson::Value::MemberIterator itr2 = val.begin(); itr2 != val.end(); ++itr2) {
            //itr->

            string key2(itr2->name.GetString());
            wstring key2_ = s2ws(key2);
            int val = itr2->value.GetInt();
            bigram[key1_][key2_] = val;
            //wstring line = key1_ + L"\t" + key2_ + L"\t" + to_wstring(val);
            if (val > 300)
                bifile << key1_ << L"\t" << key2_ << L"\t" << to_wstring(val) << endl;
            //string res2(res.data());
            //wcout << s2ws(key2) << L" " << itr2->value.GetInt() << endl;
            //wcout << s2ws(res) << endl;
        }
    }
    bifile.close();

    //std::wofstream trifile;
    //std::locale::global(std::locale(""));
#ifdef WIN32
    std::wofstream trifile(L"trigram.txt");
#else
    std::wofstream trifile("trigram.txt");
#endif
    trifile.imbue(utf8_locale);
    //trifile.open("trigram.txt", std::ios_base::out | std::ios_base::binary);
    //trifile.imbue(std::locale(""));
    for (rapidjson::Value::MemberIterator itr = trigram_.begin(); itr != trigram_.end(); ++itr) {
        //    //cout << itr->name.GetString() << endl;
        //    if 
        //    exit(1);
        string key1(itr->name.GetString());
        wstring key1_ = s2ws(key1);
        //wcout << s2ws(key1) << endl;
        //res.push_back(key1);
        Value::Object val = itr->value.GetObj();
        for (rapidjson::Value::MemberIterator itr2 = val.begin(); itr2 != val.end(); ++itr2) {
            //itr->

            string key2(itr2->name.GetString());
            wstring key2_ = s2ws(key2);
            int val = itr2->value.GetInt();
            trigram[key1_][key2_] = val;
            if (val > 300)
                trifile << key1_ << L"\t" << key2_ << L"\t" << to_wstring(val) << endl;
            //string res2(res.data());
            //wcout << s2ws(key2) << L" " << itr2->value.GetInt() << endl;
            //wcout << s2ws(res) << endl;
        }
    }
    trifile.close();
    timer(L"dict 로딩", start);

    //bifile.w/*rite(reinterpret_cast<wchar_t*>(&bigram), sizeof(unordered_map<wstring, unordered_map<wstring, int>>));
    //trifile.write(reinterpret_cast<wchar_t*>(&trigram), sizeof(unordered_map<wstring, unordered_map<wstring, int>>));
    //bifile.close();
    //trifile.*/close();
    exit(0);
    return 1;
    //wcout << L"--------------" << endl;
    //for (string s : res) {
    //    //wcout << s2ws(s) << endl;
    //    //bigram_.begin();
    //    Value::Object bigram_ = json["bigram"].GetObj();
    //    Value::Object val = bigram_[s.c_str()].GetObj();
    //    for (rapidjson::Value::MemberIterator itr = val.begin(); itr != val.end(); ++itr) {
    //        //itr->
    //        
    //        string res = itr->name.GetString();
    //        string res2(res.data());
    //        wcout << s2ws(res2) << endl;
    //        //wcout << s2ws(res) << endl;
    //    }
    //}

    //if (!error && hasKey(json, "unigram") && hasKey(json, "bigram") && hasKey(json, "trigram"))
    //    return json;
    //exit(1);
}

void split_(wstring s, wchar_t sep, unordered_map<wstring, unordered_map<wstring, int>>& ngram) {
    //cout << s << endl;
    //wstring s_ = s2ws(s);
    //wcout << s << endl;
    vector<wchar_t> svector(s.begin(), s.end());

    //vector<wstring> resvector;
    vector<wchar_t> tmp;
    vector<wstring> splittmp;
    //wcout << svector.size() << endl;
    for (int i = 0; i < svector.size(); i++) {
        wchar_t cur = svector[i];
        //wcout << cur << endl;
        if (cur != sep)
            tmp.push_back(cur);
        else {
            //wcout << cur << endl;
            wstring wtmp(tmp.begin(), tmp.end());
            
            if (strip(wtmp).compare(L"")!=0){
                try{
                    //wcout << wtmp << endl;
                    splittmp = split(wtmp, L'\t');
                    if (splittmp.size() == 3)
                        ngram[splittmp[0]][splittmp[1]] = stoi(splittmp[2]);
                }
                catch (exception e) {
                    wcout << e.what() << endl;
                    wcout << wtmp << endl;
                    exit(0);
                }
            }
            //resvector.push_back(wtmp);
            //wcout << wtmp << endl;
            tmp.clear();
            //return L"";
        }

    }
    wstring wtmp(tmp.begin(), tmp.end());
    if (strip(wtmp).compare(L"") != 0){
        splittmp = split(wtmp, L'\t');
        ngram[splittmp[0]][splittmp[1]] = stoi(splittmp[2]);
    }
    tmp.clear();
    //resvector.push_back(wtmp);
    //wcout << wstring(tmp.begin(), tmp.end()) << endl;
    //return resvector;
}

int readdict(unordered_map<wstring, unordered_map<wstring, int>>& bigram, unordered_map<wstring, unordered_map<wstring, int>>& trigram,string bidict_path,string tridict_path) {
    // 1. 파일을 읽기 위해 wifstream 객체 생성
    auto start = get_startt();
    setlocale(LC_ALL, "");
    
    std::wifstream file(bidict_path);

    // 2. 로케일을 설정하여 UTF-8 파일을 올바르게 처리하도록 함
    // 시스템에 따라 ".UTF-8" 또는 "ko_KR.UTF-8" 등으로 변경할 수 있습니다.
    // Windows 환경에서는 _setmode 함수를 사용할 수도 있습니다.
    //std::locale::global(std::locale("")); // 기본 시스템 로케일 사용
    //file.imbue(std::locale("ko_KR.UTF-8")); // 파일 스트림에 UTF-8 로케일 설정
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    file.imbue(utf8_locale);
    // 3. 파일 열기 성공 여부 확인
    if (!file.is_open()) {
        std::wcerr << L"파일을 열 수 없습니다!" << std::endl;
        return 1;
    }

    vector<wstring> tmp;
    // 4. wstring 변수에 줄 단위로 읽어들이기
    std::wstring line;
    //file >> line;
    //wcout << line << endl;
    //exit(0);
    //wchar_t line[20] = { 0, };
    while (getline(file,line)) {
        //std::wcout << line << std::endl;
        //file >> line;
        //wcout << line << endl;
        //exit(1);
        wstring line_(line);
        if (strip(line_).compare(L"") != 0){
            tmp = split(strip(line_), L'\t');
            //wcout << 
            bigram[tmp[0]][tmp[1]] = stoi(tmp[2]);
        }
    }
   /* wstringstream ss;
    ss << file.rdbuf();
    line = ss.str();
    split_(line, L'\n', bigram);*/
    //for (wstring s : split(line,L'\n')) {
    //    //wcout << s << endl;
    //    if (strip(s).compare(L"") != 0) {
    //        tmp = split(s, L'\t');
    //        bigram[tmp[0]][tmp[1]] = stoi(tmp[2]);
    //    }
    //}

    // 5. 파일 닫기 (file 객체가 범위를 벗어나면 자동으로 닫힙니다)
    file.close();
    timer(L"bigram", start);
    std::wifstream file2(tridict_path);

    // 2. 로케일을 설정하여 UTF-8 파일을 올바르게 처리하도록 함
    // 시스템에 따라 ".UTF-8" 또는 "ko_KR.UTF-8" 등으로 변경할 수 있습니다.
    // Windows 환경에서는 _setmode 함수를 사용할 수도 있습니다.
    //std::locale::global(std::locale("")); // 기본 시스템 로케일 사용
    //file.imbue(std::locale("ko_KR.UTF-8")); // 파일 스트림에 UTF-8 로케일 설정
    //std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    start = get_startt();
    file2.imbue(utf8_locale);
    // 3. 파일 열기 성공 여부 확인
    if (!file2.is_open()) {
        std::wcerr << L"파일을 열 수 없습니다!" << std::endl;
        return 1;
    }

    //vector<wstring> tmp;
    // 4. wstring 변수에 줄 단위로 읽어들이기
    std::wstring line2;
    while (getline(file2, line2)) {
        //std::wcout << line << std::endl;
        //file >> line;
        //wcout << line << endl;
        //exit(1);
        //wstring line2_(line2);
        if (strip(line2).compare(L"") != 0) {
            tmp = split(strip(line2), L'\t');
            //wcout << 
            trigram[tmp[0]][tmp[1]] = stoi(tmp[2]);
        }
    }
    //wchar_t line2[20] = { 0, };
    //while (file2.getline(line2,20)) {
    //    //std::wcout << line << std::endl;
    //    //file2 >> line2;
    //    wstring line2_(line2);
    //    if (strip(line2_).compare(L"") != 0) {
    //        tmp = split(strip(line2_), L'\t');
    //        trigram[tmp[0]][tmp[1]] = stoi(tmp[2]);
    //    }
    //}
    //wstringstream ss2;
    //ss2 << file2.rdbuf();
    //line2 = ss2.str();
    //split_(line2, L'\n', trigram);
    //// 5. 파일 닫기 (file 객체가 범위를 벗어나면 자동으로 닫힙니다)
    ////for (wstring s : split(line2,L'\n')) {
    ////    //wcout << s << endl;
    ////    if (strip(s).compare(L"") != 0) {
    ////        tmp = split(s, L'\t');
    ////        trigram[tmp[0]][tmp[1]] = stoi(tmp[2]);
    ////    }
    ////}
    file2.close();
    timer(L"trigram", start);
    return 0;
    // 읽어온 내용 출력
    /*std::wcout << L"파일 내용:" << std::endl;
    for (const auto& l : lines) {
        std::wcout << l << std::endl;
    }*/
}
// unordered_map<wstring, unordered_map<wstring, int>> trigram;
// unordered_map<wstring, unordered_map<wstring, int>> bigram;
//int flag = makedict("autospace_with_kcc.json",bigram, trigram);
void AutoModule::load_dict(){
    const char* bipath = std::getenv("BIDICT_PATH");
    const char* tripath = std::getenv("TRIDICT_PATH");

    int flag = readdict(this->bigram, this->trigram,string(bipath),string(tripath));
    if (flag){
        cout << "Load Dict Error" << endl;
        exit(1);
    }
}

bool chk_ngram(const wstring& ngram_, int n) {
    //wstring ngram_ = s2ws(ngram);
    if (ngram_.size() == n + 1)
        return true;
    return false;
}
int get_count(unordered_map<wstring, int>& dict,const wstring& word, int n) {
    if (chk_ngram(word, n)) {
        //string word_ = ws2s(word);
        if (hasKeyInt(dict, word)) {
            return dict[word];
        }
        return 0;
    }
    return 0;
}

// 2. .h 에서 전방 선언했던 Impl 구조체를 *여기서 정의*합니다.
//    rapidjson 객체는 이 구조체 안에 멤버로 둡니다.

// 4. 소멸자: ⭐️ 매우 중요!
//    std::unique_ptr<Impl>은 소멸될 때 Impl의 정의를 알아야 합니다.
//    Impl의 정의는 이 .cpp 파일에만 있으므로, 소멸자도 반드시 여기에 정의해야 합니다.
//AutoModule::~AutoModule() {
//    // 비어있더라도, 컴파일러가 올바른 위치에서 소멸자를 생성하도록 정의가 필요합니다.
//}

bool AutoModule::chk_space(wchar_t t) {
    if (t == L' ')
        return true;
    return false;
}

wstring AutoModule::get_type(const wstring& text_) {
    //wstring text_ = s2ws(text);
    std::vector<wchar_t> charVector(text_.begin(), text_.end());
    for (int i = 0; i < charVector.size(); i++) {
        if (this->chk_space(charVector[i]))
            charVector[i] = L'1';
        else
            charVector[i] = L'0';
    }
    wstring res(charVector.begin(), charVector.end());
    //wcout << res << endl;
    return res;
}

void AutoModule::bi_make_count(int spaceidx, const wstring& one, int& r0, int& r1) {
    //wstring zero_tmp = s2ws(one);
    wstring zero_tmp = one;
    vector<wchar_t> zero_(zero_tmp.begin(), zero_tmp.end());
    zero_[spaceidx] = L'0';
    wstring zero__(zero_.begin(), zero_.end());
    //wstring zero___ = zero__;
    wstring types = this->get_type(zero__);
    //wcout << L"zero count" << endl;
    //Value::Object dict = bigram;
    int zerocount = get_count(this->bigram[types], zero__, 2);
    //wcout << L"zero types 2" << endl;
    types = this->get_type(one);
    int onecount = get_count(this->bigram[types], one, 2);

    r0 = zerocount;
    r1 = onecount;
    //wcout << L"ddff" << r0 << r1 << endl;
}

void AutoModule::tri_make_count(int spaceidx, const wstring& one,int& r0, int& r1) {
    //wstring zero_tmp = one;
    //auto start = get_startt();
    vector<wchar_t> zero_(one.begin(), one.end());
    zero_[spaceidx] = L'0';
    wstring zero__(zero_.begin(), zero_.end());
    //wstring zero___ = zero__;
    wstring zerozerotype = this->get_type(zero__);
    //Value::Object dict = trigram.GetObj();
    int zerozerocount = get_count(this->trigram[zerozerotype], zero__, 3);

    wstring zeroonetype = this->get_type(one);
    int zeroonecount = get_count(this->trigram[zeroonetype], one, 3);
    
    r0 = zerozerocount;
    r1 = zeroonecount;
    //timer(L"tri make count", start);
    //wcout << r0 << " " << r1 << endl;
    //wcout << "1" << r0 << r1 << endl;
}

float AutoModule::calc_prob(int count, int totalcount) {
    if (totalcount > 0)
        return (float)count / (float)totalcount;
    return 0.0;
}

float AutoModule::calc_bigram(const wstring& text, int i) {
    if (text.size() < 3)
        return -1;

    wstring right= L"   ";
    wstring center=L"   ";
    wstring left=L"   ";
    wstring text_ = text;
    vector<wchar_t> text_arr(text_.begin(), text_.end());

    //chrono::steady_clock::time_point start = get_startt();
    
    if (i - 1 > 0 && i < text_arr.size()) {
        vector<wchar_t> right_;
        //cout << text_arr.size() <<endl;
        //cout << text.size() << endl;
        right_.push_back(text_arr[i - 1]);
        right_.push_back(text_arr[i]);
        right_.push_back(L' ');
        //right_.push_back('\0');
        right = wstring(right_.begin(), right_.end());
    }
    //timer(L"right", start);
    /*else
        right = L"   ";*/

    //start = get_startt();
    if (0 <= i && i + 1 < text_arr.size()) {
        vector<wchar_t> center_;
        center_.push_back(text_arr[i]);
        center_.push_back(L' ');
        center_.push_back(text_arr[i + 1]);
        //center_.push_back('\0');
        center = wstring(center_.begin(), center_.end());
    }
    //timer(L"center", start);
    /*else
        center = L"   ";*/

    //start = get_startt();
    if (0 <= i + 1 && i + 2 < text_arr.size()) {
        vector<wchar_t> left_;
        left_.push_back(L' ');
        left_.push_back(text_arr[i + 1]);
        left_.push_back(text_arr[i + 2]);
        //left_.push_back('\0');
        left = wstring(left_.begin(), left_.end());
    }
    //timer(L"left", start);
    /*else
        left = L"   ";*/
    //cout << right << center << left << endl;
    //wstring right__ = right;
    //wcout << right << endl;
    int right0count = -1, right1count = -1;
    //wcout << right0count << L"afdadfa" << right1count << endl;
    //start = get_startt();
    this->bi_make_count(2, right,right0count,right1count);
    //wcout << right0count << L"afdadfa" << right1count << endl;
    //timer(L"bicount right", start);
    //wstring center__ = center;
    int center0count = -1, center1count = -1;
    //start = get_startt();
    this->bi_make_count(1, center,center0count,center1count);
    //timer(L"bicount center", start);
    //wstring left__ = left;
    int left0count = -1, left1count = -1;
    //start = get_startt();
    this->bi_make_count(0, left,left0count,left1count);
    //timer(L"bicount left", start);
    //wcout << L"----------------" << endl;
    //wcout << s2ws(right__) << " " << right1count << endl;
    float rightprob = this->calc_prob(right1count, right0count + right1count);
    float centerprob = this->calc_prob(center1count, center0count + center1count);
    float leftprob = this->calc_prob(left1count, left0count + left1count);
    //wcout << rightprob
    float spprob = 0.3 * rightprob + 0.375 * centerprob + 0.325 * leftprob;

    return spprob;
}

float AutoModule::calc_trigram(const wstring& text, int i) {

    wstring text_ = text;
    vector<wchar_t> text_arr(text_.begin(), text_.end());
    wstring tri01 = L"    ";
    auto start = get_startt();
    if (i - 2 >= 0 && i < text_arr.size())
        tri01 = tri_to_string(text_arr, i - 2, i - 1, i, -1);
    //timer(L"tri01", start);
    wstring tri11 = L"    ";
    start = get_startt();
    if (i - 1 >= 0 && i + 1 < text_arr.size())
        tri11 = tri_to_string(text_arr, i - 1, i, -1, i + 1);
    //timer(L"tri11", start);

    wstring tri21 = L"    ";
    start = get_startt();
    if (i >= 0 && i + 2 < text_arr.size())
        tri21 = tri_to_string(text_arr, i, -1, i + 1, i + 2);
    //timer(L"tri21", start);

    wstring tri31 = L"    ";
    start = get_startt();
    if (i + 1 >= 0 && i + 3 < text_arr.size())
        tri31 = tri_to_string(text_arr, -1, i + 1, i + 2, i + 3);
    //timer(L"tri31", start);
    
    int tri00count = -1,tri01count = -1, tri10count = -1, tri11count = -1, tri20count = -1, tri21count = -1, tri30count = -1, tri31count = -1;
    start = get_startt();
    this->tri_make_count(3, tri01, tri00count, tri01count);
    //timer(L"0tri count", start);
    start = get_startt();
    this->tri_make_count(2, tri11, tri10count, tri11count);
    //timer(L"1tri count", start);
    start = get_startt();
    this->tri_make_count(1, tri21, tri20count, tri21count);
    //timer(L"2tri count", start);
    start = get_startt();
    this->tri_make_count(0, tri31, tri30count, tri31count);
    //timer(L"3tri count", start);

    //wcout << s2ws(tri01) << tri00count << " " << tri01count << endl;
    //wcout << s2ws(tri11) << tri10count << " " << tri11count << endl;
    //wcout << s2ws(tri21) << tri20count << " " << tri21count << endl;
    //wcout << s2ws(tri31) << tri30count << " " << tri31count << endl;
    float tri0prob = this->calc_prob(tri01count, tri01count + tri00count);
    float tri1prob = this->calc_prob(tri11count, tri11count + tri10count);
    float tri2prob = this->calc_prob(tri21count, tri21count + tri20count);
    float tri3prob = this->calc_prob(tri31count, tri31count + tri30count);

    float spprob = 0.22 * tri0prob + 0.27 * tri1prob + 0.27 * tri2prob + 0.24 * tri3prob;

    return spprob;
}

//int main() {
//    //SetConsoleOutputCP(65001);
//    setlocale(LC_ALL, "");
//    //wcout << "하이루 반가워요" << endl;
//    AutoModule autos;
//    float biprob = autos.calc_bigram(" 나는밥을먹고학교에 갔다. ", 2);
//    float triprob = autos.calc_trigram(" 나는밥을먹고학교에갔다. ", 2);
//    wcout << biprob << endl;
//    wcout << triprob << endl;
//    return 0;
//}
