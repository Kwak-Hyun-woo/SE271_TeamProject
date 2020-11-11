#include <iostream>
#include <windows.h>

// �������� �����ϴ� ����Ʈ. ���� �迭�� ���� �ϳ��� �߰��ϴ� ���� �����ϰ� �ϱ� ���� ����
class IntList {
private:
	int* list;
	int size;
public:
	IntList() {
		list = nullptr;
		size = 0;
	}

	void append(int n) {
		if (size == 0) {
			list = new int[1]{ n };
			size++;
			return;
		}
		int* temp_list = new int[size];
		for (int i = 0; i < size; i++) {
			temp_list[i] = list[i];
		}
		delete[] list;
		size++;
		list = new int[size];
		for (int i = 0; i < size - 1; i++) {
			list[i] = temp_list[i];
		}
		list[size - 1] = n;
		delete[] temp_list;
	}

	void insert(int index, int n) {
		if (size == 0) {
			list = new int[1]{ n };
			size++;
			return;
		}
		int* temp_list = new int[size];
		for (int i = 0; i < size; i++) {
			temp_list[i] = list[i];
		}
		delete[] list;
		size++;
		list = new int[size];
		for (int i = 0; i < index; i++) {
			list[i] = temp_list[i];
		}
		list[index] = n;
		for (int i = index + 1; i < size; i++) {
			list[i] = temp_list[i];
		}
		delete[] temp_list;
	}

	void print() {
		if (size == 0) {
			std::cout << "[]" << std::endl;
			return;
		}
		std::cout << "[";
		for (int i = 0; i < size - 1; i++) {
			std::cout << list[i] << ", ";
		}
		std::cout << list[size - 1] << "]" << std::endl;
	}

	int operator[](int index) {
		return list[index];
	}

	void set_value(int index, int n) {
		list[index] = n;
	}

	int get_size() {
		return size;
	}
};
// ------------------------------------------------------------------------------------------------------------

// Seat : �¼� Ŭ����
class Seat {

private:
	int seat_num;								// �¼��� ��ȣ
	bool reserved;								// ���� ����
	int reserved_student_num;					// ������ �й�
	std::string reserved_student_name;			// ������ �̸�
	int password;								// ���� ��й�ȣ

public:
	void init_set(int num) {					// �������� ��ȣ ����
		seat_num = num;
		reserved = false;
	}

	void print_status() {						// �¼� ���� ���
		std::cout << "�¼� ��ȣ : " << seat_num << std::endl;
		std::cout << "���� ���� : ";
		if (reserved) {
			std::cout << "�����" << std::endl;
			std::cout << "������ : " << reserved_student_name << "(" << reserved_student_num << ")" << std::endl;
			std::cout << "���� �ð� : �̱���" << std::endl;
		}
		else {
			std::cout << "����Ǿ� ���� ���� (���� ����)" << std::endl;
		}
	}

	bool is_reserved() {						// ���� ���� ����
		return reserved;
	}

	void reserve(int num, std::string& name, int pw) {		// ����
		reserved = true;
		reserved_student_name = name;
		reserved_student_num = num;
		password = pw;
	}

	bool cancelation() {									// ���� ���, ��� ���� ���θ� bool type���� ����
		int pw;
		std::cout << "��й�ȣ�� �Է��� �ֽʽÿ� : ";
		std::cin >> pw;
		std::cout << std::endl;
		if (pw == password) {
			reserved = false;
			reserved_student_name = "";
			reserved_student_num = NULL;
			return true;
		}
		else {
			return false;
		}
	}
};

// ------------------------------------------------------------------------------------------------------------

// StudyRoom : ������ Ŭ����
class StudyRoom {

private:
	int** seat_coordinate;							// ������ �� �¼��� ��ġ�� ��ǥ (2���� �迭)
	int max_size;									// ��ü �¼��� ��
	bool init_setting;								// �������� �ʱ� ������ �Ϸ�Ǿ������� ��Ÿ��
	int cur_using;									// ���� ������� �¼��� �� (�̱���)
	Seat* seat_instance_list;						// �¼��� �����Ǵ� Seat instance���� �迭

public:
	void print() {									// ���� ������ �¼� ��Ȳ�� ���
		// ��ü �¼��� �� ���� �ٸ� y coordinate Ž��
		int* distinct_y = new int[max_size];
		int y_count = 0;
		int seat_num = 0;
		for (int i = 0; i < max_size; i++) {
			if (i == 0) {
				distinct_y[y_count] = seat_coordinate[i][1];
				y_count++;
				continue;
			}
			bool existing = false;
			for (int j = 0; j < y_count; j++) {
				if (seat_coordinate[i][1] == distinct_y[j]) {
					existing = true;
					break;
				}
			}
			if (!existing) {
				distinct_y[y_count] = seat_coordinate[i][1];
				y_count++;
			}
		}
		// y coordinate ���� x coordinate �з��ؼ� ����, 0��° index�� �ش� y coordinate�� �����ϴ� x coordinate�� ����
		IntList* coordinates = new IntList[y_count];
		for (int i = 0; i < y_count; i++) {
			coordinates[i].append(0);
		}
		for (int i = 0; i < max_size; i++) {
			for (int y_index = 0; y_index < y_count; y_index++) {
				if (seat_coordinate[i][1] == distinct_y[y_index]) {
					coordinates[y_index].append(seat_coordinate[i][0]);
					coordinates[y_index].set_value(0, coordinates[y_index][0] + 1);
				}
			}
		}		
		// print
		for (int y_index = 0; y_index < y_count; y_index++) {
			// �¼��� ��ġ�Ǿ� ���� ���� ������ ���� print (y coordinate ����)
			if (y_index == 0) {
				for (int blank = 0; blank < distinct_y[0] * 6; blank++) {
					std::cout << std::endl;
				}
			}
			else {
				for (int blank = 0; blank < (distinct_y[y_index] - distinct_y[y_index - 1] - 1) * 6; blank++) {
					std::cout << std::endl;
				}
			}
			// ���� y coordinate ������ ���� �ٸ� �¼��� ������ ������ �����ϴ� gaps ����Ʈ
			IntList gaps;
			for (int i = 1; i <= coordinates[y_index][0]; i++) {
				if (i == 1) {
					gaps.append(coordinates[y_index][i] + 1);
					continue;
				}
				gaps.append(coordinates[y_index][i] - coordinates[y_index][i - 1]);
			}
			// �������� ���, �� �پ� ���, �� �¼��� 12x6 ũ�� ����
			for (int high = 0; high < 6; high++) {
				for (int bing = 0; bing < coordinates[y_index][0]; bing++) {
					// �¼� ��ȣ ���
					seat_num = 0;
					for (int yi = 0; yi < y_index; yi++) {
						seat_num += coordinates[yi][0];
					}
					seat_num += (bing + 1);
					//  gaps ����Ʈ���� ���� �¼��� ���� �¼��� ������ �ҷ��� �ش��ϴ� ��ŭ ���� ���
					for (int i = 0; i < gaps[bing] - 1; i++) {
						std::cout << "            ";
					}
					// ���� ���̿� ���� �¼� ��� ���
					if (high == 0) {
						std::cout << " ---------- ";
					}
					else if (high == 1) {
						std::cout << "|          |";
					}
					else if (high == 2) {
						if (seat_num < 10) {
							std::cout << "|    0" << seat_num << "    |";
						}
						else {
							std::cout << "|    " << seat_num << "    |";
						}
					}
					else if (high == 3) {
						if (seat_instance_list[seat_num - 1].is_reserved()) {
							std::cout << "|  �����  |";
						}
						else {
							std::cout << "|          |";
						}
					}
					else if (high == 4) {
						std::cout << "|          |";
					}
					else if (high == 5) {
						std::cout << " ---------- ";
					}
				}
				std::cout << std::endl;
			}
		}
	}
	// StudyRoom �ʱ� ����
	void init_set(int size, int coordinate[][2]) {
		max_size = size;
		seat_coordinate = new int* [size];
		seat_instance_list = new Seat[size];
		for (int i = 0; i < size; i++) {
			seat_coordinate[i] = new int[2];
			seat_coordinate[i][0] = coordinate[i][0];
			seat_coordinate[i][1] = coordinate[i][1];
			seat_instance_list[i].init_set(i + 1);
		}
		init_setting = true;
	}

	// ����
	void reserve(int num) {
		if (seat_instance_list[num - 1].is_reserved()) {
			std::cout << "�̹� ����Ǿ� �ִ� �¼��Դϴ�. �ٸ� �¼��� ������ �ֽʽÿ�." << std::endl;
			return;
		}
		int st_num;
		std::string st_name;
		int pw;
		std::cout << "�й��� �Է��� �ֽʽÿ� : ";
		std::cin >> st_num;
		std::cout << std::endl << "�̸��� �Է��� �ֽʽÿ� : ";
		std::cin >> st_name;
		std::cout << std::endl << "���� ��� ��й�ȣ�� �Է��� �ֽʽÿ� (4�ڸ� ����) : ";
		std::cin >> pw;
		if (pw > 9999 || pw < 1000 || std::cin.fail()) {
			std::cout << "�߸��� ��й�ȣ�Դϴ�." << std::endl;
			Sleep(500);
			return;
		}
		seat_instance_list[num - 1].reserve(st_num, st_name, pw);
		std::cout << std::endl << "������ �Ϸ�Ǿ����ϴ�." << std::endl;
	}

	// ���� ���
	void cancel_reservation(int num) {
		if (!seat_instance_list[num - 1].is_reserved()) {
			std::cout << "����Ǿ� ���� ���� �¼��Դϴ�." << std::endl;
			return;
		}
		bool cancel = seat_instance_list[num - 1].cancelation();
		if (cancel) {
			std::cout << "������ ��ҵǾ����ϴ�." << std::endl;
			return;
		}
		else {
			std::cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << std::endl;
			return;
		}
	}

	// ������ �¼��� ������ ���
	void show_seat_status(int num) {
		seat_instance_list[num - 1].print_status();
	}
	StudyRoom() {
		init_setting = false;
	}
};

// ------------------------------------------------------------------------------------------------------------

int main() {
	StudyRoom e7;
	// �¼� ��ǥ�� �ݵ�� ������ ������ �����ؼ� �Է��ؾ� ��!
	int e7_coordinate[23][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {5, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {5, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {5, 4}, {3, 6}, {4, 6}, {5, 6} };
	e7.init_set(23, e7_coordinate);
	int max_seat = 23;
	int select = 0;
	while (true) {
		system("cls");
		std::cout << "\n---------------     ������ ���� ���� ���α׷�     ---------------" << std::endl;
		std::cout << std::endl << "\n���� ���õ� ������ : E7" << std::endl;
		std::cout << std::endl << "1. �¼� ��ȸ		2. ������ ����		3. ����" << std::endl << "\n�Է� : ";
		std::cin >> select;
		if (select == 1) {
			while (true) {
				system("cls");
				e7.print();
				std::cout << "\n\n1. �¼� ����		2. �ڷ� ����" << std::endl << "\n�Է� : ";
				std::cin >> select;
				if (select == 1) {
					std::cout << "\n�¼� ��ȣ�� �Է��� �ֽʽÿ� : ";
					std::cin >> select;
					if (select > max_seat || select < 0 || std::cin.fail()) {
						std::cout << "�߸��� �Է��Դϴ�." << std::endl;
						Sleep(1000);
						continue;
					}
					int selected_seat = select;
					system("cls");
					e7.show_seat_status(select);
					std::cout << std::endl << "1. ����		2. ���� ���		3. �ڷ� ����" << std::endl << "\n�Է� : ";
					std::cin >> select;
					system("cls");
					if (select == 1) {
						e7.reserve(selected_seat);
						Sleep(1500);
						system("cls");
					}
					else if (select == 2) {
						e7.cancel_reservation(selected_seat);
						Sleep(1500);
						system("cls");
					}
					else if (select == 3) {
						system("cls");
						continue;
					}
					else {
						std::cout << "�߸��� �Է��Դϴ�." << std::endl;
						Sleep(500);
					}
				}
				else if (select == 2) {
					system("cls");
					break;
				}
				else {
					std::cout << "�߸��� �Է��Դϴ�." << std::endl;
					Sleep(500);
				}
				continue;
			}
		}
		else if (select == 2) {
			std::cout << "�̱���" << std::endl;
			Sleep(500);
			system("cls");
		}
		else if (select == 3) {
			system("cls");
			break;
		}
		else {
			std::cout << "�߸��� �Է��Դϴ�." << std::endl;
			Sleep(500);
		}
	}
	return 0;
}

// Howoo's ass, beautiful ass