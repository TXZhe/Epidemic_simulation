// simulation.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "net_work.h"
#include "SIS.h"
#include <vector>
#include <list>
#include <string>

using namespace std;

int main()
{
	double beta = 0, omega = 0;

	int usr1, usr2, USRNUM = 10146, LOCANUM = 4;
	int ts, loc;
	char coma;
	string network_file, set_file;

	srand((unsigned int)time(NULL));

	cout << "Input bate: ";
	cin >> beta;
	cout << "Input omega: ";
	cin >> omega;
	cout << "Input network file: ";
	cin >> network_file;
	cout << "Input setting file: ";
	cin >> set_file;

	fstream fset;
	fset.open(set_file, ios::in);
	fset >> USRNUM >> LOCANUM;
	fset.close();

	//---------------------读取时变网络---------------------
	cout << "Inputting reaction network..." << endl;

	list<net_work> reaction_net;

	int timeStep = 1;

	net_work rn_tmp(USRNUM);
	fstream fin;
	fin.open(network_file, ios::in);
	while (!fin.eof())
	{
		fin >> usr1 >> coma >> usr2 >> coma >> ts >> coma >> loc;
		if (ts == timeStep)
		{
			rn_tmp.add_edge(usr1, usr2, loc);
		}
		else
		{
			reaction_net.push_back(rn_tmp);
			rn_tmp.clear();
			timeStep++;
		}
	}
	fin.close();

	cout << "Input reaction network finished, total "<< timeStep <<" timesteps." << endl;
	
	/*for (int i = 0; i < reaction_net.size(); i++)
	{
		reaction_net[i].print();
	}
	system("pause");*/

	//---------------------开始仿真---------------------
	vector<int> seed;
	seed.push_back(0);
	SIS sis_process(USRNUM, reaction_net, seed, beta, omega);
	sis_process.begin(10);

	fstream fout;
	string outfile;
	outfile = "result_" + to_string(beta) + "_" + to_string(omega) + ".csv";
	fout.open(outfile, ios::out);
	sis_process.print_result(fout);
	fout.close();

	system("pause");
	return 0;
}

