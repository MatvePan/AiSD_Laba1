#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

void printBinaryShortInt(short int num) {
	int size = sizeof(short int) * 8;
	for (int i = size - 1; i >= 0; i--) {
		cout << ((num >> i) & 1);
		if (i % 8 == 0) cout << " ";
	}
	cout << endl;
}

void printBinaryLongDouble(long double num) {
	unsigned char* bytes = reinterpret_cast<unsigned char*>(&num);
	int size = sizeof(long double);
	for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            cout << ((bytes[i] >> j) & 1); 
        }
        if (i == size - 2) cout << ".";
		cout << " ";
	}
	cout << endl;
}


short int swapBitsShortInt(short int num, int bit1, int bit2) {
	int b1 = (num >> bit1) & 1;
	int b2 = (num >> bit2) & 1;
	if (b1 != b2) num ^= (1 << bit1) | (1 << bit2);
	return num;
}

long double swapBitsLongDouble(long double num, int bit1, int bit2) {
	unsigned char* bytes = reinterpret_cast<unsigned char*>(&num);
	int byte1 = bit1 / 8;
	int byte2 = bit2 / 8;
	int offset1 = bit1 % 8;
	int offset2 = bit2 % 8;

	int b1 = (bytes[byte1] >> offset1) & 1;
	int b2 = (bytes[byte2] >> offset2) & 1;
	if (b1 != b2) {
		bytes[byte1] ^= (1 << offset1);
		bytes[byte2] ^= (1 << offset2);
	}
	return num;
}

int main() {
    setlocale(LC_ALL, "ru");
	short int shortNum;
	long double longDoubleNum;
	int numPairs, bit1, bit2;

    // ���� short int
    cout << "������� �������� ���� short int: ";
    cin >> shortNum;

    // ���� long double
    cout << "������� �������� ���� long double: ";
    cin >> longDoubleNum;

    // ����� ��������� �������������
    cout << "\n�������� ������������� short int:\n";
    printBinaryShortInt(shortNum);
    cout << "\n�������� ������������� long double:\n";
    printBinaryLongDouble(longDoubleNum);

    // ������ ���������� ��� ��� ������
    cout << "\n������� ���������� ��� ��� ��� ������: ";
    cin >> numPairs;

    // ����� ����� ��� short int
    for (int i = 0; i < numPairs; i++) {
        cout << "������� ������ ����� ��� ������ � short int (�� 0 �� 15): ";
        cin >> bit1 >> bit2;
        shortNum = swapBitsShortInt(shortNum, bit1, bit2);
    }

    // ����� ����� ��� long double
    for (int i = 0; i < numPairs; i++) {
        cout << "������� ������ ����� ��� ������ � long double (�� 0 �� "
            << (sizeof(long double) * 8 - 1) << "): ";
        cin >> bit1 >> bit2;
        longDoubleNum = swapBitsLongDouble(longDoubleNum, bit1, bit2);
    }

    // ����� ���������������� �������������
    cout << "\n��������������� ������������� short int:\n";
    printBinaryShortInt(shortNum);
    cout << "��������������� �������� short int: " << shortNum << endl;

    cout << "\n��������������� ������������� long double:\n";
    printBinaryLongDouble(longDoubleNum);
    cout << "��������������� �������� long double: " << longDoubleNum << endl;

    return 0;
}