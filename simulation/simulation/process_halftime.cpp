#include "stdafx.h"
#include "process.h"

//边免疫
int process_halftime(int source, double beta, vector<net_work> &reaction_net, set<USERS> &immunized)
{
	srand((unsigned int)time(NULL));
	set<int> infected;
	vector<bool> check_infected(USRNUM,false);
	infected.insert(source);
	check_infected[source] = true;
	int start_time = -1;
	int end_time = -1;
	int max_time_step = int(reaction_net.size());
	for (int i = 0; i < max_time_step; i++)	//找到第一个含有源节点的时间步
	{
		if (reaction_net[i].check_node(source))
		{
			start_time = i;
			break;
		}
	}
	if (start_time == -1)
	{
		cout << "Error:" << source << " is not in the network" << endl;
		return -1;
	}

	set<int>::iterator iter;
	set<USERS>::iterator tmpfind;
	for (int i = start_time; i < max_time_step; i++)
	{
		if (reaction_net[i].edges_num() == 0)
		{
			continue;
		}
		set<int> new_infected;
		for (iter = infected.begin(); iter != infected.end(); iter++)
		{
			bool unhealth = false;
			int neighbors = reaction_net[i].neighbors_num(*iter);
			for (int j = 0; j < neighbors; j++)
			{
				int b = reaction_net[i].find_edge_by_index(*iter, j);
				USERS tmpPAIR;
				if(*iter< b)
				{
					tmpPAIR = make_pair(*iter, b);
				}
				else
				{
					tmpPAIR = make_pair(b, *iter);
				}

				if ((tmpfind = immunized.find(tmpPAIR)) != immunized.end())
				{
					continue;
				}
				//cout << *iter<<','<<b << endl;
				
				if (!check_infected[b])
				{
					if (rand() % 100 / 100 < beta)
					{
						new_infected.insert(b);
					}
				}
				
			}
		}
		for (iter = new_infected.begin(); iter != new_infected.end(); iter++)
		{
			infected.insert(*iter);
			check_infected[*iter] = true;
		}
		/*for (iter = infected.begin(); iter != infected.end(); iter++)
		{
			cout << *iter << ' ';
		}
		cout << endl;*/
		//cout << infected.size() << endl;
		if (infected.size() >= USRNUM / 2)
		{
			
			end_time = i;
			break;
		}
	}
	//cout << "(" << start_time << ", "<< end_time << ")" << endl;
	return end_time - start_time;
}


//节点免疫
int process_halftime(int source, double beta, vector<net_work> &reaction_net, set<int> &immunized)
{
	srand((unsigned int)time(NULL));
	set<int> infected;
	vector<bool> check_infected(USRNUM, false);
	infected.insert(source);
	check_infected[source] = true;
	int start_time = -1;
	int end_time = -1;
	int max_time_step = int(reaction_net.size());
	//int target_num = (USRNUM - int(immunized.size())) / 2;
	int target_num = USRNUM / 2;
	for (int i = 0; i < max_time_step; i++)	//找到第一个含有源节点的时间步
	{
		if (reaction_net[i].check_node(source))
		{
			start_time = i;
			break;
		}
	}
	if (start_time == -1)
	{
		cout << "Error:" << source << " is not in the network" << endl;
		return -1;
	}

	set<int>::iterator iter;
	set<int>::iterator tmpfind;
	for (int i = start_time; i < max_time_step; i++)
	{
		if (reaction_net[i].edges_num() == 0)
		{
			continue;
		}
		set<int> new_infected;
		for (iter = infected.begin(); iter != infected.end(); iter++)
		{
			bool unhealth = false;
			int neighbors = reaction_net[i].neighbors_num(*iter);
			for (int j = 0; j < neighbors; j++)
			{
				int b = reaction_net[i].find_edge_by_index(*iter, j);

				if ((tmpfind = immunized.find(b)) != immunized.end())
				{
					continue;
				}
				//cout << *iter<<','<<b << endl;

				if (!check_infected[b])
				{
					if (double(rand() % 100) / 100 < beta)
					{
						new_infected.insert(b);
					}
				}

			}
		}
		for (iter = new_infected.begin(); iter != new_infected.end(); iter++)
		{
			infected.insert(*iter);
			check_infected[*iter] = true;
		}
		/*for (iter = infected.begin(); iter != infected.end(); iter++)
		{
		cout << *iter << ' ';
		}
		cout << endl;*/
		//cout << infected.size() << endl;
		if (infected.size() >= target_num)
		{

			end_time = i;
			break;
		}
	}
	if(end_time<0)
		cout << "(" << start_time << ", "<< end_time << ")"<< infected.size() << endl;
	return end_time - start_time;
}