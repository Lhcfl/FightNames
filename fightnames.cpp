#include<bits/stdc++.h>
#include<conio.h>

#define NEED_LEN 8

using namespace std;

//程序版本信息
class{
	public:
		string name = "名字竞技场";
		string version = "Alpha";
} APP;

struct Player{
	string name;
	vector<int> p;
	//p的前8位分别对应 pro
	bool isdead, isboss;
	int killnum, killedby, score, zd;
	Player() {
		isdead = false;
		killnum = 0;
		score = 0; //积分
		killedby = -1;
		isboss = false;
		zd = 1; //若为boss,技能是否为主动
	}
};

int name_num = 0; //名字数
map<string, Player> mp; //名字地图，查询重名时用
vector<string> names; //名字数组
string pro[NEED_LEN] = {"命", "攻", "魔", "抗", "智", "速", "敏", "力"};

//下面是copy来的MD5生成器
namespace md5 {
	//strBaye的长度
	unsigned int strlength;
	unsigned int atemp;
	unsigned int btemp;
	unsigned int ctemp;
	unsigned int dtemp;
	//常量ti unsigned int(abs(sin(i+1))*(2pow32))
	const unsigned int k[]={
	        0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	        0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
	        0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
	        0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
	        0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	        0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
	        0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
	        0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
	   	    0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
	        0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
	        0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
	        0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
	        0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
	//向左位移数
	const unsigned int s[]={7,12,17,22,7,12,17,22,7,12,17,22,7,
	        12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	        4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
	        15,21,6,10,15,21,6,10,15,21,6,10,15,21};
	const char str16[]="0123456789abcdef";
	void mainLoop(unsigned int M[])
	{
	    unsigned int f,g;
	    unsigned int a=atemp;
	    unsigned int b=btemp;
	    unsigned int c=ctemp;
	    unsigned int d=dtemp;
	    for (unsigned int i = 0; i < 64; i++)
	    {
	        if(i<16){
	            f=(((b) & (c)) | ((~b) & (d)));
	            g=i;
	        }else if (i<32)
	        {
	            f=(((b) & (d)) | ((c) & (~d)));
	            g=(5*i+1)%16;
	        }else if(i<48){
	            f=((b) ^ (c) ^ (d));
	            g=(3*i+5)%16;
	        }else{
	            f=((c) ^ ((b) | (~d)));
	            g=(7*i)%16;
	        }
	        unsigned int tmp=d;
	        d=c;
	        c=b;
	        b=b+(((a+f+k[i]+M[g]) << (s[i])) | ((a+f+k[i]+M[g]) >> (32-(s[i]))));
	        a=tmp;
	    }
	    atemp=a+atemp;
	    btemp=b+btemp;
	    ctemp=c+ctemp;
	    dtemp=d+dtemp;
	}
	/*
	*填充函数
	*处理后应满足bits≡448(mod512),字节就是bytes≡56（mode64)
	*填充方式为先加一个1,其它位补零
	*最后加上64位的原来长度
	*/
	unsigned int* add(string str)
	{
	    unsigned int num=((str.length()+8)/64)+1;//以512位,64个字节为一组
	    unsigned int *strByte=new unsigned int[num*16];    //64/4=16,所以有16个整数
	    strlength=num*16;
	    for (unsigned int i = 0; i < num*16; i++)
	        strByte[i]=0;
	    for (unsigned int i=0; i <str.length(); i++)
	    {
	        strByte[i>>2]|=(str[i])<<((i%4)*8);//一个整数存储四个字节，i>>2表示i/4 一个unsigned int对应4个字节，保存4个字符信息
	    }
	    strByte[str.length()>>2]|=0x80<<(((str.length()%4))*8);//尾部添加1 一个unsigned int保存4个字符信息,所以用128左移
	    /*
	    *添加原长度，长度指位的长度，所以要乘8，然后是小端序，所以放在倒数第二个,这里长度只用了32位
	    */
	    strByte[num*16-2]=str.length()*8;
	    return strByte;
	}
	string changeHex(int a)
	{
	    int b;
	    string str1;
	    string str="";
	    for(int i=0;i<4;i++)
	    {
	        str1="";
	        b=((a>>i*8)%(1<<8))&0xff;   //逆序处理每个字节
        	for (int j = 0; j < 2; j++)
    	    {
	            str1.insert(0,1,str16[b%16]);
	            b=b/16;
	        }
	        str+=str1;
	    }
	    return str;
	}
	string getMD5(string source)
	{
	    atemp=0x67452301;    //初始化
	    btemp=0xefcdab89;
	    ctemp=0x98badcfe;
	    dtemp=0x10325476;
	    unsigned int *strByte=add(source);
	    for(unsigned int i=0;i<strlength/16;i++)
	    {
	        unsigned int num[16];
	        for(unsigned int j=0;j<16;j++)
	            num[j]=strByte[i*16+j];
	        mainLoop(num);
	    }
	    return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
	}
}

void Load(string s = ""){
	system("CLS");
    cout << APP.name << "    Version:" << APP.version;
    if (s != "") cout << endl << s;
    cout << "\n-------------\n";
    return;
}


int toint(string s) {
	int tmp;
	stringstream ss;
	ss << s;
	ss >> tmp;
	return tmp;
}

string tostr(int n) {
	string tmp;
	stringstream ss;
	ss << n;
	ss >> tmp;
	return tmp;
}

int toint(char c){
	if (c <= '9' && c >= '0') return c - '0';
	if (c <= 'z' && c >= 'a') return 25 - (c - 'a') * 4;
	if (c <= 'Z' && c >= 'A') return c - 'A';
	return 0;
}

vector<int> get_pro(string s){
	//用名字的MD5生成一个序列
	vector<int> answer;
	s = md5::getMD5(s);
	for (int i = 0; i < 8; i++) {
		int num = 0;
		num += 25 - toint(s[4 * i]);
		num += 25 - toint(s[4 * i + 1]);
		num += 25 - toint(s[4 * i + 2]);
		num += 25 - toint(s[4 * i + 3]);
		answer.push_back(num);
	}
	answer[0] *= 7;
	return answer;
}

int alive_number() {
	int count = 0;
	for (int i = 0; i < names.size(); i++) {
		if (!mp[names[i]].isdead) count++;
	}
	return count;
}

int alive_boss_number() {
	int count = 0;
	for (int i = 0; i < names.size(); i++) {
		if (!mp[names[i]].isdead && mp[names[i]].isboss) count++;
	}
	return count;
}

int first_alive(int n = -1) {
	//return the ID of the first one who is alive after n
	for (int i = n + 1; i < names.size(); i++) {
		if (!mp[names[i]].isdead) return i;
	}
	for (int i = 0; i < n; i++) {
		if (!mp[names[i]].isdead) return i;
	}
	return n;
}

int find_MVP() {
	int count = 0;
	int maxn = 0;
	for (int i = 0; i < names.size(); i++) {
		if (mp[names[i]].score >= maxn) {
			count = i;
			maxn = mp[names[i]].score;
		}
	}
	return count;
}

int find_Killer() {
	int count = 0;
	int maxn = 0;
	for (int i = 0; i < names.size(); i++) {
		if (mp[names[i]].killnum >= maxn) {
			count = i;
			maxn = mp[names[i]].killnum;
		}
	}
	return count;
}

int md5_rand(string seed) {
	string key = md5::getMD5(seed);
	int n = 0;
	for (int i = 0; i < key.length(); i++) {
		n += toint(key[i]);
	}
	return n;
}

int main() {
	bool boss_mode = false;
	Load("by:Lhc_fl");

	printf(
	"帮助:\n"
	"输入名字，以空格或Tab或换行分割，以end结尾。\n"
	"程序会强制让你输入两个以上的不同名字。\n"
	"---------------------------------\n"
	"boss名单：\n"
	"蚊\n"
	"---------------------------------\n"
	);
	
	while(1){
		string tmp_name = "";
		cin >> tmp_name;
		if (mp.count(tmp_name)) {
			continue; //the name does exist
		} else {
			if (tmp_name == "end") {
				if(name_num < 2) {
					cout << "名字数量不足\n";
					continue;	
				} else break;
			}
			Player tmp_player;
			tmp_player.p = get_pro(tmp_name);
			mp[tmp_name] = tmp_player;
			names.push_back(tmp_name);
			name_num++;
			//boss 判断
			if (tmp_name == "蚊") {
				boss_mode = true;
				mp[tmp_name].p[0] = 100;
				mp[tmp_name].p[6] = 800;
				mp[tmp_name].isboss = true;
			}
			if (tmp_name == "梁今为") {
				boss_mode = true;
				mp[tmp_name].p[6] = 700;
				mp[tmp_name].isboss = true;
			}
		}
	}
	
	sort(names.begin(),names.end());
	
	//show names' property
	Load();

	for (int i = 0; i < names.size(); i++) {
		cout << names[i] << '\n';
		for (int j = 0; j < NEED_LEN; j++) {
			cout << "\t" << pro[j] << ":" << mp[names[i]].p[j];
		}
		cout << endl << endl;
		_sleep(500);
	}
	
	cout<<"3秒后开始...";
	
	for (int i = 3; i > 0; i--) {
		cout << i;
		_sleep(1000);
		cout << "\b \b";
	}
	
	for (int i = 1; i < 13; i++) {
		cout << "\b \b";
	}
	
	//start

	//set rand seed
	string MD5_seed;
	for (int i = 0; i < names.size(); i++) {
		MD5_seed += names[i];
	}
	srand(md5_rand(names[0]));
	
	int first_blood = -1;

	if (boss_mode == false) {
		//普通模式
		while (alive_number() > 1) {
			//a attack b
			int a, b;
			mak:
				a = rand() % name_num;
				b = rand() % name_num;
			if (a == b || mp[names[a]].isdead == true || mp[names[b]].isdead == true) goto mak;

			cout << names[a] << " ";
			int attack_id = rand() % 11;
			int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //初始攻击
			int back = 0; //初始反噬
			switch (attack_id) {
				case 0:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					cout << "攻击了";
					break;
				case 1:
					cout << "重击了";
					damage *= 2;
					break;
				case 2:
					cout << "使用力量宝石攻击了";
					damage *= 4;
					back = damage / 2;
					break;
				case 3:
					cout << "使用“嗜血”攻击了";
					damage /= 2;
					back = -damage;
					break;
				case 4:
					cout << "使用“会心一击”攻击了";
					damage *= 2;
					break;
				case 5:
					cout << "使用“大地突刺”攻击了";
					damage *= 1.5;
					break;
				
				default:
					cout << "攻击了";
					break;
			}
			// attack's result
			bool missed = false;
			
			if (rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
				// missed
				missed = true;
				if (attack_id == 3) //嗜血失败
					back = -back;
				cout << " " << names[b] << ", 但 " << names[b] << " 机智地躲开了.\n";
			}else{
				cout << " " << names[b] << ", 使 " << names[b] << " 受到了 " << damage << "点伤害.\n";
				mp[names[b]].p[0] -= damage;
				mp[names[a]].score += damage;
			}
			if (back != 0) {
				if (back > 0)
					cout << names[a] << " 受到了 " << back << " 点反噬.\n"; 
				else 
					cout << names[a] << " 受到了 " << -back << " 点加血.\n"; 
				mp[names[a]].p[0] -= back;
				mp[names[b]].score += back;
			}
			if (!missed) cout << "现在" << names[b] << " 还有 " << mp[names[b]].p[0] << " 点HP。\n";
			if (back != 0) {
				cout << names[a] << " 还有 " << mp[names[a]].p[0] << " 点HP。\n";
			}
			if (mp[names[a]].p[0] <= 0) {
				cout << "\t" << names[a] << " 死了.\n";
				mp[names[a]].isdead = true;
				mp[names[a]].killedby = b;
				mp[names[b]].killnum++;
				if (first_blood == -1) {
					first_blood = b;
				}
			}
			if (mp[names[b]].p[0] <= 0) {
				cout << "\t" << names[b] << " 死了.\n";
				mp[names[b]].isdead = true;
				mp[names[b]].killedby = a;
				mp[names[a]].killnum++;
				if (first_blood == -1) {
					first_blood = a;
				}
			}
			cout << "\n\n";
			_sleep(500);
		}
	} else {
		while (alive_boss_number() > 0 && alive_number() > 1) {
			//a attack b
			int a, b;
			mak2:
				a = rand() % name_num;
				b = rand() % name_num;
			if (a == b || mp[names[a]].isdead == true || mp[names[b]].isdead == true || (mp[names[b]].isboss == false && mp[names[a]].isboss == false) ) goto mak2;
			
			if (mp[names[a]].isboss == false || mp[names[a]].zd == false) {
				//若a不是boss, 照旧
				cout << names[a] << " ";
				int attack_id = rand() % 11;
				int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //初始攻击
				int back = 0; //初始反噬
				switch (attack_id) {
					case 0:
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
						cout << "攻击了";
						break;
					case 1:
						cout << "重击了";
						damage *= 2;
						break;
					case 2:
						cout << "使用力量宝石攻击了";
						damage *= 4;
						back = damage / 2;
						break;
					case 3:
						cout << "使用“嗜血”攻击了";
						damage /= 2;
						back = -damage;
						break;
					case 4:
						cout << "使用“会心一击”攻击了";
						damage *= 2;
						break;
					case 5:
						cout << "使用“大地突刺”攻击了";
						damage *= 1.5;
						break;
					
					default:
						cout << "攻击了";
						break;
				}
				// attack's result
				if (names[b] == "梁今为" && rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
					cout << " 梁今为， 但 梁今为 强行修改代码把攻击转给了";
					int tmp = b;
					while (b == tmp || mp[names[b]].isdead == true) {
						b = rand() % name_num;
					} 
					mp[names[tmp]].score += damage;
				}
				bool missed = false;
				
				if (rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
					// missed
					missed = true;
					if (attack_id == 3) //嗜血失败
						back = -back;
					cout << " " << names[b] << ", 但 " << names[b] << " 机智地躲开了.\n";
				}else{
					cout << " " << names[b] << ", 使 " << names[b] << " 受到了 " << damage << "点伤害.\n";
					mp[names[b]].p[0] -= damage;
					mp[names[a]].score += damage;
				}
				if (back != 0) {
					if (back > 0)
						cout << names[a] << " 受到了 " << back << " 点反噬.\n"; 
					else 
						cout << names[a] << " 受到了 " << -back << " 点加血.\n"; 
					mp[names[a]].p[0] -= back;
					mp[names[b]].score += back;
				}
				if (!missed) cout << "现在" << names[b] << " 还有 " << mp[names[b]].p[0] << " 点HP。\n";
				if (back != 0) {
					cout << names[a] << " 还有 " << mp[names[a]].p[0] << " 点HP。\n";
				}
				if (mp[names[a]].p[0] <= 0) {
					cout << "\t" << names[a] << " 死了.\n";
					mp[names[a]].isdead = true;
					mp[names[a]].killedby = b;
					mp[names[b]].killnum++;
					if (first_blood == -1) {
						first_blood = b;
					}
				}
				if (mp[names[b]].p[0] <= 0) {
					cout << "\t" << names[b] << " 死了.\n";
					mp[names[b]].isdead = true;
					mp[names[b]].killedby = a;
					mp[names[a]].killnum++;
					if (first_blood == -1) {
						first_blood = a;
					}
				}
			} else {
				//a是boss
				int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //初始攻击
				int back = 0; //初始反噬
				int attack_id = rand() % 6;
				if (names[a] == "蚊") {
					cout << "蚊 使用“嗜血” 攻击了 ";
					damage /= 2;
					back = -damage;
					attack_id = 3;
				}
				//if (names[a] == "柯南")

				// attack's result
				bool missed = false;
				if (rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
					// missed
					missed = true;
					if (attack_id == 3) //嗜血失败
						back = -back;
					cout << " " << names[b] << ", 但 " << names[b] << " 机智地躲开了.\n";
				}else{
					cout << " " << names[b] << ", 使 " << names[b] << " 受到了 " << damage << "点伤害.\n";
					mp[names[b]].p[0] -= damage;
					mp[names[a]].score += damage;
				}
				if (back != 0) {
					if (back > 0)
						cout << names[a] << " 受到了 " << back << " 点反噬.\n"; 
					else 
						cout << names[a] << " 受到了 " << -back << " 点加血.\n"; 
					mp[names[a]].p[0] -= back;
					mp[names[b]].score += back;
				}
				if (!missed) cout << "现在" << names[b] << " 还有 " << mp[names[b]].p[0] << " 点HP。\n";
				if (back != 0) {
					cout << names[a] << " 还有 " << mp[names[a]].p[0] << " 点HP。\n";
				}
				if (mp[names[a]].p[0] <= 0) {
					cout << "\t" << names[a] << " 死了.\n";
					mp[names[a]].isdead = true;
					mp[names[a]].killedby = b;
					mp[names[b]].killnum++;
					
					if (first_blood == -1) {
						first_blood = b;
					}
				}
				if (mp[names[b]].p[0] <= 0) {
					cout << "\t" << names[b] << " 死了.\n";
					mp[names[b]].isdead = true;
					mp[names[b]].killedby = a;
					mp[names[a]].killnum++;
					if (first_blood == -1) {
						first_blood = a;
					}
				}
			}
			cout << "\n\n";
			_sleep(250);
		}
	}

	cout << "\n-------------------------战斗结束-------------------------\n";
	if (first_alive() != -1) cout << "胜者：" << names[first_alive()] << endl;
	cout << "最大输出: " << names[find_MVP()] << endl;
	cout << "击杀最多: " << names[find_Killer()] << endl;
	cout << "第一滴血: " << names[first_blood] << endl;
	cout << "\n-------------------------详细情况-------------------------\n";
	for (int i = 0; i < names.size(); i++) {
		cout << names[i];
		cout << " 输出: " <<  mp[names[i]].score;
		cout << " 击杀数：" << mp[names[i]].killnum;
		if (mp[names[i]].killedby != -1) cout << " 被击杀：" << names[mp[names[i]].killedby] << endl;
		else cout << endl;
		
	}
	system("pause");
}
