#pragma once

#include <set>
#include <string>

#include "control.h"

class Student;
class Admin;
class Seat;
class StudyRoom;

class LessCoordinate {					// Seat instance를 담는 set을 위한 functor << 좌표 작은 순으로 정렬
public:
	bool operator() (const Seat& s1, const Seat& s2) {
		if (s1.coordinate[1] == s2.coordinate[1]) {
			return s1.coordinate[0] < s2.coordinate[0];
		}
		else {
			return s1.coordinate[1] < s2.coordinate[1];
		}
	}
};

class Student {
private:
	int student_num;					// student number
	std::string password;				// password for login / reservation
	bool is_using;						// 현재 좌석을 예약하고 이용중인가?
	StudyRoom* studyroom_using;			// 현재 이용중인 독서실
	Seat* seat_using;					// 현재 이용중인 좌석
	
public:
	Student() {}
	Student(int num, std::string pwd) : student_num{ num }, password{ pwd }, is_using{ false } {}

	virtual ~Student() {}
	
	// get data
	int get_student_num();
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
	
public:
	Admin() {}
};

class Seat {
private:
	std::string belong_to;				// 어떤 독서실에 있는 좌석인가?
	int seat_num;						// 좌석의 고유 번호
	bool reservation;					// 현재 예약되어 있는지
	Student* res_student;				// 예약한 학생
	bool away_from;						// 자리 비움 상태인가?

public:
	Seat() {}
	Seat(std::string study_room, int num, int pos[2]) : belong_to{ study_room }, seat_num{ num }, reservation{ false }, away_from{ false } {
		coordinate[0] = pos[0];
		coordinate[1] = pos[1];
	}

	virtual ~Seat() {}

	int coordinate[2];					// 좌석의 위치

	// get data
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
	int max_seat_num;					// 전체 좌석 수
	int cur_using_num;					// 이용중인 좌석 수
	std::set<Seat> seats;				// StudyRoom에 포함된 Seat instance set -> 항상 좌표 순서로 정렬된 상태를 유지하도록 set container 사용
public:
	StudyRoom() {}
	StudyRoom(int max) : max_seat_num{ max }, cur_using_num{ 0 } {}

	// get data
	int get_cur_using_num();
	std::set<Seat, LessCoordinate>* get_seat(int idx);

	// set data
	void set_cur_using_num(int i);
};