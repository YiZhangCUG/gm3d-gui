#include "gm3d.h"

int GM3D::ReadModel_mst(char* filename){
	int temp_int,ele_type,attri_num,temp_attri,temp_id;
	double temp_val;
	_1dArray temp_model;
	cpoint temp_vert;
	cube temp_cu;
	string temp_str;
	stringstream temp_ss;

	ifstream mstin;
	if (open_infile(mstin,filename)) return -1; //¼ì²é²¢´ò¿ªÄ£ÐÍÎÄ¼þ
	double ynum, xnum, znum;
    double ystart, xstart, zstart;
    double ylength, xlength, zlength;
    char temp;
    mstin>>ynum>>xnum>>znum;
    mstin>>ystart>>xstart>>zstart;
    mstin>>ynum>>temp>>ylength;
	mstin>>xnum>>temp>>xlength;
	mstin>>znum>>temp>>zlength;

    model_num_ = ynum*xnum*znum;
    model_cube_.resize(model_num_);
	//³õÊ¼»¯Êý×é
	forward_model_.resize(model_num_,0.0);

    double f_mdl_tmp;

    int i, j, k;
    int tmp_num;
    for(i = 0; i < xnum; i++){
        for(j = 0; j < ynum; j++){
            for(k = 0; k < znum; k++){
                tmp_num = i*ynum*znum + j*znum + k;
                mstin>>f_mdl_tmp;
                forward_model_[tmp_num] = f_mdl_tmp;
                model_cube_[tmp_num].cen.x = xstart + xlength*i + xlength*0.5;
                model_cube_[tmp_num].cen.y = ystart + ylength*j + ylength*0.5;
                model_cube_[tmp_num].cen.z = zstart + zlength*k + zlength*0.5;
                model_cube_[tmp_num].dx = xlength;
                model_cube_[tmp_num].dy = ylength;
                model_cube_[tmp_num].dz = zlength;
            }
        }
    }
    mstin.close();

	return 0;
}