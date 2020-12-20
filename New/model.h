#pragma once

#include <vector>
#include <string>

class Pos;
class Student;
class Admin;
class Seat;
class StudyRoom;
class StudentDB;

class Pos {
public:
	Pos() : x{ 0 }, y{ 0 } {}
	Pos(int x, int y) : x{ x }, y{ y } {}
	int x;
	int y;

	void operator()(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}
};

class Student {
private:
	int student_num = NULL;						// student number
	std::string password = NULL;				// password for login / reservation
	bool is_using = false;						// 현재 좌석을 예약하고 이용중인가?
	StudyRoom* studyroom_using = nullptr;		// 현재 이용중인 독서실
	Seat* seat_using = nullptr;					// 현재 이용중인 좌석
		
public:
	Student() {}
	Student(int num) : student_num{ num } {}
	Student(int num, std::string pw) : student_num{ num }, password{ pw } {}

	virtual ~Student() {}
	
	// get data
	int get_student_num();
	std::string get_password();
	bool get_is_using();
	StudyRoom* get_studyroom_using();
	Seat* get_seat_using();

	// set data
	void set_student_num(int num);
	void set_password(std::string pwd);
	void set_is_using_reverse();
	void set_studyroom_using(StudyRoom* room);
	void set_seat_using(Seat* seat);
};

class Admin : public Student {
private:
	std::string admin_id;			// 관리자 계정 전용 ID
public:
	Admin() {}
	Admin(std::string ad_id) : admin_id{ ad_id } {}
	std::string get_admin_id();

	void set_admin_id(std::string ad_id);
};

class Seat {
private:
	StudyRoom* belong_to = nullptr;				// 어떤 독서실에 있는 좌석인가?
	int seat_num = NULL;						// 좌석의 고유 번호
	bool reservation = false;					// 현재 예약되어 있는지
	Student* res_student = nullptr;				// 예약한 학생
	bool away_from = false;						// 자리 비움 상태인가?

public:
	Seat() {}
	Seat(StudyRoom* study_room, int num, Pos input_pos) : belong_to{ study_room }, seat_num{ num } {
		pos.x = input_pos.x;
		pos.y = input_pos.y;
	}

	virtual ~Seat() {}

	Pos pos;									// 좌석의 위치

	// get data
	StudyRoom* get_belong_to();
	int get_seat_num();
	bool is_reserved();
	Student* get_res_student();
	bool is_away_from();

	// set data
	void set_reservation_reverse();
	void set_res_student(Student* student);
	void set_away_from_reverse();
};

class StudyRoom {
private:
	std::string name = NULL;
	int max_seat_num = NULL;					// 전체 좌석 수
	int cur_using_num = NULL;					// 이용중인 좌석 수
	std::vector<Seat> seats;					// StudyRoom에 포함된 Seat instance vector

public:
	StudyRoom() {}
	StudyRoom(int max) : max_seat_num{ max }, cur_using_num{ 0 } {}
	StudyRoom(std::string room_name, int max) : name{ room_name }, max_seat_num { max }, cur_using_num{ 0 } {}

	// get data
	std::string get_name();
	int get_max_seat_num();
	int get_cur_using_num();
	Seat* get_seat(int idx);

	// set data
	void set_name(std::string studyroom_name);
	void set_cur_using_num(int i);
	void add_seat(Seat seat);
};

// 프로그램에 등록된 Student/Admin을 관리하는 StudentDB 클래스
class StudentDB {
private:
	std::vector<Student*> student_database;				// ID, PW
	std::vector<Admin*> admin_database;					// admin_ID, PW
public:
	int load_student_database();
	int load_student_admin_database();

	void save_student_database();
	void save_student_admin_database();

	void add_student(Student* student);
	void add_admin(Admin* admin);

	Student* get_student(int student_num);
	Admin* get_admin(std::string admin_id);
};

class StudyRoomDB {
private:
	std::vector<StudyRoom*> studyroom_database;			// name, size /n x1, y1, x2, y2 ...
public:
	int load_studyroom_database();
	void save_studyroom_database();
	void add_studyroom(StudyRoom* studyroom);
};