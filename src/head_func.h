#ifndef _HEAD_FUNC_H
#define _HEAD_FUNC_H
#include "iostream"
#include "fstream"
#include "sstream"
#include "string.h"
#include "cmath"
#include "iomanip"
#include "stdio.h"
#include "stdlib.h"
//#include "unistd.h"
#include "vector"
#include "map"
#include "algorithm"
#include "ctime"
#include "omp.h"
#include "random"

using namespace std;

//��ѧ����
#define BDL_MAX 1e+30 ///< ������������ֵ
#define BDL_MIN -1e+30 ///< �����������Сֵ
#define PRECISION 16 ///< ����С�������Ҫʹ�õ�λ��
#define ZERO 1e-16 ///< ������ֵ

//������
#define Pi (4.0*atan(1.0)) ///< Բ����
#define G0 6.67408e-3 ///< ��������������ע���������������Ӧ����e-11�����ǵ���λת����ȡά�ȵ�λΪm���ܶȵ�λΪg/cm^3������G0��������λ��ΪmGal
#define T0 5.0e+4 ///< �شų�ƽ��ǿ��
//�꺯��
#define MAX(a,b) (a>b?a:b) ///< ����a��b�����ֵ
#define MIN(a,b) (a<b?a:b) ///< ����a��b����Сֵ
#define SetToBox(a,b,in) (MAX(a,MIN(b,in))) ///< ����a��b֮���һ��ֵ����in��a��b֮����ֱ�ӷ��أ����򷵻ؽϽ��ı߽�ֵ
//�ն���ʾ���Ʒ�
#define BOLDRED "\033[1m\033[31m" ///< ���ú����ַ�����Ϊ��ɫ�Ӵ�
#define BOLDGREEN "\033[1m\033[32m" ///< ���ú����ַ�����Ϊ��ɫ�Ӵ�
#define BOLDYELLOW "\033[1m\033[33m" ///< ���ú����ַ�����Ϊ��ɫ�Ӵ�
#define BOLDBLUE "\033[1m\033[34m" ///< ���ú����ַ�����Ϊ��ɫ�Ӵ�
#define UNDERLINE "\033[1m\033[4m" ///< ���ú����ַ�Ϊ����»���
#define RESET "\033[0m" ///< �����ַ�����
#define MOVEUP(x) printf("\033[%dA", (x)) ///< ���������Ųx��
#define MOVEDOWN(x) printf("\033[%dB", (x)) ///< �����������x��
#define MOVELEFT(x) printf("\033[%dD", (x)) ///< �����������x�ַ�
#define MOVERIGHT(x) printf("\033[%dC", (x)) ///< �����������x�ַ�
#define MOVETO(y,x) printf("\033[%d;%dH", (y), (x)) ///< ����������ȶ�y�ַ�,����Ų��x�ַ�
#define CLEARLINE "\033[K" ///< �������
#define CLEARALL "\033[2J" ///< ����ն�����
//���ݽṹ
typedef vector<int> _1iArray; ///< ����һά����
typedef vector<double> _1dArray; ///< ˫���ȸ���һά����
typedef vector<string> _1sArray; ///< �ַ���һά����
typedef vector<vector<int> > _2iArray; ///< ���θ����ά����
typedef vector<vector<double> > _2dArray; ///< ˫���ȸ����ά����
typedef map<int,int> _int2intMap; ///< ���͵����ε�ӳ��
//ģ�Ϳ������
struct modelist{
	char mod_type[1024];
	char val_type[1024];
	char mod_para[1024];
	double mod_value;
};
typedef vector<modelist> modelistArray;
//ֱ������ϵ��
struct cpoint{
	int id = -1;
	double x = BDL_MAX; double y = BDL_MAX; double z = BDL_MAX;
};
typedef vector<cpoint> cpointArray;
typedef map<string,cpoint> _str2pointMap;
//�۲��
struct obspoint : public cpoint{
	double val = BDL_MAX; double dev = BDL_MAX;
};
typedef vector<obspoint> obspointArray;
//����
struct cube{
	cpoint cen;
	int ids[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
	double dx = BDL_MAX; double dy = BDL_MAX; double dz = BDL_MAX;
};
typedef vector<cube> cubeArray;
/*************************���ݽṹ����********************************/
cpoint operator -(cpoint,cpoint); //ʸ������
double modCpoint(cpoint); //ʸ��ģ
/*************************ȫ�ֺ���********************************/
double arctg(double); //���������atan���� ��������atan ��������atan+pi
stringstream str2ss(string); //��stringת��Ϊstringstream
string cpoint_id(cpoint); //����һ��cpoint��λ��id
int open_infile(ifstream&,char*); //���Դ������ļ� ����ɹ��򷵻�0�������Ϣ ���򷵻�1
int open_outfile(ofstream&,char*); //���Դ�����ļ� ����ɹ��򷵻�0�������Ϣ ���򷵻�1
double grid_interpolate(double,double,double,double,double,double,double,double,double,double); //���������ֵ
#endif