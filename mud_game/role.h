#ifndef ROLE_H
#define ROLE_H

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "windows.h"
#include "goods.h"

using namespace std;

class man
{
public:
	man() {}
	void creat_m(int l, int s, int d, int m, int e, string n);
	void creat_p(int l, int s, int d, int a, int m, int e, int lv, string n, int t);

	string getname()
	{
		return name;
	}

	/*战斗*/
	int battle(man NPC);             //战斗
	void win(man npc);                //装备掉落
	void lv_up(man npc);              //升级
	int using_agility(int d);         //闪避

									  /*背包*/
	void equip_weapon(int num);       //物品使用
	void equip_weapon(Goods goods);
	void getgoods(Goods &a);          //获得物品
	void losegoods(int num);          //失去物品
	void showgoods();                 //展示背包
	void showequip();                 //展示装备
	void showrole();                  //人物属性


									  /*商店*/
	void shopping(man k);
	void buy(Goods *sth);
	void creat_s(Goods g[]);

	/*游戏判定*/
	int getkillnumber()
	{
		return killnumber;
	}
	int getenternumber()
	{
		return enternumber;
	}
	void pluskillnumber(int a)
	{
		killnumber += a;
	}
	void plusenternumber(int a)
	{
		enternumber += a;
	}
	//private:
public:
	int HP;                           //生命
	int present_HP;                   //现有生命
	int strength;                     //力量
	int present_strength;             //加刀后攻击
	int denfence;                     //防御
	int present_denfence;             //加甲后防御
	int agility;                      //敏捷
	int Lv;                           //等级
	int experience[3];                //经验
	int money;                        //金钱
	string name;
	int type;                         //人物类型（1.水 2.火 3.木）

	Goods *item[10];                  //背包
	Goods *equip1;
	Goods *equip2;                    //装备

	int killnumber;                   //击杀BOSS数目
	int enternumber;                  //进入特殊房间次数
};

void man::creat_m(int l, int s, int d, int m, int e, string n)
{
	HP = l;
	present_HP = l;
	strength = s;
	denfence = d;
	money = m;
	experience[0] = e;
	name = n;
}

void man::creat_p(int l, int s, int d, int a, int m, int e, int lv, string n, int t)
{
	HP = l;
	present_HP = HP;
	strength = s;
	present_strength = strength;
	denfence = d;
	present_denfence = denfence;
	agility = a;
	money = m;
	for (int i = 0; i < 3; i++)
		experience[i] = e;
	Lv = lv;
	name = n;
	type = t;
	for (int i = 0; i<10; i++)
	{
		item[i] = NULL;
	}
	equip1 = NULL;
	equip2 = NULL;
	killnumber = 0;
	enternumber = 0;
}

/*人物升级*/
void man::lv_up(man npc)
{
	if (Lv < 3)
	    experience[Lv] = experience[Lv - 1] + npc.experience[0] - Lv * 10;
	Lv++;
	if (type == 1)               //水的升级
	{
		HP = HP + 2;
		present_HP = HP;
		strength = strength + 1;
		denfence = denfence + 3;
	}
	else if (type == 2)          //火的升级
	{
		HP = HP + 1;
		present_HP = HP;
		strength = strength + 3;
		denfence = denfence + 2;
	}
	else                         //木的升级
	{
		HP = HP + 3;
		present_HP = HP;
		strength = strength + 2;
		denfence = denfence + 1;
	}
}
/*人物闪避*/
int man::using_agility(int d)
{
	int n;
	srand(time(0));
	n = rand() % 30;
	if (n < 3)
	{
		cout << "你躲避了伤害" << endl;
		d = 0;
	}
	return d;
}
/*战斗*/
int man::battle(man npc)
{
	cout << endl;
	cout << "你与" << npc.name << "开始战斗" << endl;
	while (present_HP != 0 && npc.HP != 0)
	{
		int choice;
		cout << "你的生命值" << present_HP << "/" << HP << endl;
		cout << "                 " << npc.name << "的生命值" << npc.HP << endl << endl;
		cout << "现在是你的回合，你的选择是：" << endl << endl;
		cout << "1.攻击             2.逃跑" << endl << endl;
		cin >> choice;

		do
		{
			if (choice == 2)
			{
				return 3;
				break;
			}
			else if (choice == 1)
			{
				int damge;
				damge = present_strength - npc.denfence;
				if (damge < 0)
					damge = 0;
				npc.HP = npc.HP - damge;
				cout << "你对" << npc.name << "造成了" << damge << "点伤害" << endl << endl;
				break;
			}
			else if (choice != 1 && choice != 2)
			{
				cout << "请重新选择" << endl;
				cin >> choice;
			}
		} while (1);
		if (npc.HP <= 0)                           //战胜npc
		{
			cout << "你战胜了" << npc.name << "，获得金钱" << npc.money << "和经验" << npc.experience[0] << endl << endl;
			money = money + npc.money;
			pluskillnumber(1);
			if (experience[Lv - 1] + npc.experience[0] < Lv * 10)
				experience[Lv - 1] = experience[Lv - 1] + npc.experience[0];
			else
				lv_up(npc);
			return 1;
		}
		else
		{
			int damge;
			damge = npc.strength - present_denfence;
			damge = using_agility(damge);          //闪避判定
			if (damge < 0)
				damge = 0;
			if (present_HP - damge > 0)
			{
				present_HP = present_HP - damge;
				cout << npc.name << "对你造成了" << damge << "点伤害" << endl << endl;
			}
			else
			{
				cout << npc.name << "对你造成了" << damge << "点伤害" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "你被打败了！" << endl;
				cout << "游戏结束" << endl;
				return 0;
				break;
			}
		}
		system("pause");
		system("cls");
	}
	return 1;
}

/*装备掉落*/
void man::win(man npc)
{
	Goods sword;
	Goods amor;
	sword.assignment("圣剑", "传承已久的圣物，拥有不可思议的力量", 12, 0, 0, 80, 5);
	amor.assignment("圣甲", "传承已久的圣物，拥有不可思议的力量", 0, 10, 0, 80, 2);
	if (npc.name == "dragen")
	{
		cout << "你打败了dragen获得了装备圣剑！" << endl;
		getgoods(sword);
	}
	else if (npc.name == "tiger" || npc.name == "snake" || npc.name == "dog")
	{
		int n;
		srand(time(0));
		n = rand() % 100;
		if (n < 50)
		{
			cout << "你打败了" << npc.name << "获得了装备圣甲！" << endl;
			getgoods(amor);
		}
	}
}

/*物品使用*/
void man::equip_weapon(int num)
{
	if (item[num] == NULL)
	{
		cout << "无法使用" << endl;
	}
	else
	{

		if (item[num]->getadd_attack()>0)
			present_strength = strength + item[num]->getadd_attack();
		if (item[num]->getadd_defence()>0)
			present_denfence = denfence + item[num]->getadd_defence();
		present_HP = present_HP + item[num]->getadd_HP();
		if (present_HP > HP)
		{
			present_HP = HP;
		}
		if (item[num]->getnumber() >= 0 && item[num]->getnumber() <= 2)
		{
			equip1 = item[num];
		}
		if ((item[num]->getnumber() >= 3 && item[num]->getnumber() <= 5) || item[num]->getnumber() == 9)
		{
			equip2 = item[num];
		}
		if (item[num]->getnumber() >= 6 && item[num]->getnumber() <= 8)
		{
			item[num] = NULL;
		}
	}
}
void man::equip_weapon(Goods goods)
{
	if (goods.getadd_attack()>0)
		present_strength = strength + goods.getadd_attack();
	if (goods.getadd_defence()>0)
		present_denfence = denfence + goods.getadd_defence();

	if (goods.getnumber() >= 0 && goods.getnumber() <= 2)
	{
		equip1 = &goods;
	}
	if ((goods.getnumber() >= 3 && goods.getnumber() <= 5) || goods.getnumber() == 9)
	{
		equip2 = &goods;
	}
}
/*获得物品*/
void man::getgoods(Goods &a)
{
	for (int i = 0; i<10; i++)
	{
		if (item[i] == NULL)
		{
			item[i] = &a;
			break;
		}
	}
}
/*失去物品*/
void man::losegoods(int num)
{
	money = money + item[num]->getprice() / 2;
	item[num] = NULL;
}
/*展示背包*/
void man::showgoods()
{
	int choice = 1;
	while (choice)
	{

		cout << endl << "背包状况:" << endl;
		int num = 0;
		for (int i = 0; i<10; i++)
		{
			if (item[i] != NULL)
			{
				cout << num++ << " " << item[i]->getname() << endl;
			}
			if (item[i] == NULL)
			{
				cout << num++ << " " << "空" << endl;
			}
		}
		cout << "选择操作" << endl << "1.使用装备 2.查看道具属性 3.售卖装备 0.退出" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "选择装备" << endl;
			int num1;
			cin >> num1;
			equip_weapon(num1);
			showequip();
			break;
		}
		case 2:
		{
			cout << "选择装备" << endl;
			int num2;
			cin >> num2;
			item[num2]->display();
			break;
		}
		case 3:
		{
			cout << "选择装备" << endl;
			int num3;
			cin >> num3;
			losegoods(num3);
			break;
		}
		}
		system("pause");
		system("cls");
	}
}
/*展示装备（已经穿戴）*/
void man::showequip()
{
	cout << endl << "装备状况" << endl;
	if (equip1 != NULL)
	{
		cout << "防具：" << equip1->getname() << endl;
	}
	else if (equip1 == NULL)
	{
		cout << "防具：空" << endl;
	}
	if (equip2 != NULL)
	{
		cout << "武器：" << equip2->getname() << endl;
	}
	else if (equip2 == NULL)
	{
		cout << "武器：空" << endl;
	}
}
/*人物面板*/
void man::showrole()
{
	cout << "人物面板" << endl;
	cout << "姓名：" << name << endl;
	cout << "等级：" << Lv << endl;
	cout << "生命：" << present_HP << "/" << HP << endl;
	cout << "攻击：" << present_strength << endl;
	cout << "防御：" << present_denfence << endl;
	cout << "敏捷：" << agility << endl;
	cout << "金钱：" << money << "文" << endl;
	system("pause");
	system("cls");
}
/*怪物数据*/
void creat_monster(man men[])
{
	/*生命值，攻击，防御，金钱，经验，名字*/
	men[0].creat_m(20, 4, 3, 4, 1, "mouse");
	men[1].creat_m(21, 6, 3, 6, 2, "chicken");
	men[2].creat_m(22, 5, 3, 6, 3, "rabbit");
	men[3].creat_m(25, 6, 3, 8, 4, "pig");
	men[4].creat_m(30, 7, 4, 6, 4, "bull");
	men[5].creat_m(28, 8, 4, 8, 4, "sheep");
	men[6].creat_m(32, 7, 4, 8, 5, "horse");
	men[7].creat_m(28, 8, 5, 10, 7, "monkey");
	men[8].creat_m(45, 10, 5, 10, 8, "dog");
	men[9].creat_m(48, 11, 5, 12, 7, "snake");
	men[10].creat_m(50, 12, 5, 12, 8, "tiger");
	men[11].creat_m(54, 13, 6, 14, 10, "dragen");
	men[12].creat_m(150, 15, 7, 0, 0, "big boss");

}
/*创建人物*/
void creat_player(man &player)
{
	cout << "请选择你的角色属性：" << endl;
	cout << "1.水系（高防御）" << endl;
	cout << "2.火系（高攻击）" << endl;
	cout << "3.木系（高生命）" << endl;
	int choice;
	cin >> choice;

	/*创建人物（生命值，力量，防御，敏捷，钱，经验，等级，名字，种类）*/

	do
	{
		if (choice == 1)
			player.creat_p(20, 4, 3, 3, 50, 0, 1, "欧阳云", 1);
		else if (choice == 2)
			player.creat_p(18, 6, 2, 3, 50, 0, 1, "欧阳云", 2);
		else if (choice == 3)
			player.creat_p(22, 5, 1, 3, 50, 0, 1, "欧阳云", 3);
		else
			cout << "输入错误" << endl;
	} while (choice != 1 && choice != 2 && choice != 3);
	cout << "创建成功" << endl;
	system("pause");
	system("cls");
}
/*创建商人*/
void man::creat_s(Goods g[])
{
	for (int i = 0; i < 10; i++)
		item[i] = NULL;
	getgoods(g[0]);
	getgoods(g[1]);
	getgoods(g[2]);
	getgoods(g[3]);
	getgoods(g[4]);
	getgoods(g[5]);
	getgoods(g[6]);
	getgoods(g[7]);
	getgoods(g[8]);
}
/*购买物品*/
void man::buy(Goods *sth)
{
	int m = money - sth->getprice();
	if (m >= 0)
	{
		getgoods(*sth);
		cout << "交易成功，你获得了" << sth->getname() << "!" << endl;
		money = m;
	}
	else
		cout << "你的钱不够！" << endl;
}
/*打开商店*/
void man::shopping(man k)
{
	cout << "我这里有：" << endl;
	for (int i = 0; k.item[i] != NULL; i++)
	{
		cout << i + 1 << ".";
		cout << endl;
		k.item[i]->display();
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "你拥有金钱" << money << "文" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "0.退出" << endl;
	cout << "你需要什么？" << endl;
	int n = 1;
	while (n != 0)
	{
		cin >> n;
		switch (n)
		{
		case 0:
			break;
		case 1:
			buy(k.item[0]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 2:
			buy(k.item[1]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 3:
			buy(k.item[2]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 4:
			buy(k.item[3]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 5:
			buy(k.item[4]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 6:
			buy(k.item[5]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 7:
			buy(k.item[6]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 8:
			buy(k.item[7]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 9:
			buy(k.item[8]);
			cout << "你还需要什么？" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "你拥有金钱" << money << "文" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		default:
			cout << "请重新输入" << endl;
			break;
		}
	}
	cout << "再见！" << endl;
}

#endif
// ROLE_H
