#include "stdafx.h"
#include "immunity.h"

set<USERS> immunize_edge(double pha, int immune_type, vector<vector<USERS>> &social_tie, int minlenth, vector<USERS> &edges)
{
	srand((unsigned int)time(NULL));
	//vector<USERS> immunized;

	set<USERS> immunized;
	int immu_size = int(minlenth * pha);

	switch (immune_type)
	{
	case 1: //随机选取一定比例的边免疫
		{
			int range = int(edges.size());
			vector<int> tmpimmu(range);
			for (int i = 0; i < range; i++)
			{
				tmpimmu[i] = i;
			}
			random_shuffle(tmpimmu.begin(), tmpimmu.end());

			for (int i = 0; i < immu_size; i++)
			{
				immunized.insert(edges[tmpimmu[i]]);
			}
			break;
		}

	case 2: //随机选S边
	case 3: //随机选F边
	case 4: //随机选FS边
	case 5: //随机选IR边
		{
			int range = int(social_tie[immune_type - 2].size());
			vector<int> tmpimmu(range);
			for (int i = 0; i < range; i++)
			{
				tmpimmu[i] = i;
			}
			random_shuffle(tmpimmu.begin(), tmpimmu.end());
		
			for (int i = 0; i < immu_size; i++)
			{
				immunized.insert(social_tie[immune_type - 2][tmpimmu[i]]);
			}
			break;
		}

	case 6: //熟人免疫
		{
			
			break;
		}

	default:
		cout << "ERROR: immune_type " << immune_type << " out of range!"<< endl;
		break;
	}

	return immunized;
}