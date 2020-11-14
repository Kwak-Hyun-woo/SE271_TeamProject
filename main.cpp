#include "tp.h"

#include <iostream>
#include <windows.h>

int main() {
	StudyRoom e7;
	// �¼� ��ǥ�� �ݵ�� ������ ������ �����ؼ� �Է��ؾ� ��!
	int e7_coordinate[23][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {5, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {5, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {5, 4}, {3, 6}, {4, 6}, {5, 6} };
	e7.init_set(23, e7_coordinate);
	int max_seat = 23;
	int select;
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
					if (select > max_seat || select < 0) {
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