#include "AutoSpace.h"
//#include "AutoModule.h"
#include <string>
#include <iostream>
#include <vector>
#include <clocale>
#include <chrono>
#include <regex>
#include <codecvt>
#include <fstream>
#include "utils.h"

using namespace std;


void symbol(wstring& txt, wstring& res, vector<wstring>& txt_sym) {
    //txt = txt.replace("”", "").replace("“", "").replace("’", "").replace("‘", "")
    setlocale(LC_ALL, "");
    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
    wregex pattern(L"\\s+[^가-힣]+\\s+|[^가-힣]+\\s+|\\s+[^가-힣]+|[^가-힣\\s]+");
    wsregex_iterator it(txt.begin(), txt.end(), pattern);
    std::wsregex_iterator end;
    while (it != end) {
        std::wsmatch match = *it; // 반복자에서 wsmatch 객체 가져오기
        txt_sym.push_back(match.str());

        ++it; // 다음 일치 항목으로 이동
    }
    wstring res_tmp = regex_replace(txt, pattern, L" * ");
    wregex space_(L" +");
    res_tmp = regex_replace(res_tmp, space_, L" ");
    res = strip(res_tmp);
}

wstring symto_str(const wstring& res, const vector<wstring>& sf) {
    wstring str_;
    int idx = 0;

    vector<wstring> tmplist = split(res, L'*');
    for (wstring s : tmplist) {
        if (idx < sf.size()) {
            str_ += strip(s) + sf[idx];
            idx += 1;
        }
        else {
            str_ += strip(s);
        }
    }
    return str_;
}


//void timer(wstring type, chrono::steady_clock::time_point start) {
//    chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
//    std::chrono::milliseconds duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::wcout << type << L" 실행 시간: " << duration_ms.count() / 1000.0 << L" ms" << std::endl;
//}

//def autospacefn2(autospace, l) :
//
//    if True :
//        l_ = l
//        l_, sym, sf = symbol(l_.strip())
//        # print(l_)
//        res = toautospace2(autospace, l_)#autospace.autospace(l_)
//        # print(l_)
//        # print(l)
//        if len(sym) > 0 or len(sf) > 0:
//res = symto_str(res, sym, sf)
//res = res.strip()
//# print(res)
//# result.append(res)
//# else:
//# result.append(l_)
//return res
AutoSpace::AutoSpace() {
    this-> automodel.load_dict();
}
string AutoSpace::autospace(const string& text) {
    wstring text__ = s2ws(text);
    wstring l_ = wstring(text__);
    wstring res;
    vector<wstring> sf;
    symbol(l_, res, sf);
    //chrono::steady_clock::time_point start_ = std::chrono::high_resolution_clock::now();
    wstring text_ = L" " + res + L" ";
    wstring sentence = text_;//s2ws(text);
    int index = 0;

    sentence = strip(sentence);
    wstring tmpsentence = sentence;
    vector<wstring> sentence_ = ws2wsvec(sentence);
    float thres = 0.45;
    int spacecount = 0;

    for (wstring eoj : split(strip(sentence),L' ')) {
        if (eoj.size() >= 5)
            thres = 0.4;
        else
            thres = 0.45;

        if (eoj.size() >= 3) {
            for (int i = index; i < index + eoj.size(); i++) {
                tmpsentence = strip(tmpsentence);
                //string tmpsentence_ = ws2s(tmpsentence);
                // chrono::steady_clock::time_point start = get_startt();
                float tris = this->automodel.calc_trigram(L" " + tmpsentence + L" ", spacecount + i + 1);
                //timer(L"Calc Trigram", start);
                // start = std::chrono::high_resolution_clock::now();
                float bis = this->automodel.calc_bigram(L" " + tmpsentence + L" ", spacecount + i + 1);
                //timer(L"Calc Bigram", start);
                float per = 0.55 * tris + 0.45 * bis;

                if (per > thres) {
                    sentence_[i] = sentence_[i] + L" ";
                    
                    tmpsentence = join(sentence_);
                    
                    spacecount += 1;
                }
                
            }
        }
        index = index + eoj.size() + 1;
    }
    res = join(sentence_);
    // wcout << res << endl;
    res = symto_str(res, sf);
    string res_ = ws2s(res);
    //timer(L"자동띄어쓰기 전체", start_);
    return res_;
}

// int main(){
//     string line="어떻게 애니메이션을 이렇게 역동적으로 만들 수 있지정말감탄밖에안나오는영화";
//     AutoSpace autos;   
//     string res = autos.autospace(line);
//     setlocale(LC_ALL,"");
//     // wcout << s2ws(res) << endl;
    
//     while(true){
//         wstring line;
//         wcout << L"하이" << endl;
//         wcin >> line;
//         wcout << L"input: " << line << endl;
//         string res = autos.autospace(ws2s(line));
//         wcout << s2ws(res) << endl;
//     }
//     return 0;
// }
//void fileread(string path) {
//    setlocale(LC_ALL, "");
//    std::wifstream file(path);
//    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
//    file.imbue(utf8_locale);
//
//    wstring fileline;
//    while (getline(file, fileline)) {
//        //wcout << fileline << endl;
//
//    }
//    //file >> fileline;
//    // 
//    //while (fileline.size()!=0) {
//    //wcout << fileline << endl;
//    //file >> fileline;
//    //wcout << fileline << endl;
//    //file.getline()
//    //}
// //}

// int main(int argc, char* argv[]) {
//     wcout << L"Loaded" << endl;
//     if (argc > 1) {
//         cout << argv[1] << endl;
//         fileread(argv[1]);
//     }
    
//     /*AutoSpace autom;

//     wstring res = autom.toautospace2(L"나는밥을,먹고학교에,갔다.");
//     wcout << res << endl;*/
//     return 0;
// }
