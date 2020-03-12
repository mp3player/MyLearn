#include "ObjLoader.h"

#include<iostream>
#include<fstream>

using namespace std;

ObjLoader::ObjLoader(const char* path)
{
	char info[512];
	fstream f(path, ios::in);
	while (f.getline(info, sizeof(info))) {
		cout << info << endl;
	}
}

