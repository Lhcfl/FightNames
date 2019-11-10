#include<bits/stdc++.h>
#include<conio.h>

#define NEED_LEN 8

using namespace std;

//����汾��Ϣ
class{
	public:
		string name = "���־�����";
		string version = "Alpha";
} APP;

struct Player{
	string name;
	vector<int> p;
	//p��ǰ8λ�ֱ��Ӧ pro
	bool isdead, isboss;
	int killnum, killedby, score, zd;
	Player() {
		isdead = false;
		killnum = 0;
		score = 0; //����
		killedby = -1;
		isboss = false;
		zd = 1; //��Ϊboss,�����Ƿ�Ϊ����
	}
};

int name_num = 0; //������
map<string, Player> mp; //���ֵ�ͼ����ѯ����ʱ��
vector<string> names; //��������
string pro[NEED_LEN] = {"��", "��", "ħ", "��", "��", "��", "��", "��"};

//������copy����MD5������
namespace md5 {
	//strBaye�ĳ���
	unsigned int strlength;
	unsigned int atemp;
	unsigned int btemp;
	unsigned int ctemp;
	unsigned int dtemp;
	//����ti unsigned int(abs(sin(i+1))*(2pow32))
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
	//����λ����
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
	*��亯��
	*�����Ӧ����bits��448(mod512),�ֽھ���bytes��56��mode64)
	*��䷽ʽΪ�ȼ�һ��1,����λ����
	*������64λ��ԭ������
	*/
	unsigned int* add(string str)
	{
	    unsigned int num=((str.length()+8)/64)+1;//��512λ,64���ֽ�Ϊһ��
	    unsigned int *strByte=new unsigned int[num*16];    //64/4=16,������16������
	    strlength=num*16;
	    for (unsigned int i = 0; i < num*16; i++)
	        strByte[i]=0;
	    for (unsigned int i=0; i <str.length(); i++)
	    {
	        strByte[i>>2]|=(str[i])<<((i%4)*8);//һ�������洢�ĸ��ֽڣ�i>>2��ʾi/4 һ��unsigned int��Ӧ4���ֽڣ�����4���ַ���Ϣ
	    }
	    strByte[str.length()>>2]|=0x80<<(((str.length()%4))*8);//β�����1 һ��unsigned int����4���ַ���Ϣ,������128����
	    /*
	    *���ԭ���ȣ�����ָλ�ĳ��ȣ�����Ҫ��8��Ȼ����С�������Է��ڵ����ڶ���,���ﳤ��ֻ����32λ
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
	        b=((a>>i*8)%(1<<8))&0xff;   //������ÿ���ֽ�
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
	    atemp=0x67452301;    //��ʼ��
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
	//�����ֵ�MD5����һ������
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
	"����:\n"
	"�������֣��Կո��Tab���зָ��end��β��\n"
	"�����ǿ�����������������ϵĲ�ͬ���֡�\n"
	"---------------------------------\n"
	"boss������\n"
	"��\n"
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
					cout << "������������\n";
					continue;	
				} else break;
			}
			Player tmp_player;
			tmp_player.p = get_pro(tmp_name);
			mp[tmp_name] = tmp_player;
			names.push_back(tmp_name);
			name_num++;
			//boss �ж�
			if (tmp_name == "��") {
				boss_mode = true;
				mp[tmp_name].p[0] = 100;
				mp[tmp_name].p[6] = 800;
				mp[tmp_name].isboss = true;
			}
			if (tmp_name == "����Ϊ") {
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
	
	cout<<"3���ʼ...";
	
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
		//��ͨģʽ
		while (alive_number() > 1) {
			//a attack b
			int a, b;
			mak:
				a = rand() % name_num;
				b = rand() % name_num;
			if (a == b || mp[names[a]].isdead == true || mp[names[b]].isdead == true) goto mak;

			cout << names[a] << " ";
			int attack_id = rand() % 11;
			int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //��ʼ����
			int back = 0; //��ʼ����
			switch (attack_id) {
				case 0:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					cout << "������";
					break;
				case 1:
					cout << "�ػ���";
					damage *= 2;
					break;
				case 2:
					cout << "ʹ��������ʯ������";
					damage *= 4;
					back = damage / 2;
					break;
				case 3:
					cout << "ʹ�á���Ѫ��������";
					damage /= 2;
					back = -damage;
					break;
				case 4:
					cout << "ʹ�á�����һ����������";
					damage *= 2;
					break;
				case 5:
					cout << "ʹ�á����ͻ�̡�������";
					damage *= 1.5;
					break;
				
				default:
					cout << "������";
					break;
			}
			// attack's result
			bool missed = false;
			
			if (rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
				// missed
				missed = true;
				if (attack_id == 3) //��Ѫʧ��
					back = -back;
				cout << " " << names[b] << ", �� " << names[b] << " ���ǵض㿪��.\n";
			}else{
				cout << " " << names[b] << ", ʹ " << names[b] << " �ܵ��� " << damage << "���˺�.\n";
				mp[names[b]].p[0] -= damage;
				mp[names[a]].score += damage;
			}
			if (back != 0) {
				if (back > 0)
					cout << names[a] << " �ܵ��� " << back << " �㷴��.\n"; 
				else 
					cout << names[a] << " �ܵ��� " << -back << " ���Ѫ.\n"; 
				mp[names[a]].p[0] -= back;
				mp[names[b]].score += back;
			}
			if (!missed) cout << "����" << names[b] << " ���� " << mp[names[b]].p[0] << " ��HP��\n";
			if (back != 0) {
				cout << names[a] << " ���� " << mp[names[a]].p[0] << " ��HP��\n";
			}
			if (mp[names[a]].p[0] <= 0) {
				cout << "\t" << names[a] << " ����.\n";
				mp[names[a]].isdead = true;
				mp[names[a]].killedby = b;
				mp[names[b]].killnum++;
				if (first_blood == -1) {
					first_blood = b;
				}
			}
			if (mp[names[b]].p[0] <= 0) {
				cout << "\t" << names[b] << " ����.\n";
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
				//��a����boss, �վ�
				cout << names[a] << " ";
				int attack_id = rand() % 11;
				int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //��ʼ����
				int back = 0; //��ʼ����
				switch (attack_id) {
					case 0:
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
						cout << "������";
						break;
					case 1:
						cout << "�ػ���";
						damage *= 2;
						break;
					case 2:
						cout << "ʹ��������ʯ������";
						damage *= 4;
						back = damage / 2;
						break;
					case 3:
						cout << "ʹ�á���Ѫ��������";
						damage /= 2;
						back = -damage;
						break;
					case 4:
						cout << "ʹ�á�����һ����������";
						damage *= 2;
						break;
					case 5:
						cout << "ʹ�á����ͻ�̡�������";
						damage *= 1.5;
						break;
					
					default:
						cout << "������";
						break;
				}
				// attack's result
				if (names[b] == "����Ϊ" && rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
					cout << " ����Ϊ�� �� ����Ϊ ǿ���޸Ĵ���ѹ���ת����";
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
					if (attack_id == 3) //��Ѫʧ��
						back = -back;
					cout << " " << names[b] << ", �� " << names[b] << " ���ǵض㿪��.\n";
				}else{
					cout << " " << names[b] << ", ʹ " << names[b] << " �ܵ��� " << damage << "���˺�.\n";
					mp[names[b]].p[0] -= damage;
					mp[names[a]].score += damage;
				}
				if (back != 0) {
					if (back > 0)
						cout << names[a] << " �ܵ��� " << back << " �㷴��.\n"; 
					else 
						cout << names[a] << " �ܵ��� " << -back << " ���Ѫ.\n"; 
					mp[names[a]].p[0] -= back;
					mp[names[b]].score += back;
				}
				if (!missed) cout << "����" << names[b] << " ���� " << mp[names[b]].p[0] << " ��HP��\n";
				if (back != 0) {
					cout << names[a] << " ���� " << mp[names[a]].p[0] << " ��HP��\n";
				}
				if (mp[names[a]].p[0] <= 0) {
					cout << "\t" << names[a] << " ����.\n";
					mp[names[a]].isdead = true;
					mp[names[a]].killedby = b;
					mp[names[b]].killnum++;
					if (first_blood == -1) {
						first_blood = b;
					}
				}
				if (mp[names[b]].p[0] <= 0) {
					cout << "\t" << names[b] << " ����.\n";
					mp[names[b]].isdead = true;
					mp[names[b]].killedby = a;
					mp[names[a]].killnum++;
					if (first_blood == -1) {
						first_blood = a;
					}
				}
			} else {
				//a��boss
				int damage = mp[names[a]].p[1] * mp[names[a]].p[7] / mp[names[b]].p[3] / 4 + 20 ; //��ʼ����
				int back = 0; //��ʼ����
				int attack_id = rand() % 6;
				if (names[a] == "��") {
					cout << "�� ʹ�á���Ѫ�� ������ ";
					damage /= 2;
					back = -damage;
					attack_id = 3;
				}
				//if (names[a] == "����")

				// attack's result
				bool missed = false;
				if (rand() % 900 < mp[names[b]].p[6] - 0.1 * mp[names[a]].p[5]) {
					// missed
					missed = true;
					if (attack_id == 3) //��Ѫʧ��
						back = -back;
					cout << " " << names[b] << ", �� " << names[b] << " ���ǵض㿪��.\n";
				}else{
					cout << " " << names[b] << ", ʹ " << names[b] << " �ܵ��� " << damage << "���˺�.\n";
					mp[names[b]].p[0] -= damage;
					mp[names[a]].score += damage;
				}
				if (back != 0) {
					if (back > 0)
						cout << names[a] << " �ܵ��� " << back << " �㷴��.\n"; 
					else 
						cout << names[a] << " �ܵ��� " << -back << " ���Ѫ.\n"; 
					mp[names[a]].p[0] -= back;
					mp[names[b]].score += back;
				}
				if (!missed) cout << "����" << names[b] << " ���� " << mp[names[b]].p[0] << " ��HP��\n";
				if (back != 0) {
					cout << names[a] << " ���� " << mp[names[a]].p[0] << " ��HP��\n";
				}
				if (mp[names[a]].p[0] <= 0) {
					cout << "\t" << names[a] << " ����.\n";
					mp[names[a]].isdead = true;
					mp[names[a]].killedby = b;
					mp[names[b]].killnum++;
					
					if (first_blood == -1) {
						first_blood = b;
					}
				}
				if (mp[names[b]].p[0] <= 0) {
					cout << "\t" << names[b] << " ����.\n";
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

	cout << "\n-------------------------ս������-------------------------\n";
	if (first_alive() != -1) cout << "ʤ�ߣ�" << names[first_alive()] << endl;
	cout << "������: " << names[find_MVP()] << endl;
	cout << "��ɱ���: " << names[find_Killer()] << endl;
	cout << "��һ��Ѫ: " << names[first_blood] << endl;
	cout << "\n-------------------------��ϸ���-------------------------\n";
	for (int i = 0; i < names.size(); i++) {
		cout << names[i];
		cout << " ���: " <<  mp[names[i]].score;
		cout << " ��ɱ����" << mp[names[i]].killnum;
		if (mp[names[i]].killedby != -1) cout << " ����ɱ��" << names[mp[names[i]].killedby] << endl;
		else cout << endl;
		
	}
	system("pause");
}
