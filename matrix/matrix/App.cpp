#include<glm/mat4x4.hpp>
#include<iostream>

using namespace std;

int main() {
	int a[] = { 1,2,3,4,5,6 };

	for (int i = 0; i < 6; i++) {
		cout << a[i] << endl;
	}

	for (int i = 0; i < 6; i++) {
		cout << *(a+i) << endl;
	}
	
	return -1;

}