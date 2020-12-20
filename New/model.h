#pragma once

#include <vector>
#include <string>

class Student;
class Admin;
class Seat;
class StudyRoom;
class StudentDB;

class Student {
private:
	int student_num = NULL;						// student number
	std::string password = NULL;				// password for login / reservation
	bool is_using = false;						// ���� �¼��� �����ϰ� �̿����ΰ�?
	StudyRoom* studyroom_using = nullptr;		// ���� �̿����� ������
	Seat* seat_using = nullptr;					// ���� �̿����� �¼�
		
public:
	Student() {}
	Student(int num) : student_num{ num }, is_using{ false } {}
	Student(int num, std::string pw) : student_num{ num }, password{ pw }, is_using{ false } {}

	virtual ~Student() {}
	
	// get data
	int get_student_num();
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
	std::string admin_id;			// ������ ���� ���� ID
public:
	Admin() {}
	Admin(std::string ad_id) : admin_id{ ad_id } {}
	std::string get_admin_id();
};

class Seat {
private:
	StudyRoom* belong_to = nullptr;				// � �����ǿ� �ִ� �¼��ΰ�?
	int seat_num = NULL;						// �¼��� ���� ��ȣ
	bool reservation = false;					// ���� ����Ǿ� �ִ���
	Student* res_student = nullptr;				// ������ �л�
	bool away_from = false;						// �ڸ� ��� �����ΰ�?

public:
	Seat() {}
	Seat(StudyRoom* study_room, int num, int pos[2]) : belong_to{ study_room }, seat_num{ num }, reservation{ false }, away_from{ false } {
		coordinate[0] = pos[0];
		coordinate[1] = pos[1];
	}

	virtual ~Seat() {}

	int coordinate[2];					// �¼��� ��ġ

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
	int max_seat_num = NULL;					// ��ü �¼� ��
	int cur_using_num = NULL;					// �̿����� �¼� ��
	std::vector<Seat> seats;					// StudyRoom�� ���Ե� Seat instance vector
public:
	StudyRoom() {}
	StudyRoom(int max) : max_seat_num{ max }, cur_using_num{ 0 } {}

	// get data
	int get_cur_using_num();
	Seat* get_seat(int idx);

	// set data
	void set_cur_using_num(int i);
};

// ���α׷��� ��ϵ� Student/Admin�� �����ϴ� StudentDB Ŭ����
class StudentDB {
private:
	std::vector<Student*> student_database;				// ID, PW
	std::vector<Admin*> admin_database;					// ID, PW, ADMIN_ID
public:
	int load_student_database();
	int load_student_admin_database();

	int save_student_database();
	int save_student_admin_database();

	void add_student(Student* student);
	void add_admin(Admin* admin);

	Student* get_student(int student_num);
	Admin* get_admin(std::string admin_id);
};