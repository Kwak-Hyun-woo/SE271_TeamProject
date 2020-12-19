#include "model.h"

// class Studnet - get data
int Student::get_student_num() { return student_num; }
bool Student::get_is_using() { return is_using; }
StudyRoom* Student::get_studyroom_using() { return studyroom_using; }
Seat* Student::get_seat_using() { return seat_using; }

// class Studnet - set data
void Student::set_student_num(int num) { student_num = num; }
void Student::set_password(std::string pwd) { password = pwd; }
void Student::set_is_using_reverse() { is_using = !is_using; }
void Student::set_studyroom_using(StudyRoom* room) { studyroom_using = room; }
void Student::set_seat_using(Seat* seat) { seat_using = seat; }



// class Seat - get data
StudyRoom* Seat::get_belong_to() { return belong_to; }
int Seat::get_seat_num() { return seat_num; }
bool Seat::is_reserved() { return reservation; }
Student* Seat::get_res_student() { return res_student; }
bool Seat::is_away_from() { return away_from; }

// class Seat - set data
void Seat::set_reservation_reverse() { reservation = !reservation; }
void Seat::set_res_student(Student* student) { res_student = student; }
void Seat::set_away_from_reverse() { away_from = !away_from; }



// class StudyRoom - get data
int StudyRoom::get_cur_using_num() { return cur_using_num; }
Seat* StudyRoom::get_seat(int idx) { return &(seats[idx]); }

// class StudyRoom - set data
void StudyRoom::set_cur_using_num(int i) { cur_using_num = i; }

// class StudentDB
void StudentDB::add_student(Student* student) {
	student_database.push_back(student);
}
void StudentDB::add_admin(Admin* admin) {
	admin_database.push_back(admin);
}

void StudentDB::get_student(int student_num) {

}
void get_admin(std::string admin_id) {

}