#ifndef _GM3D_H
#define _GM3D_H
#include "head_func.h"
#include "progress_bar.h"

class GM3D{
public:
	GM3D(){}
	~GM3D(){}
	int BuildRegularGrid(char*); //��ʼ������ģ�Ϳռ�
	int AddModels(char*); //��ȡģ�Ϳ�������ļ�
	void AddModels_GUI(); //���ģ�Ϳ������
	int AddRegularBlock(modelist); //�����ͨģ�Ϳ���
	int AddTiltedBlock(modelist); //�����бģ�Ϳ���
	int AddSphereBlock(modelist); //����������������
	int AddInterfaceBlock(modelist); //����ܶȽ���
	//ģ�Ͳ���
	int ReadModel(char*,char*);
	int ReadModel_mst(char*);
	//���ģ��
	int RegisteredOuput(bool); //ע������Ŀ���ģ��
	int OutMshFile(char*,string); //���ģ���ļ�
	int OutNeighborFile(char*,char*); //���ģ�Ϳ���򶥵�����ڹ�ϵ �ݻ�
	//�۲�����
	int InitObs(char*);
	int OutObs(char*);
	//���ݺ���
	int ForwardVz(char*);
	int ForwardVzx(char*);
	int ForwardVzy(char*);
	int ForwardVzz(char*);
	int ForwardDeltaT(char*,char*);
	int ForwardDeltaTx(char*,char*);
	int ForwardDeltaTy(char*,char*);
	int ForwardDeltaTz(char*,char*);
	int ForwardHax(char*,char*);
	int ForwardHay(char*,char*);
	int ForwardZa(char*,char*);
	//gm3d_gui����
	void get_model_list(modelistArray);
private:
	int obs_num_, model_num_, vert_num_;
	//��������
	obspointArray obs_p_;
	_2dArray input_models_;
	_1sArray input_model_names_;
	_1dArray forward_model_;
	//ģ������
	cubeArray model_cube_;
	cpointArray model_vert_;
	_1dArray model_block_val_;
	modelistArray model_list_;
	_1iArray out_ele_ids_;
	_1iArray out_ele_data_ids_;
	_1iArray out_vert_ids_;
	_int2intMap vert_out_map_;
	_int2intMap ele_data_out_map_;

	_2iArray model_vert_neighbor_; //�ݻ�
	_2iArray model_cube_neighbor_; //�ݻ�
};
#endif