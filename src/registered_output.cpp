#include "gm3d.h"

int GM3D::RegisteredOuput(bool remove_empty_element){
	int count;
	//ͳ�����ģ�͵�Ԫ����Ͷ��� �Լ�����Ŀ��������б�
	if (remove_empty_element){
		count = 0;
		//�������п������� ע����ֵ�Ŀ���
		for (int i = 0; i < model_num_; i++){
			if (model_block_val_[i] != BDL_MAX){
				out_ele_data_ids_.push_back(i);
				out_ele_ids_.push_back(i);
				ele_data_out_map_[count] = count;
				count++;
			}
		}

		//��������ע��Ŀ��� ��Ӷ���
		for (int i = 0; i < out_ele_ids_.size(); i++){
			for (int j = 0; j < 8; j++){
				out_vert_ids_.push_back(model_cube_[out_ele_ids_[i]].ids[j]);
			}
		}

		//ȥ����������е��ظ�����
		vector<int>::iterator pos; //���������ĵ�����
		sort(out_vert_ids_.begin(),out_vert_ids_.end()); //�Զ���������С��������
		pos = unique(out_vert_ids_.begin(),out_vert_ids_.end()); //��ȡ�ظ����п�ʼ��λ��
		out_vert_ids_.erase(pos,out_vert_ids_.end()); //ɾ���ظ���

		//����Ҫ�����ģ�Ͷ�����������ǵ�������һ����Ӧ ��֤������ļ��ж���������ʼ���Ǵ�0��ʼ������������
		for (int i = 0; i < out_vert_ids_.size(); i++){
			vert_out_map_[out_vert_ids_[i]] = i;
		}
	}
	else{
		//�����ģ�Ϳ���Ϊ����
		out_ele_ids_.resize(model_num_);
		for (int i = 0; i < model_num_; i++){
			out_ele_ids_[i] = i;
		}

		//�����ģ�Ͷ���Ϊ����
		out_vert_ids_.resize(vert_num_);
		for (int i = 0; i < vert_num_; i++){
			vert_out_map_[i] = out_vert_ids_[i] = i;
		}

		//ע��������ֵ�Ŀ�������
		count = 0;
		for (int i = 0; i < model_num_; i++){
			if (model_block_val_[i] != BDL_MAX){
				ele_data_out_map_[count] = i;
				out_ele_data_ids_.push_back(i);
				count++;
			}
		}
	}
	//�������ģ�͵�Ԫ����Ͷ��� ֻͳ������Ŀ��������б�
	return 0;
}