#ifndef GOODS_H
#define GOODS_H

#include <string>
using namespace std;
class Goods
{
private:
	string name;            //名称
	string description;     //描述
	int add_attack;         //攻击力
	int add_defence;        //防御力
	int add_HP;             //体力
	int price;              //价钱
	int number;             //序号
public:
	void assignment(string newname, string newdescription, int newadd_attack, int newadd_defence, int newadd_HP, int newprice, int newnumber);//赋值
	void display();//显示数据
	string getname();
	string getdescription();
	int getadd_attack();
	int getadd_defence();
	int getadd_HP();
	int getprice();
	int getnumber();
};
/*物品*/
void Goods::assignment(string newname, string newdescription, int newadd_attack, int newadd_defence, int newadd_HP, int newprice, int newnumber)
{
	name = newname;
	description = newdescription;
	add_attack = newadd_attack;
	add_defence = newadd_defence;
	add_HP = newadd_HP;
	price = newprice;
	number = newnumber;
}
/*显示物品数据*/
void Goods::display()
{
	cout << "名称：" << name << endl;
	cout << "简介：" << description << endl;
	if (add_attack>0)
		cout << "攻击：" << add_attack << endl;
	if (add_defence>0)
		cout << "防御：" << add_defence << endl;
	if (add_HP>0)
		cout << "恢复体力：" << add_HP << endl;
	cout << "价钱：" << price << "文" << endl;
}
string Goods::getname()
{
	return name;
}
string Goods::getdescription()
{
	return description;
}
int Goods::getadd_attack()
{
	return add_attack;
}
int Goods::getadd_defence()
{
	return add_defence;
}
int Goods::getadd_HP()
{
	return add_HP;
}
int Goods::getprice()
{
	return price;
}
int Goods::getnumber()
{
	return number;
}

void initialize(Goods goods[])//进行赋值，确定基础数据
{
	goods[0].assignment("布甲", "虽然是布甲，但还是有些防御力的", 0, 2, 0, 10, 0);
	goods[1].assignment("铁甲", "制作精良的铠甲，有着不俗的防御", 0, 5, 0, 20, 1);
	goods[2].assignment("圣甲", "传承已久的圣物，拥有不可思议的力量", 0, 10, 0, 80, 2);
	goods[3].assignment("木剑", "平平无奇的铁剑，看不出有什么特殊", 5, 0, 0, 10, 3);
	goods[4].assignment("铁剑", "采用寒铁锻造而成，十分锋利", 7, 0, 0, 20, 4);
	goods[5].assignment("圣剑", "传承已久的圣物，拥有不可思议的力量", 12, 0, 0, 80, 5);
	goods[6].assignment("活血散", "简单的药物，具有不错的效果", 0, 0, 5, 6, 6);
	goods[7].assignment("金疮药", "数代医师的智慧结晶，疗伤宝药", 0, 0, 10, 12, 7);
	goods[8].assignment("还阳丹", "由上古奇方炼制而成，疗伤圣药", 0, 0, 20, 24, 8);
	goods[9].assignment("法杖", "传言天帝赐福之物，神秘莫测", 20, 0, 0, 200, 9);
}


#endif // GOODS_H
