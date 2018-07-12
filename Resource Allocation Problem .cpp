#include<iostream>
#include <sstream>
#include<fstream>
#include <string>

using namespace std;
int arr[1000][1000], row, col, best_sol[1000][1000];


int find_sol(int days,int course){
	if (course == 0 || days == 0)
		return 0;
	if (best_sol[course][days] != 0)
		return best_sol[course][days];
	int sol = 0;
	for (int i = days-course+1; i >= 1; i--){
		if (sol < arr[i][course] + find_sol(days-i,course-1))
			sol = arr[i][course] + find_sol(days - i, course - 1);
	}
	best_sol[course][days] = sol;
	return sol;
};


int main(){
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");
	string s;
	int num, days;

	getline(fin, s);
read_array:
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++){
			arr[i][j] = 0;
			best_sol[i][j] = 0;
		}
	}
	row = 1;
	while (true){
		istringstream ins(s);
		if (s.size() == 0)
			goto instruct;
		col = 1;
		while (ins >> arr[row][col]){
			col++;
		}
		row++;
		getline(fin, s);
	}

instruct:
	getline(fin, s);
	istringstream ins(s);
	if (fin.eof())
		goto end;
	num = 0;
	while (ins >> days){
		num++;
	}
	if (num > 1)
		goto read_array;
	else if (num == 0)
		goto instruct;

start:
	fout << find_sol(days, col - 1) << endl;
	goto instruct;

	/*
	for (int i = 1; i < row; i++){
		for (int j = 1; j < col; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	*/
end:
	fin.close();
	fout.close();
}