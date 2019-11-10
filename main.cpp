#include<bits/stdc++.h>
#include<conio.h>

#define NEED_LEN 8

using namespace std;

//程序版本信息
class{
	public:
		string name="名字竞技场";
		string version="Beta";
}APP;

struct Player{
	string name;
	vector<int> p;
	//p的前8位分别对应 pro
	bool isdead=0;
	int score=0;
};

int name_num=0;//名字数
map<string,Player> mp; //名字地图，查询重名时用
vector<string> names; //名字数组
string pro[NEED_LEN]={"命","攻","魔","抗","智","速","敏","力"};

//下面是copy来的MD5生成器
namespace md5{
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

int toint(char c){
	if(c<='9' && c>='0')return c-'0';
	if(c<='z' && c>='a')return 25-(c-'a')*4;
	if(c<='Z' && c>='A')return c-'A';
	return 0;
}

vector<int> magic(string s){
	//用名字的MD5生成一个序列
	vector<int> answer;
	s=md5::getMD5(s);
	for(int i=0;i<8;i++){
		int num=0;
		num+=25-toint(s[4*i]);
		num+=25-toint(s[4*i+1]);
		num+=25-toint(s[4*i+2]);
		num+=25-toint(s[4*i+3]);
		answer.push_back(num);
	}
	answer[0]*=3;
	return answer;
}
int magic(vector<int> a,vector<int> b,int maxn=name_num){
	string s="";
	int n=min(a.size(),b.size());
	for(int i=0;i<n;i++){
		s+=(char)((abs(a[i])+abs(b[i]))%(127-32)+32);
	}
	s=md5::getMD5(s);
	int sum=0;
	for(int i=0;i<s.size();i++){
		sum+=s[i];
	}
	return (sum * abs((int)s[1]) +1) % maxn;
}

bool all_dead(){
	int a=-1;
	for(int i=0;i<names.size();i++){
		a+=!mp[names[i]].isdead;
	}
	return !a;
}
int first_live(int s=0,int dont=-1){
	for(int i=s;i<names.size();i++){
		if(!mp[names[i]].isdead && i!=dont)return i;
	}
	for(int i=0;i<s;i++){
		if(!mp[names[i]].isdead && i!=dont)return i;
	}
	return 0;
}
int fight_with(int n){
	int to=magic(mp[names[first_live(n+1)]].p,mp[names[n]].p);
	to=first_live(to,n);
	return to;
}
void fight(int a,int b){
	cout<<names[a];
	int id=magic(mp[names[(a+1)%name_num]].p,magic(names[a]+names[b]),16);
	cout<<"使用id为"<<id<<"的攻击攻击了";
	cout<<names[b]<<", \n\t";
	cout<<names[b]<<"受到了";
	int d=magic(
		magic(names[b]+names[a]),
		magic(names[a]+names[b]),
		abs(mp[names[b]].p[0]-mp[names[b]].p[3]+(mp[names[a]].p[1]+mp[names[a]].p[7])/2)
	)+1;
	cout<<d<<"点伤害\n";
	mp[names[b]].p[0]-=d;
	mp[names[a]].score+=d/2;
	cout<<"现在"<<names[b]<<"还有"<<mp[names[b]].p[0]<<"点HP\n";
	if(mp[names[b]].p[0]<=0){
		mp[names[b]].isdead=1;
		cout<<names[b]<<"死了.";
	}
	cout<<"\n\n";
}

void Load(string s=""){
	system("CLS");
    cout<<APP.name+"    Version:"<<APP.version;
    if(s!="")cout<<endl<<s;
    cout<<"\n-------------\n";
}

int main(){
	Load("by:Lhc_fl");

	printf(
	"帮助:\n"
	"输入名字，以空格或Tab或换行分割，以end结尾。\n"
	"程序会强制让你输入两个以上的不同名字。\n"
	);

	while(1){
		string tmp_name="";
		cin>>tmp_name;
		if(mp.count(tmp_name)){
			continue;
		}else{
			if(tmp_name=="end"){
				if(name_num<2)continue;
				else break;
			}
			Player tmp_player;
			tmp_player.name=tmp_name;
			tmp_player.p=magic(tmp_name);
			mp.insert(pair<string,Player>(tmp_name,tmp_player));
			names.push_back(tmp_name);
			name_num++;
		}
	}


	sort(names.begin(),names.end());

	Load("展示");

	for(int i=0;i<names.size();i++){
		cout<<names[i]<<'\n';
		for(int j=0;j<NEED_LEN;j++){
			cout<<"\t"<<pro[j]<<":"<<mp[names[i]].p[j];
		}
		cout<<endl<<endl;
		_sleep(500);
	}
	cout<<"按任意键开始...";
	getch();

	Load("战斗");
	int i=first_live();
	while(!all_dead()){
		if(all_dead()){
			break;
		}
		fight(i,fight_with(i));
		i=first_live(magic(mp[names[i]].p,mp[names[(i+1)%name_num]].p));
		_sleep(700);
	}
	cout<<"\n\n结果公示：\n---------------\n";
	cout<<"最后赢家:"<<names[first_live()];
	cout<<"\n---------------\n";
	for(int i=0;i<name_num;i++){;
		cout<<names[i]<<"\t积分"<<mp[names[i]].score<<endl;
	}
	return 0;
}