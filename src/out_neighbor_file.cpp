#include "gm3d.h"

int GM3D::OutNeighborFile(char* v_name,char* b_name){
	/*
	if (strcmp(v_name,"NULL") || strcmp(b_name,"NULL")){
		//������������ڹ�ϵ �ȳ�ʼ��������������
		model_vert_neighbor_.resize(vert_num_);
		for (int i = 0; i < vert_num_; i++)
			model_vert_neighbor_[i].resize(8,-1);

		//�������п������������ڹ�ϵ
		for (int i = 0; i < model_num_; i++){
			for (int j = 0; j < 8; j++){
				model_vert_neighbor_[model_cube_[i].ids[j]][j] = model_cube_[i].cen.id;
			}
		}

		//�������ж������ڹ�ϵ ���й���Ŀ��嶼���϶�Ϊ���ڿ���
		model_cube_neighbor_.resize(model_num_);

		//ѭ�����������б� ����Ϊ-1���໥���
		for (int i = 0; i < vert_num_; i++){
			for (int n = 0; n < 8; n++){
				if (model_vert_neighbor_[i][n] != -1){
					for (int k = 1; k < 8; k++){
						if (model_vert_neighbor_[i][(n+k)%8] != -1){
							model_cube_neighbor_[model_vert_neighbor_[i][n]].push_back(model_vert_neighbor_[i][(n+k)%8]);
							model_cube_neighbor_[model_vert_neighbor_[i][(n+k)%8]].push_back(model_vert_neighbor_[i][n]);
						}
					}
				}
			}
		}

		vector<int>::iterator pos; //���������ĵ�����
		for (int i = 0; i < model_num_; i++){
			sort(model_cube_neighbor_[i].begin(),model_cube_neighbor_[i].end()); //�Զ���������С��������
			pos = unique(model_cube_neighbor_[i].begin(),model_cube_neighbor_[i].end()); //��ȡ�ظ����п�ʼ��λ��
			model_cube_neighbor_[i].erase(pos,model_cube_neighbor_[i].end()); //ɾ���ظ���
		}

		//��������
		for (int i = 0; i < vert_num_; i++){
			model_vert_neighbor_[i].clear();
			vector <int>().swap(model_vert_neighbor_[i]);
		}
		model_vert_neighbor_.clear();
		vector < vector<int> >().swap(model_vert_neighbor_);
	}
	*/
	return 0;
}