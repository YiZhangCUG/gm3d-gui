#include "gm3d.h"

int GM3D::ReadModel(char* filename,char* input_forward_model_name){
	int temp_int,ele_type,attri_num,temp_attri,temp_id;
	double temp_val;
	_1dArray temp_model;
	cpoint temp_vert;
	cube temp_cu;
	string temp_str;
	stringstream temp_ss;

	ifstream mshin;
	if (open_infile(mshin,filename)) return -1; //��鲢��ģ���ļ�
	while(getline(mshin,temp_str)){
		//����ģ�Ϳռ䶥�㼯 msh�ļ��汾Ϊ2.2
		if (temp_str == "$Nodes"){
			getline(mshin,temp_str);
			temp_ss = str2ss(temp_str);
			temp_ss >> vert_num_; //��һ����Ϊ����ĸ���
			model_vert_.resize(vert_num_); //���ٿռ�
			for (int i = 0; i < vert_num_; i++){
				getline(mshin,temp_str);
				temp_ss = str2ss(temp_str);
				temp_ss >> temp_vert.id >> temp_vert.x >> temp_vert.y >> temp_vert.z;
				model_vert_[i] = temp_vert;
			}
		}
		//����ģ�Ϳռ䵥Ԫ��
		else if (temp_str == "$Elements"){
			getline(mshin,temp_str);
			temp_ss = str2ss(temp_str);
			temp_ss >> model_num_; //��һ����Ϊ��Ԫ�صĸ��� �������������͵�Ԫ�� ���������� �ı��� �����
			model_cube_.resize(model_num_);
			for (int i = 0; i < model_num_; i++){
				getline(mshin,temp_str);
				temp_ss = str2ss(temp_str);
				temp_ss >> temp_cu.cen.id >> ele_type;
				//ֻ�������
				if (ele_type == 5){
					temp_ss >> attri_num; //����ģ�͵�Ԫ�ļ����������������Ϣ �Ժ���ܻ�����
					for (int a = 0; a < attri_num; a++)
						temp_ss >> temp_attri;
					for (int a = 0; a < 8; a++)
						temp_ss >> temp_cu.ids[a];
					model_cube_[i] = temp_cu;
				}
			}
		}
		else continue; //����ʶ��ĵ�Ԫ����������
	}
	mshin.close();

	//�ڶ��ζ���ģ���ļ� ��ʼ��ģ�͵�Ԫ����
	if (open_infile(mshin,filename)) return -1; //��鲢��ģ���ļ�
	while(getline(mshin,temp_str)){
		//����ģ�͵�Ԫ���� ע����Ϊmsh�ļ���$ElementData��δע������Ԫ������
		//���Կ��ܻὫ����Ԫ�����͵�����ֵҲ���� ����Ϊ����pyIdMap�в�δע�� ��������ֵ��ȫΪ0 �ں���ʹ��ʱ������Ҫͨ�����Ʊ��
		if (temp_str == "$ElementData"){
			temp_model.resize(model_num_,0.0); //��ʼ��temp_model Ϊ����ģ�͵�Ԫ������׼��
			for (int i = 0; i < 2; i++) //�ȶ���Ԫ�ؿ������ ��ӵ�����
				getline(mshin,temp_str);
			input_model_names_.push_back(temp_str);
			for (int i = 0; i < 6; i++) //����Ԫ������ǰ���ֵ ���һ��Ϊ��ǰԪ�ؿ�ĸ���
				getline(mshin,temp_str);
			temp_ss = str2ss(temp_str);
			temp_ss >> temp_int;
			for (int i = 0; i < temp_int; i++){
				getline(mshin,temp_str);
				temp_ss = str2ss(temp_str);
				temp_ss >> temp_id >> temp_val; //���뵥Ԫ������������ֵ
				temp_model[temp_id] = temp_val;
			}
			input_models_.push_back(temp_model);
			temp_model.clear();
		}
		else continue; //����ʶ��ĵ�Ԫ����������
	}
	mshin.close();

	//����ӳ��
	temp_model.clear();
	vector <double>().swap(temp_model);

	//��ʼ������
	forward_model_.resize(model_num_,0.0);
	//ƥ����������
	char forward_model_name[1024] = "\"";
	strcat(forward_model_name,input_forward_model_name);
	strcat(forward_model_name,"\"");
	for (int i = 0; i < input_model_names_.size(); i++){
		if (!strcmp(input_model_names_[i].c_str(),forward_model_name)){
			forward_model_ = input_models_[i];
			//clog << "forward model initialized from file." << endl;
		}
	}

	//������������λ�úͳߴ�
	cpoint corner[8];
	for (int i = 0; i < model_num_; i++){
		for (int j = 0; j < 8; j++){
			corner[j] = model_vert_[model_cube_[i].ids[j]];
		}

		model_cube_[i].cen.x = 0.5*(corner[0].x + corner[6].x);
		model_cube_[i].cen.y = 0.5*(corner[0].y + corner[6].y);
		model_cube_[i].cen.z = 0.5*(corner[0].z + corner[6].z);
		model_cube_[i].dx = fabs(corner[6].x - corner[0].x);
		model_cube_[i].dy = fabs(corner[6].y - corner[0].y);
		model_cube_[i].dz = fabs(corner[6].z - corner[0].z);
	}

	for (int i = 0; i < input_models_.size(); i++){
		input_models_[i].clear();
		vector <double>().swap(input_models_[i]);
	}
	input_models_.clear();
	vector < vector<double> >().swap(input_models_);

	input_model_names_.clear();
	vector <string>().swap(input_model_names_);
	return 0;
}