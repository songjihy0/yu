#include<iostream>
#include<stdlib.h>
#include "windows.h"
#include <fstream>
using namespace std;

void start()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl
		<< "         0                                                                        000000000000 " << endl
		<< "         0                                            0000000000                  0             " << endl
		<< "         0                   00000000000                                          0  000000000   " << endl
		<< "         0                                                                        0               " << endl
		<< " 00000000000000000                                 00000000000000000              0  000000000         " << endl
		<< "         0                                               0   0                   0   0  0           " << endl
		<< "         0                00000000000000000              0   0                  0    0   0   0        " << endl
		<< "         0                                              0    0                 0     0     0        " << endl
		<< "         0                                             0     0                0      0 0     0           " << endl
		<< "         0                                           0        0 0 0 0        0       0         0                  " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << " ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl
		<< " ┃城市的灯火忽闪忽明，你走在回家的路上，酒精让你有些昏沉。但终究是庆功宴，内心有着难以掩饰欣喜。|" << endl
		<< " ┃“欧阳云！”似有一声声呼喊在耳边回响，你环视周围，却始终找不到那个呼喊你的人。你不由自嘲，酒量|" << endl
		<< " ┃差竟然出现了幻觉。这时，又有声音响起“请您帮帮我们”，你不由一愣，问道：“怎么帮？”转瞬间，仿|" << endl
		<< " ┃佛天旋地转，你 失去了意识.你从昏迷中醒来，便发现眼前有着一个老者，老者向你询问：“敢问你就是来|" << endl
		<< " ┃拯救我们傲来国的勇士吧！？”有着激动和期许，你知道这是一个抉择。                              |" << endl
		<< " ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl;
	system("pause");
	system("cls");
}
void beijing()
{
	cout << "天帝治世，人道昌盛，神圣显化，教化世人。" << endl << endl;
	cout << "天帝秉持天意，治人道，立十二元辰，定时序。" << endl << endl;
	cout << "众生感念天帝恩德，时时祷告，然人有七情六欲，世间邪念亦因此汇集，终成一个集世间万恶的魔物，天帝下令由十二元辰封印魔物，以防其危害苍生。" << endl << endl;
	cout << "世间贪欲无尽，则魔物后力无穷， 日积月累之下，魔物侵染十二元辰神智，封印岌岌可危，天降大任，勇士当战败十二元辰，助其恢复神智，合力镇封魔物，还世间朗朗乾坤。" << endl << endl;
}
void gonglue()
{
	cout << "没错，纯正的官方攻略来了" << endl << endl;
	cout << "直接干货！！！" << endl << endl;
	cout << "1.推荐大家按顺序挑战前十三个房间，这是来自设计者的劝导" << endl << endl;
	cout << "2.第十三个房间是终点" << endl << endl;
	cout << "3.第十四个房间时一个彩蛋，你将获得梦寐以求的力量（魔王的低语）" << endl << endl;
	cout << "4.我们没打算让你们轻松获得彩蛋，所以你们还是别再第十四个房间浪费时间了" << endl << endl;
	cout << "5.打不过就跑呀" << endl << endl;
}
void vectory()
{
	cout << "赤诚之心破其魔念，十二元辰镇其魔身。" << endl << endl;
	cout << "十二元辰化作十二道光，引世间浩荡正气，压其邪念。" << endl << endl;
	cout << "十二元辰轮流值守，镇压魔物，百姓感十二元辰功劳辛苦，以十二元辰记年，以此为生肖，" << endl << endl;
	cout << "此后亦传为生肖年。" << endl << endl;
	cout << endl << endl;
	cout << "视线越来越模糊，眼皮越来越重。" << endl << endl;
	cout << "在起来时，自己躺在沙发上，头脑难免有些沉重。" << endl << endl;
	cout << "原来只是做了一个梦啊，真搞笑，什么时候我也会做这种奇怪的梦。" << endl << endl;
	cout << "欧阳云回到家，准备开发一个游戏，名字叫做《十二元辰》。" << endl << endl;
	cout << "终结" << endl << endl;
}
void defeat()
{
	cout << "你失败了" << endl << endl;
	cout << "没有传说中的大难不死" << endl << endl;
	cout << "没有奇遇连连" << endl << endl;
	cout << "你就这么倒下了" << endl << endl;
	cout << "或许。。。。。。。" << endl << endl;
	cout << "平凡一生会很幸福吧。。。。" << endl << endl;
	cout << "终结" << endl << endl;
}

void save(ROOM room[])
{
	ofstream file1("room.txt");
	for (int i = 0; i<14; i++)
	{
		file1 << room[i].ifboss;
	}
	file1.close();
}

void read(ROOM room[])
{
	int i, team;
	char a;
	ifstream file1("room.txt");
	for (i = 0; i<14; i++)
	{
		file1 >> a;
		team = a - '0';
		room[i].ifboss = team;
	}
	file1.close();

}
void save2(man &player, ROOM room[], Goods goods[])
{
	ofstream file2("role.txt");
	file2 << player.HP << endl;
	file2 << player.present_HP << endl;
	file2 << player.strength << endl;
	file2 << player.denfence << endl;
	file2 << player.Lv << endl;
	file2 << player.experience[0] << endl;
	file2 << player.experience[1] << endl;
	file2 << player.experience[2] << endl;
	file2 << player.money << endl;
	file2 << player.type << endl;
	file2 << player.killnumber << endl;
	file2 << player.enternumber << endl;
	if (player.item[0] != NULL)
	{
		file2 << player.item[0]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[1] != NULL)
	{
		file2 << player.item[1]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[2] != NULL)
	{
		file2 << player.item[2]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[3] != NULL)
	{
		file2 << player.item[3]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[4] != NULL)
	{
		file2 << player.item[4]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[5] != NULL)
	{
		file2 << player.item[5]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[6] != NULL)
	{
		file2 << player.item[6]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[7] != NULL)
	{
		file2 << player.item[7]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[8] != NULL)
	{
		file2 << player.item[8]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.item[9] != NULL)
	{
		file2 << player.item[9]->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.equip1 != NULL)
	{
		file2 << player.equip1->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	if (player.equip2 != NULL)
	{
		file2 << player.equip2->getnumber() << endl;
	}
	else
	{
		file2 << "99" << endl;
	}
	file2.close();
}
void read2(man &player, ROOM room[], Goods goods[])
{

	char array1[20];
	int c;
	ifstream file2("role.txt");

	file2.getline(array1, 20);
	c = atoi(array1);
	player.HP = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.present_HP = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.strength = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.denfence = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.Lv = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.experience[0] = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.experience[1] = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.experience[2] = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.money = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.type = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.killnumber = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	player.enternumber = c;

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[0] = &goods[c];
	}
	if (c == 99)
	{
		player.item[0] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[1] = &goods[c];
	}
	if (c == 99)
	{
		player.item[1] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[2] = &goods[c];
	}
	if (c == 99)
	{
		player.item[2] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[3] = &goods[c];
	}
	if (c == 99)
	{
		player.item[3] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[4] = &goods[c];
	}
	if (c == 99)
	{
		player.item[4] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[5] = &goods[c];
	}
	if (c == 99)
	{
		player.item[5] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[6] = &goods[c];
	}
	if (c == 99)
	{
		player.item[6] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[7] = &goods[c];
	}
	if (c == 99)
	{
		player.item[7] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[8] = &goods[c];
	}
	if (c == 99)
	{
		player.item[8] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		player.item[9] = &goods[c];
	}
	if (c == 99)
	{
		player.item[9] = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		for (int k = 0; k<10; k++)
		{
			if (player.item[k] != NULL&&player.item[k]->getnumber() == c)
			{
				player.equip_weapon(k);
				break;
			}
		}
	}
	if (c == 99)
	{
		player.equip1 = NULL;
	}

	file2.getline(array1, 20);
	c = atoi(array1);
	if (c != 99)
	{
		for (int k = 0; k<10; k++)
		{
			if (player.item[k] != NULL&&player.item[k]->getnumber() == c)
			{
				player.equip_weapon(k);
				break;
			}
		}
	}
	if (c == 99)
	{
		player.equip2 = NULL;
	}

	file2.close();



}

