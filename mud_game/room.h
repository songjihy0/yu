#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include<stdlib.h>
#include"windows.h"
#include"role.h"

using namespace std;

class ROOM
{
public:
	ROOM() {};
	ROOM(int number, string name);
	void XuanXiang();
	void Miaoshu();

	string name;
	int ifboss = 1;
	int number = 1;

};

ROOM::ROOM(int number, string name)
{
	this->number = number;
	this->name = name;
}

void ROOM::XuanXiang()
{
	cout << "1.观察   2.四处翻找   " << endl;
	int choice;
	cin >> choice;
	if (choice == 1 || choice == 2)
	{
		cout << "无事发生,你决定离开" << endl;

	}
}

//房间描述
void ROOM::Miaoshu()
{
	if (number == 1)
		cout << endl << "你进入了房间，略显阴暗的房间中，一只尺许长的紫金色毛发的老鼠映入眼帘。这就是子鼠" << endl
		<< "吧。走动时的响声显然让子鼠察觉，一双暗金色的鼠瞳凝望着你。你知道，这应该就是十二" << endl
		<< "元辰中的子鼠了，不过，子鼠貌似有些奇特。" << endl;

	if (number == 2)
		cout << endl << "你进入了房间，金黄的稻草散落在房间的各处，在一块布满青苔的岩石上，雄赳赳气昂昂的" << endl
		<< "公鸡在那里傲立，鲜红的鸡冠饱满圆润，尾羽鲜艳动人，单从卖相上来看，酉鸡确实是不错" << endl
		<< "的，不过，当你看到岩石上丛横交错的抓痕时，你明白了什么。" << endl;

	if (number == 3)
		cout << endl << "你进入了房间，忽然进入一片冰雪的世界让你有点惊奇，但你很快紧了紧衣服，好抵挡一下" << endl
		<< "寒气。一只雪兔出现在了你的眼前，你知道，这边是卯兔了，只要击败它，你就离完成使命" << endl
		<< "更进一步，集中精神，不要大意。" << endl;

	if (number == 4)
		cout << endl << "你进入了房间，首先映入眼帘的便是位于房间正中的篝火，跳跃的火苗如同火的精灵，在飘" << endl
		<< "摇之后，纷纷汇集到房间的角落，一只小猪趴在那里，布满血丝的双眼有些令人畏惧，随着" << endl
		<< "火苗的汇集，小猪的眼神越来越可怕。" << endl;

	if (number == 5)
		cout << endl << "你进入了房间，一头浑身金黄，貌似绸缎的牛正在盯着你，并不是十分高大的提醒却带来了" << endl
		<< "十足的压迫力，疯狂的双眸凝望，一对牛角似乎随时都会冲到你的面前，你不有自主有些焦" << endl
		<< "急，你必须赶紧做点什么了。" << endl;

	if (number == 6)
		cout << endl << "你进入了房间，在那略显昏暗的房间里，你看到了未羊，双目无神，漫无目的的在房间内走" << endl
		<< "动，正当你准备迈步前进时，未羊忽然直勾勾地盯着你，猩红的双眸更是添加了几分狰狞，" << endl
		<< "似乎你必须要经历一番恶战。" << endl;

	if (number == 7)
		cout << endl << "你进入了房间，绿草丛生的房间让你眼前一亮，不远处，一匹骏马向你奔腾而来，嘶鸣阵阵，" << endl
		<< "带给你震撼，虽然只是孤身，却展现出了雷霆万钧之势，面对那汹涌而来的阵势，你知道，" << endl
		<< "你需要全力以赴来应对危局。" << endl;

	if (number == 8)
		cout << endl << "你进入了房间，在树木丛生的房间里，一只金猴在林间翻飞，跳动的身影如同一道金色的闪" << endl
		<< "电，电光火石之间，它便直冲你的面门而来，你赶紧侧身躲开，就地打了一个滚，堪堪躲开" << endl
		<< "一块飞石，你赶紧端正身子，全神贯注。" << endl;

	if (number == 9)
		cout << endl << "你进入了房间，刚刚进入，你便发现浑身乌黑的巨犬趴在门口不远处，涎液从张开的大口不" << endl
		<< "断地流出，铜铃般的眼睛是不是闪烁着危险的光芒。面对着小牛犊子一样的巨犬，你不敢有" << endl
		<< "丝毫大意，你需要全力以赴。" << endl;

	if (number == 10)
		cout << endl << "你进入了房间，在这个潮湿的房间里，你看到了一条翠绿色的蛇，翠如美玉的颜色并没有带" << endl
		<< "给你任何美好的联想，反而是耳边的嘶嘶声让你感觉头皮发麻。双目紧紧盯着那修长的蛇躯，" << endl
		<< "你尽力保持着距离，小心翼翼。" << endl;

	if (number == 11)
		cout << endl << "你进入了房间，感受到一阵阵压迫力，不由屏息，巨虎卧在一块青石上，虽然它并没有立即" << endl
		<< "对你发动攻击，但是从那猩红的眼睛里，你似乎看到了自己并不美妙的未来，暗自咽下一口" << endl
		<< "唾液，你浑身紧绷，戒备起来。" << endl;

	if (number == 12)
		cout << endl << "你进入了房间，首先映入眼帘的就是那令人目瞪口呆的生物，虽然之前你从来没有亲眼见过，" << endl
		<< "但你知道，那个虽在假寐，但仍旧无比威严的存在，就是龙。轻吐一口气，你知道，你将面" << endl
		<< "临巨大的挑战，但你相信你会成功。" << endl;

	if (number == 13)
		cout << endl << "你和十二元辰来到到魔王的封印之地。" << endl << endl
		<< "你：魔物！你破环封印，想要跳脱而出，为祸苍生，今日必将你永世镇压！" << endl << endl
		<< "你：世间万恶不绝，吾魔魂不灭" << endl << endl;

	if (number == 14)
		cout << endl << "你进入了一个布满灰尘到处透露着诡异的破败房间，但房间里好像没有什么异样" << endl << endl;
}

int enternumber = 1;

void setROOM(ROOM room[])
{
	ROOM room0(1, "子间");
	room[0] = room0;

	ROOM room1(2, "酉间");
	room[1] = room1;

	ROOM room2(3, "卯间");
	room[2] = room2;

	ROOM room3(4, "亥间");
	room[3] = room3;

	ROOM room4(5, "丑间");
	room[4] = room4;

	ROOM room5(6, "未间");
	room[5] = room5;

	ROOM room6(7, "午间");
	room[6] = room6;

	ROOM room7(8, "申间");
	room[7] = room7;

	ROOM room8(9, "戌间");
	room[8] = room8;

	ROOM room9(10, "巳间");
	room[9] = room9;

	ROOM room10(11, "寅间");
	room[10] = room10;

	ROOM room11(12, "辰间");
	room[11] = room11;

	ROOM room12(13, "诡异的房间");
	room[12] = room12;

	ROOM room13(14, "神秘的房间");
	room[13] = room13;
}

int Comein = 0;

//始于出生点 选择房间
int map(ROOM room[], man &player, man men[], Goods goods[])
{

	cout << endl << "你想要去哪里：" << endl << endl;
	cout << "1.子间   2.酉间    3.卯间   4.亥间   5.丑间  6.未间" << endl
		<< "7.午间   8.申间    9.戌间  10.巳间  11.寅间 12.辰间" << endl
		<< "13.诡异的房间    14.神秘的房间   " << endl << endl
		<< "0.返回" << endl;

	int i = 1;
	int Choice;
	cin >> Choice;

	system("pause");
	system("cls");

	if (Choice >= 1 && Choice < 13)
	{
		if (room[Choice - 1].ifboss == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			room[Choice - 1].Miaoshu();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			i = player.battle(men[Choice - 1]);
			if (i == 1)
			{
				room[Choice - 1].ifboss = 0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << endl << endl << men[Choice - 1].getname() << "悠悠醒来，它告诉你会在你面临魔王的时候助你一臂之力，现在它要沉睡了" << endl;
				cout << endl << endl << "点点光芒出现" << men[Choice - 1].getname() << "消失在你的视野里" << endl << endl;
			}
			if (i == 3)
			{
				cout << "你落荒而逃" << endl << endl;
			}
		}
		else
		{
			cout << "空空如也的房间" << endl << endl;
		}
	}

	else if (Choice == 13 && player.getkillnumber() == 12)
	{
		room[Choice - 1].Miaoshu();
		i = player.battle(men[Choice - 1]);      //打完返回主界面！！！！！！！！！！！！！！！！！！！！！！！！
	}

	else if (Choice == 13 && player.getkillnumber() != 12)
	{
		cout << endl << "你觉得这个房间无比诡异，但是依旧无事发生。于是你赶紧离开了房间。" << endl << endl;
	}

	else if (Choice == 14 && player.getenternumber() == 2 && (player.getkillnumber() == 6 || player.getkillnumber() == 4 || player.getkillnumber() == 1))
	{
		cout << "你再次进入了房间" << endl;
		cout << "恭喜你获得了法杖，物品已放入背包" << endl;
		player.getgoods(goods[9]);
		player.plusenternumber(1);
	}

	else if (Choice < 1 || Choice>14)
	{
		cout << "返回主页面" << endl;
	}

	else
	{
		room[Choice - 1].Miaoshu();
		room[Choice - 1].XuanXiang();
		player.plusenternumber(1);
	}
	return i;
}

#endif // ROOM_H
