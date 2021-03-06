#include <iostream>
#include <string>
#include <fstream>
#include "h.h"
using namespace std;

string& ltrim(string& str, const string& chars = "\t\n\v\f\r ");
string& rtrim(string& str, const string& chars = "\t\n\v\f\r ");
string& trim(string& str, const string& chars = "\t\n\v\f\r ");
int countWords(const char* str);
systemOfEquations ReadDrSaniFormat()
{
	cout << "Enter file address: ";
	string fileAdd;
	cin >> fileAdd;
	fileAdd = "C:\\Users\\Reza\\Desktop\\axb_1.txt";
	ifstream file;
	file.open(fileAdd.c_str());
	string word;
	file >> word;
	int rows = stoi(word);
	file >> word;
	int nonzeros = stoi(word);
	double* val = new double[nonzeros];
	for (int i = 0; i < nonzeros; i++)
	{
		file >> word;
		val[i] = stod(word);
	}
	int* col_index = new int[nonzeros];
	for (int i = 0; i < nonzeros; i++)
	{
		file >> word;
		col_index[i] = stoi(word);
	}
	int* row_ptr = new int[rows + 1];
	for (int i = 0; i <= rows; i++)
	{
		file >> word;
		row_ptr[i] = stoi(word);
	}
	double* b = new double[rows];
	for (int i = 0; i < rows; i++)
	{
		file >> word;
		b[i] = stod(word);
	}
	double* x = new double[rows];
	for (int i = 0; i < rows; i++)
	{
		file >> word;
		x[i] = stod(word);
	}
	file.close();
	systemOfEquations sys;
	sys.numOfEquations = rows;
	sys.b = b;
	sys.x = x;
	sys.A = new double* [rows];
	for (int i = 0; i < rows; i++)
		sys.A[i] = new double[rows];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < rows; j++)
			sys.A[i][j] = 0;
	int current_row = -1;
	for (int i = 0; i < nonzeros; i++)
	{
		if (i == row_ptr[current_row + 1]) current_row++;
		sys.A[current_row][col_index[i]] = val[i];
	}
	return sys;
}

systemOfEquations ReceiveMatrices()
{
	cout << "Enter file address for matrix A: ";
	string addressMatA;
	cin >> addressMatA;
	cout << "Enter file address for matrix b: ";
	string addressMatB;
	cin >> addressMatB;
	ifstream* Afile = new ifstream(addressMatA.c_str());
	ifstream* Bfile = new ifstream(addressMatB.c_str());
	string line;
	int count = 0;
	while (getline(*Bfile, line)) count++;
	Bfile->close();
	delete[] Bfile;
	systemOfEquations system;
	system.numOfEquations = count;
	system.b = new double[count];
	system.A = new double* [count];
	for (int i = 0; i < count; i++)
		system.A[i] = new double[count];
	Bfile = new ifstream(addressMatB.c_str());
	for (int i = 0; i < count; i++)
	{
		getline(*Bfile, line);
		trim(line);
		system.b[i] = stod(line);
	}
	Bfile->close();
	for (int i = 0; i < count; i++)
	{
		getline(*Afile, line);
		trim(line);
		for (int j = 0; j < count; j++)
		{
			string temp;
			temp = line.substr(0, line.find(" "));
			if (j < (count - 1))
				line = line.substr(line.find(" "), line.length());
			trim(line);
			trim(temp);
			if (temp.empty()) break;
			system.A[i][j] = stod(temp);
		}
	}
	Afile->close();
	delete Afile;
	return system;
}

matrix2D Receive2Dmatrix()
{
	cout << "Enter matrix file address: ";
	string address;
	cin >> address;
	ifstream file(address.c_str());
	string line;
	int i = 0;
	while (getline(file, line)) i++;
	file.clear();
	file.seekg(0, ios::beg);
	getline(file, line);
	trim(line);
	int j = countWords(line.c_str());
	file.clear();
	file.seekg(0, ios::beg);
	matrix2D mat;
	mat.i = i;
	mat.j = j;
	mat.A = new double* [i];
	for (int k = 0; k < i; k++) mat.A[k] = new double[j];
	for (int l = 0; l < i; l++)
	{
		getline(file, line);
		trim(line);
		for (int m = 0; m < j; m++)
		{
			string temp;
			temp = line.substr(0, line.find(" "));
			if (m < (j - 1))
				line = line.substr(line.find(" "), line.length());
			trim(line);
			trim(temp);
			if (temp.empty()) break;
			mat.A[l][m] = stod(temp);
		}
	}
	return mat;
}

int countWords(const char* str)
{
	bool inSpaces = true;
	int numWords = 0;

	while (*str != '\0')
	{
		if (std::isspace(*str))
		{
			inSpaces = true;
		}
		else if (inSpaces)
		{
			numWords++;
			inSpaces = false;
		}

		++str;
	}

	return numWords;
}

string& ltrim(string& str, const string& chars)
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

string& rtrim(string& str, const string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

string& trim(string& str, const string& chars)
{
	return ltrim(rtrim(str, chars), chars);
}