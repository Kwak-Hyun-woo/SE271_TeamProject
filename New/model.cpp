#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <math.h>

#include "model.h"

// class Student - get data
int Student::get_student_num()				{ return student_num; }
std::string Student::get_password()			{ return password; }
bool Student::get_is_using()				{ return is_using; }
StudyRoom* Student::get_studyroom_using()	{ return studyroom_using; }
Seat* Student::get_seat_using()				{ return seat_using; }

// class Student - set data
void Student::set_student_num(int num)				{ student_num = num; }
void Student::set_password(std::string pwd)			{ password = pwd; }
void Student::set_is_using_reverse()				{ is_using = !is_using; }
void Student::set_studyroom_using(StudyRoom* room)	{ studyroom_using = room; }
void Student::set_seat_using(Seat* seat)			{ seat_using = seat; }

// class Admin - get data
std::string Admin::get_admin_id()			{ return admin_id; }

// class Admin - set data
void Admin::set_admin_id(std::string ad_id) { admin_id = ad_id; }

// class Seat - get data
StudyRoom* Seat::get_belong_to()			{ return belong_to; }
int Seat::get_seat_num()					{ return seat_num; }
bool Seat::is_reserved()					{ return reservation; }
Student* Seat::get_res_student()			{ return res_student; }
bool Seat::is_away_from()					{ return away_from; }

// class Seat - set data
void Seat::set_reservation_reverse()		{ reservation = !reservation; }
void Seat::set_res_student(Student* student){ res_student = student; }
void Seat::set_away_from_reverse()			{ away_from = !away_from; }

// class StudyRoom - get data
std::string StudyRoom::get_name()			{ return name; }
int StudyRoom::get_max_seat_num()			{ return max_seat_num; }
int StudyRoom::get_cur_using_num()			{ return cur_using_num; }
Seat* StudyRoom::get_seat(int idx)			{ return &(seats[idx]); }
std::vector<Seat> StudyRoom::get_seats()	{ return seats; }

// class StudyRoom - set data
void StudyRoom::set_name(std::string studyroom_name)	{ name = studyroom_name; }
void StudyRoom::set_cur_using_num(int i)				{ cur_using_num = i; }
void StudyRoom::add_seat(Seat seat) {
	if (cur_using_num == max_seat_num) {
		std::cout << "더 이상 좌석을 추가할 수 없습니다." << std::endl;
		return;
	}
	seats.push_back(seat);
	cur_using_num++;
}

// class StudentDB
int StudentDB::load_student_database() {
	std::fstream fs;
	std::stringstream ss;
	std::vector<std::string> row;
	
	fs.open("student.csv", std::ios::in);

	if (fs.fail()) {
		return 1;
	}

	while (fs.good()) {
		char c = fs.get();
		if (c != '\n' && c != ',') {
			ss << (char)fs.get();
		}
		else {
			row.push_back(ss.str());
		}
	}

	fs.close();

	for (unsigned int i = 0; i < row.size(); i += 2) {
		Student st(stoi(row[i]), row[i + 1]);
		student_database.push_back(&st);
	}

	return 0;
}

int StudentDB::load_student_admin_database() {
	std::fstream fs;
	std::stringstream ss;
	std::vector<std::string> row;

	fs.open("admin.csv", std::ios::in);

	if (fs.fail()) {
		return 1;
	}

	while (fs.good()) {
		char c = fs.get();
		if (c != '\n' && c != ',') {
			ss << (char)fs.get();
		}
		else {
			row.push_back(ss.str());
		}
	}

	fs.close();

	for (unsigned int i = 0; i < row.size(); i += 2) {
		Admin st(row[i]);
		st.set_password(row[i + 1]);
		admin_database.push_back(&st);
	}

	return 0;
}

void StudentDB::save_student_database() {
	std::string student_db;
	std::string row;

	for (auto student : student_database) {
		if (student_db.size()) student_db += '\n';
		row = std::to_string(student->get_student_num()) + ',' + student->get_password();
		student_db += row;
	}

	std::fstream fs;
	fs.open("student.csv");
	fs.write(student_db.c_str(), student_db.size());
	fs.close();
}

void StudentDB::save_student_admin_database() {
	std::string admin_db;
	std::string row;

	for (auto admin : student_database) {
		if (admin_db.size()) admin_db += '\n';
		row = std::to_string(admin->get_student_num()) + ',' + admin->get_password();
		admin_db += row;
	}

	std::fstream fs;
	fs.open("admin.csv");
	fs.write(admin_db.c_str(), admin_db.size());
	fs.close();
}

void StudentDB::add_student(Student* student) {
	student_database.push_back(student);
}
void StudentDB::add_admin(Admin* admin) {
	admin_database.push_back(admin);
}

Student* StudentDB::get_student(int student_num) {
	for (auto student : student_database) {
		if (student_num == student->get_student_num()) return student;
	}
	return nullptr;
}

Admin* StudentDB::get_admin(std::string admin_id) {
	for (auto admin : admin_database) {
		if (admin_id == admin->get_admin_id()) return admin;
	}
	return nullptr;
}

int StudyRoomDB::load_studyroom_database() {
	std::fstream fs;
	std::stringstream ss;
	std::vector<std::string> row;
	std::vector<std::vector<std::string>> rows;

	fs.open("studyroom.csv", std::ios::in);

	if (fs.fail()) {
		return 1;
	}

	while (fs.good()) {
		char c = fs.get();
		if (c != '\n' && c != ',') {
			ss << (char)fs.get();
		}
		else if (c == ',') {
			row.push_back(ss.str());
		}
		else {
			rows.push_back(row);
		}
	}

	fs.close();

	for (unsigned int i = 0; i < rows.size(); ++i) {
		StudyRoom room(rows[i][0], stoi(rows[i][1]));
		for (unsigned int j = 2; j < room.get_max_seat_num() * 2 + 2; j += 2) {
			Pos pos(stoi(row[j]), stoi(row[j + 1]));
			Seat seat(&room, (j - 2) / 2, pos);
			room.add_seat(seat);
		}
		studyroom_database.push_back(&room);
	}

	return 0;
}

void StudyRoomDB::save_studyroom_database() {
	std::string studyroom_db;
	std::string row;

	for (auto studyroom : studyroom_database) {
		if (studyroom_db.size()) studyroom_db += '\n';
		row = studyroom->get_name() + ',' + std::to_string(studyroom->get_max_seat_num());

		for (auto seat : studyroom->get_seats()) {
			row += ',' + std::to_string(seat.pos.x) + ',' + std::to_string(seat.pos.y);
		}
		
		studyroom_db += row;
	}

	std::fstream fs;
	fs.open("studyroom.csv");
	fs.write(studyroom_db.c_str(), studyroom_db.size());
	fs.close();
}

void StudyRoomDB::add_studyroom(StudyRoom* studyroom) {

}