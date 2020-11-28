#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>

class User {
public:
    std::string name;
    int id_num;
    int pw;

    User(const std::string& name, int num, int pw) : name(name), id_num(num), pw(pw) {}
    std::string get_info() {
        return std::to_string(id_num) + "/" + name + "/" + std::to_string(pw);
    }

    friend std::ofstream& operator<<(std::ofstream& o, User& h);
};

class UserList {
    std::vector<std::vector<std::string>> userlist;
    
    std::vector<std::string>  user_infos;

    int size;

public:
    void add_user( User newbie) {
        user_infos.push_back(std::to_string(newbie.id_num));
        user_infos.push_back(newbie.name);
        user_infos.push_back(std::to_string(newbie.pw));

        userlist.push_back(user_infos);
        size += 1;
        std::cout << "Working\n";
    }
    // userlist 안에 해당 학번이 있는지 없는지 조사
    bool in_list(int id_num) {
        std::string s_num = std::to_string(id_num);

        for (int i = 0; i < userlist.size(); ++i ) {
            if (userlist[i][0] == s_num) {                                 // vector의 첫번쨰 원소(이름), 매개변수로 받은 이름 이 같은지 비교
                return true;
            }
        }
        return false;
    }
};

std::ofstream& operator<<(std::ofstream& o, User& h) {
    o << h.get_info();
    return o;
}

int to_number(std::string s) {
    std::istringstream ss(s);
    int x;

    ss >> x;
    return x;
}

int main() {
    //변수선언
    int id_num;
    std::string name;
    int pw;
    UserList userlist;
    bool in_list;


    //User 파일을 읽어와 user_list 형태로 만들기
    std::ifstream users_r("Users.txt");

    std::string student_info;
    std::string buf;

    if (!users_r.is_open()) {
        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
        return 0;
    }
    while (getline(users_r, student_info)) {            // 회원 목록 파일에 문자열들을 한 문장씩 읽어서 student_info 에 저장
        std::istringstream ss(student_info);
        std::vector<std::string> st_info;

        while (getline(ss, buf, '/')) {                 // student_info를 stringstream으로 저장한 후 '/'를 기준으로 학번, 이름, pw를 순차적으로 vector에 pushback
            st_info.push_back(buf);                     // vector[0] = 학번,  vector[1] = 이름, vector[2] = pw
        }

        User temp_one(st_info[1], to_number(st_info[0]), to_number(st_info[2]));    // 이름, 학번, pw 순으로 생성       
        userlist.add_user(temp_one);
    }
    users_r.close();

    // 파일 쓰기 준비
    std::ofstream users_f("Users.txt", std::ios::app);

    // 로그인 창 
    while (true) {
    std::cout << "--------------로그인 창--------------" << std::endl;
    std::cout << "\n학번 : ";
    std::cin >> id_num;
    std::cout << "\n비밀번호(반드시 숫자 4개로 적어주세요!) : ";
    std::cin >> pw;
        if (pw > 9999 || pw < 1000 || std::cin.fail()) {
            std::cout << "잘못된 비밀번호입니다." << std::endl;
            Sleep(500);
        }
        else {
            break;
        }
    }

    // 입력받은 id가 user_list에 있는지 비교 있으면

    in_list = userlist.in_list(id_num);

    if (in_list) {
        std::cout << "본격적인 예약창으로 넘어가기" << std::endl;
    }
    else {
        // 입력받은 id가 없을 때 회원가입
        while (true) {
            std::cout << "--------------회원 가입--------------" << std::endl;
            std::cout << "\n이름 : ";
            std::cin >> name;
            std::cout << "\n학번 : ";
            std::cin >> id_num;
            std::cout << "\n비밀번호(반드시 숫자 4개로 적어주세요!) : ";
            std::cin >> pw;
            if (pw > 9999 || pw < 1000 || std::cin.fail()) {
                std::cout << "잘못된 비밀번호입니다." << std::endl;
                Sleep(500);
                continue;
            }
            else {
                break;
            }
        }
        //신규회원 객체 생성 및 회원 목록 파일에 저장
        User newbie(name, id_num, pw);
        users_f << newbie << std::endl;
    }
    return 0;
}