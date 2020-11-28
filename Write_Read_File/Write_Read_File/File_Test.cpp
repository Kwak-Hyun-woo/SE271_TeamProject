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
    // userlist �ȿ� �ش� �й��� �ִ��� ������ ����
    bool in_list(int id_num) {
        std::string s_num = std::to_string(id_num);

        for (int i = 0; i < userlist.size(); ++i ) {
            if (userlist[i][0] == s_num) {                                 // vector�� ù���� ����(�̸�), �Ű������� ���� �̸� �� ������ ��
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
    //��������
    int id_num;
    std::string name;
    int pw;
    UserList userlist;
    bool in_list;


    //User ������ �о�� user_list ���·� �����
    std::ifstream users_r("Users.txt");

    std::string student_info;
    std::string buf;

    if (!users_r.is_open()) {
        std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
        return 0;
    }
    while (getline(users_r, student_info)) {            // ȸ�� ��� ���Ͽ� ���ڿ����� �� ���徿 �о student_info �� ����
        std::istringstream ss(student_info);
        std::vector<std::string> st_info;

        while (getline(ss, buf, '/')) {                 // student_info�� stringstream���� ������ �� '/'�� �������� �й�, �̸�, pw�� ���������� vector�� pushback
            st_info.push_back(buf);                     // vector[0] = �й�,  vector[1] = �̸�, vector[2] = pw
        }

        User temp_one(st_info[1], to_number(st_info[0]), to_number(st_info[2]));    // �̸�, �й�, pw ������ ����       
        userlist.add_user(temp_one);
    }
    users_r.close();

    // ���� ���� �غ�
    std::ofstream users_f("Users.txt", std::ios::app);

    // �α��� â 
    while (true) {
    std::cout << "--------------�α��� â--------------" << std::endl;
    std::cout << "\n�й� : ";
    std::cin >> id_num;
    std::cout << "\n��й�ȣ(�ݵ�� ���� 4���� �����ּ���!) : ";
    std::cin >> pw;
        if (pw > 9999 || pw < 1000 || std::cin.fail()) {
            std::cout << "�߸��� ��й�ȣ�Դϴ�." << std::endl;
            Sleep(500);
        }
        else {
            break;
        }
    }

    // �Է¹��� id�� user_list�� �ִ��� �� ������

    in_list = userlist.in_list(id_num);

    if (in_list) {
        std::cout << "�������� ����â���� �Ѿ��" << std::endl;
    }
    else {
        // �Է¹��� id�� ���� �� ȸ������
        while (true) {
            std::cout << "--------------ȸ�� ����--------------" << std::endl;
            std::cout << "\n�̸� : ";
            std::cin >> name;
            std::cout << "\n�й� : ";
            std::cin >> id_num;
            std::cout << "\n��й�ȣ(�ݵ�� ���� 4���� �����ּ���!) : ";
            std::cin >> pw;
            if (pw > 9999 || pw < 1000 || std::cin.fail()) {
                std::cout << "�߸��� ��й�ȣ�Դϴ�." << std::endl;
                Sleep(500);
                continue;
            }
            else {
                break;
            }
        }
        //�ű�ȸ�� ��ü ���� �� ȸ�� ��� ���Ͽ� ����
        User newbie(name, id_num, pw);
        users_f << newbie << std::endl;
    }
    return 0;
}