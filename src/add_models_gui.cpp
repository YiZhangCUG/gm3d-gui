#include "gm3d.h"

void GM3D::AddModels_GUI(){
	for (int i = 0; i < model_list_.size(); i++){
		if (!strcmp(model_list_[i].mod_type,"regular_block")){
			AddRegularBlock(model_list_[i]);
		}
		else if (!strcmp(model_list_[i].mod_type,"tilted_block")){
			AddTiltedBlock(model_list_[i]);
		}
		else if (!strcmp(model_list_[i].mod_type,"sphere")){
			AddSphereBlock(model_list_[i]);
		}
		else if (!strcmp(model_list_[i].mod_type,"interface")){
			AddInterfaceBlock(model_list_[i]);
		}
		else{
			cerr << BOLDYELLOW << "ignored ==> " << RESET << "unknown model type: " << model_list_[i].mod_type << endl;
			continue;
		}
	}
	return;
}