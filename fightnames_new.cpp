#include <bits/stdc++.h>
#define NEED_LEN 8

using namespace std;

//����汾��Ϣ
const class {
	public:
        char *name = "���־�����";
        char *version = "Alpha";
} APP;

struct Player{
	string name;
	vector<int> pro;
	//p��ǰ8λ�ֱ��Ӧ pro
	bool isdead, isboss;
	int killnum, killedby, score, zd;
    int team;
	Player() {
        team = -1;
		isdead = false;
		killnum = 0; //ɱ����
		score = 0; //����
		killedby = -1;
		isboss = false;
		zd = 1; //��Ϊboss,�����Ƿ�Ϊ����
	}
};

Player make_player(string &name, int team) {
    Player t;
    t.name = name;
    t.team = team;
    return t;
}

int name_num = 0, team_num = 1; //���������Ŷ���
map<string, int> name_mp; //���ֵ�ͼ����ѯ����ʱ��
vector<Player> player; //��������
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

void Load(string s = "") {
	system("CLS");
    cout << APP.name << "    Version:" << APP.version;
    if (s != "") cout << endl << s;
    cout << "\n-------------\n";
    return;
}

vector<string> split(string &s, char c = ' ') {
    //����Ƭ��Python�﷨���ơ�
    string s_tmp = "";
    vector<string> ret;
    bool no_str = true;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != c && s[i] != '\t' && s[i] != '\n') {
            s_tmp += s[i];
            no_str = false;
        } else {
            if(!no_str || c != ' ') {ret.push_back(s_tmp); s_tmp = ""; no_str = true;}
        }
    }
    if (!no_str || c != ' ') ret.push_back(s_tmp);
    return ret;
}

string getnames() {
    string name_t, MD5_seed = "";
    bool have_num = false;
    while (1) {
        getline(cin, name_t);
        MD5_seed += name_t;
        if (name_t == "end") {
            if (name_num < 2) {
                cout << "�����������㡣\n";
                continue;
            }
            if (have_num == false) team_num--;
            return MD5_seed;
        }
        if (name_t == "") {
            if (have_num) {
                team_num++;
                have_num = false;
            }            
            continue;
        }
        if (name_mp.count(name_t)) {
            cout << "�ظ�������\n";
            continue;
        }
        // ���ֺϷ�
        have_num = true;
        name_mp[name_t] = name_num;
        name_num++;
        player.push_back(make_player(name_t, team_num));
    }
}

int string_hash(string s) {
    unsigned int ret = 0;
    for (int i = 0; i <= s.size(); i++) {
        ret = ret * 233 + s[i];
    }
    return (int)ret;
}

void name_load() {

}

int main() {
    Load("by:Lhc_fl");

	printf(
	    "����:\n"
	    "�������֣��Ի��зָ��end��β��\n"
	    "�����ǿ�����������������ϵĲ�ͬ���֡�\n"
        "��������Էָ��Ŷ�\n"
	    "---------------------------------\n"
	);
    

    srand(string_hash(md5::getMD5(getnames())));

    name_load();
    system("pause");
    return 0;
}