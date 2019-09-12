#include "head_func.h"
/*************************���ݽṹ����********************************/
//cpoint����
cpoint operator -(cpoint a, cpoint b){
	cpoint m;
	m.x=a.x-b.x;
	m.y=a.y-b.y;
	m.z=a.z-b.z;
	return m;
}
//cpointģ��
double modCpoint(cpoint v){
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}
/*************************ȫ�ֺ���********************************/
//���������atan���� ��������atan ��������atan+pi
double arctg(double v){
	double ang;
	if(v>=0) ang=atan(v);
	else if(v<0) ang=atan(v)+Pi;
	return ang;
}
//��stringת��Ϊstringstream
stringstream str2ss(string s){
	stringstream sstr;
	sstr.str(""); sstr.clear(); sstr.str(s);
	return sstr;
}
//����һ��cpoint��λ��id�ַ���
string cpoint_id(cpoint c){
	string vert_id, mid_id;
	stringstream sstemp;
	sstemp.str(""); sstemp.clear(); sstemp<<setprecision(PRECISION)<<c.x;
	sstemp>>vert_id;
	sstemp.str(""); sstemp.clear(); sstemp<<setprecision(PRECISION)<<c.y;
	sstemp>>mid_id;
	vert_id = vert_id + " " + mid_id;
	sstemp.str(""); sstemp.clear(); sstemp<<setprecision(PRECISION)<<c.z;
	sstemp>>mid_id;
	vert_id = vert_id + " " + mid_id;
	return vert_id;
}
//���Դ������ļ� ����ɹ��򷵻�0�������Ϣ ���򷵻�1
int open_infile(ifstream &infile,char* filename){
	infile.open(filename);
	if (!infile){
		cerr << BOLDRED << "error ==> " << RESET << "file not found: " << filename << endl;
		return -1;
	}
	return 0;
}
//���Դ�����ļ� ����ɹ��򷵻�0�������Ϣ ���򷵻�1
int open_outfile(ofstream &outfile,char* filename){
	outfile.open(filename);
	if (!outfile){
		cerr << BOLDRED << "error ==> " << RESET << "fail to create the file: " << filename << endl;
		return -1;
	}
	return 0;
}

//���������ֵ �����������ݲ�ֵ ����ƽ������
/*������ʾ��ͼ*/
// y
// |
// |
// 3------------2
// |            |
// |            |
// |            |
// 0------------1--->x
// ���½�����x0 y0
// ����ߴ�dx dy
// ��ֵ������x y
// �ĸ��ǵ�ֵ
double grid_interpolate(double x0,double y0,double dx,double dy,double x,double y,
					double d0,double d1,double d2,double d3)
{
	double res = 0;
	double total_dist = 0;
	double dist[4] = {0,0,0,0};
	double val[4];
	val[0] = d0; val[1] = d1; val[2] = d2; val[3] = d3;
	dist[0] = 1.0/(1e-30+(x-x0)*(x-x0)+(y-y0)*(y-y0));
	dist[1] = 1.0/(1e-30+(x-dx-x0)*(x-dx-x0)+(y-y0)*(y-y0));
	dist[2] = 1.0/(1e-30+(x-dx-x0)*(x-dx-x0)+(y-dy-y0)*(y-dy-y0));
	dist[3] = 1.0/(1e-30+(x-x0)*(x-x0)+(y-dy-y0)*(y-dy-y0));
	for (int i = 0; i < 4; i++){
		total_dist += dist[i];
	}
	for (int i = 0; i < 4; i++){
		res += val[i]*dist[i]/total_dist;
	}
	return res;
}