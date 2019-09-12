#include "gm3d.h"

int GM3D::BuildRegularGrid(char* space_para){
	cpoint temp_cp;
	cube temp_cu;
	string temp_str;
	string temp_id_str;
	double x,xs,dx,xe,xmin,xmax;
	double y,ys,dy,ye,ymin,ymax;
	double z,zs,dz,ze,zmin,zmax;
	double sign[8][3] = {{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},
						{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5}};

	_str2pointMap map_str_point;
	_str2pointMap::iterator imsp;

	ifstream infile;
	infile.open(space_para);
	if (!infile) {
		if (9 != sscanf(space_para,"%lf/%lf/%lf/%lf/%lf/%lf/%lf/%lf/%lf",
					&xs,&dx,&xe,&ys,&dy,&ye,&zs,&dz,&ze)){
			return -1;
		}
	}
	else {
		getline(infile,temp_str);
		if (3 != sscanf(temp_str.c_str(),"%lf %lf %lf",&xs,&dx,&xe)) return -1;

		getline(infile,temp_str);
		if (3 != sscanf(temp_str.c_str(),"%lf %lf %lf",&ys,&dy,&ye)) return -1;

		getline(infile,temp_str);
		if (3 != sscanf(temp_str.c_str(),"%lf %lf %lf",&zs,&dz,&ze)) return -1;

		infile.close();
	}

	xmin = MIN(xs,xe); xmax = MAX(xs,xe);
	ymin = MIN(ys,ye); ymax = MAX(ys,ye);
	zmin = MIN(zs,ze); zmax = MAX(zs,ze);

	temp_cu.dx = fabs(dx); temp_cu.dy = fabs(dy); temp_cu.dz = fabs(dz);
	y = ys;
	while(y >= ymin && y <= ymax){
		x = xs;
		while(x >= xmin && x <= xmax){
			z = zs;
			while(z >= zmin && z <= zmax){
				//���denMod
				temp_cu.cen.id = model_cube_.size();
				temp_cu.cen.x = x; temp_cu.cen.y = y; temp_cu.cen.z = z;
				//���mshVert
				for (int i = 0; i < 8; i++){
					temp_cp.id = model_vert_.size(); //���msh�Ķ�������ΪmshVert�Ĵ�С
					temp_cp.x = temp_cu.cen.x - sign[i][0]*temp_cu.dx; //���µ׽�
					temp_cp.y = temp_cu.cen.y - sign[i][1]*temp_cu.dy;
					temp_cp.z = temp_cu.cen.z - sign[i][2]*temp_cu.dz;
					temp_id_str = cpoint_id(temp_cp);
					imsp = map_str_point.find(temp_id_str);
					//����map_vert�鵽��ǰ�����Ƿ����,������Ҫע�⣬��������Ѿ�������ֻ��Ҫ������������Ϊ�Ѵ��ڶ���������������Ӷ������
					if(imsp!=map_str_point.end()){
						temp_cu.ids[i] = imsp->second.id;
					}
					//��Ϊ�µĶ����������ӵ�����ӳ���һ��������
					else{
						temp_cu.ids[i] = temp_cp.id;//�µĶ����������ڶ��㼯������
						model_vert_.push_back(temp_cp);//���²����Ķ��㱣�浽����������
						map_str_point[temp_id_str] = temp_cp;//���²����Ķ��㱣�浽����λ��ӳ����
					}
				}
				model_cube_.push_back(temp_cu);
				z += dz;
			}
			x += dx;
		}
		y += dy;
	}

	if (model_cube_.empty()){
		return -1;
	}
	else{
		vert_num_ = model_vert_.size();
		model_num_ = model_cube_.size();
		model_block_val_.resize(model_num_,BDL_MAX); //��ʼ��ģ�Ϳ���ֵΪBDL_MAX
	}
	return 0;
}