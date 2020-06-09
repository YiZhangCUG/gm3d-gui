#include "gm3d_gui.h"

Fl_Double_Window *add_mod_win=(Fl_Double_Window *)0;
Fl_Group *mod_type_group=(Fl_Group *)0;
Fl_Radio_Round_Button *reg_bok_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *til_bok_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *sph_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *int_face_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Group *val_type_group=(Fl_Group *)0;
Fl_Radio_Round_Button *app_val_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *rep_val_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *era_val_rbtn=(Fl_Radio_Round_Button *)0;
Fl_Group *agn_part_group=(Fl_Group *)0;
Fl_Radio_Round_Button *top_val_btn=(Fl_Radio_Round_Button *)0;
Fl_Radio_Round_Button *bot_val_btn=(Fl_Radio_Round_Button *)0;
Fl_Input *sig_mod_para_input=(Fl_Input *)0;
Fl_Return_Button *can_add_btn=(Fl_Return_Button *)0;
Fl_Button *sig_add_btn=(Fl_Button *)0;
Fl_Input *mod_val_input=(Fl_Input *)0;

// 声明三个字符串用于保存新建的模型类型和赋值类型
char add_mod_type[1024];
char add_val_type[1024];
char agn_val_type[1024];

void cb_reg_bok_rbtn(Fl_Button*, void*){
  strcpy(add_mod_type,"regular_block");
  agn_part_group->deactivate();
  //printf("%s\n", "Regular block button selected!");
  return;
}

void cb_til_bok_rbtn(Fl_Button*, void*){
  strcpy(add_mod_type,"tilted_block");
  agn_part_group->deactivate();
  //printf("%s\n", "Tilted block button selected!");
  return;
}

void cb_sph_rbtn(Fl_Button*, void*){
  strcpy(add_mod_type,"sphere");
  agn_part_group->deactivate();
  //printf("%s\n", "Sphere button selected!");
  return;
}

void cb_int_face_rbtn(Fl_Button*, void*){
  strcpy(add_mod_type,"interface");
  agn_part_group->activate();
  //printf("%s\n", "Interface button selected!");
  return;
}

void cb_app_val_rbtn(Fl_Button*, void*){
  strcpy(add_val_type,"add");
  //printf("%s\n", "append button selected!");
  return;
}

void cb_rep_val_rbtn(Fl_Button*, void*){
  strcpy(add_val_type,"replace");
  //printf("%s\n", "replace button selected!");
  return;
}

void cb_era_val_rbtn(Fl_Button*, void*){
  strcpy(add_val_type,"erase");
  //printf("%s\n", "Erase button selected!");
  return;
}

void cb_top_val_rbtn(Fl_Button*, void*){
  strcpy(agn_val_type,"top");
  //printf("%s\n", "Erase button selected!");
  return;
}

void cb_bot_val_rbtn(Fl_Button*, void*){
  strcpy(agn_val_type,"bot");
  //printf("%s\n", "Erase button selected!");
  return;
}

// 声明一个字符串用于保存新建的模型参数并添加至列表中
// 模型参数的排列为<模型类型> <赋值类型> <物理参数字符串> <几何参数字符串>
char add_mod_para[1024];

void cb_sig_add_btn(Fl_Widget*, void*){
  strcpy(add_mod_para,add_mod_type);
  strcat(add_mod_para," ");
  strcat(add_mod_para,add_val_type);
  if (!strcmp(add_mod_type,"interface"))
  {
    strcat(add_mod_para,"/");
    strcat(add_mod_para,agn_val_type);
  }
  strcat(add_mod_para," ");
  strcat(add_mod_para,mod_val_input->value());
  strcat(add_mod_para," ");
  strcat(add_mod_para,sig_mod_para_input->value());
  mod_para_brw->add(add_mod_para);
  return;
}
//取消添加模型
void cb_can_add_btn(Fl_Widget*, void*){
	add_mod_win->hide();
	return;
}

void cb_add_mod_btn(Fl_Widget*, void*)
{
  { add_mod_win = new Fl_Double_Window(315, 300, "Add model (gm3d)");
    { mod_type_group = new Fl_Group(20, 25, 250, 53, "Model Type :");
      mod_type_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { reg_bok_rbtn = new Fl_Radio_Round_Button(20, 25, 110, 28, "Regular Block");
        reg_bok_rbtn->down_box(FL_ROUND_DOWN_BOX);
        reg_bok_rbtn->callback((Fl_Callback*)cb_reg_bok_rbtn);
        reg_bok_rbtn->tooltip("model parameter:\n<xmin>/<xmax>/<ymin>/<ymax>/<zmin>/<zmax>");
      } // Fl_Radio_Round_Button* reg_bok_rbtn
      { til_bok_rbtn = new Fl_Radio_Round_Button(160, 25, 100, 28, "Tilted Block");
        til_bok_rbtn->down_box(FL_ROUND_DOWN_BOX);
        til_bok_rbtn->callback((Fl_Callback*)cb_til_bok_rbtn);
        til_bok_rbtn->tooltip("model parameter:\n<xmin_z>/<xmax_z>/<ymin_z>/<ymax_z>/<zmin>/<xmin_Z>/<xmax_Z>/<ymin_Z>/<ymax_Z>/<zmax>");
      } // Fl_Radio_Round_Button* til_bok_rbtn
      { sph_rbtn = new Fl_Radio_Round_Button(20, 50, 70, 28, "Sphere");
        sph_rbtn->down_box(FL_ROUND_DOWN_BOX);
        sph_rbtn->callback((Fl_Callback*)cb_sph_rbtn);
        sph_rbtn->tooltip("model parameter:\n<x_c>/<y_c>/<z_c>/<x_radius>/<y_radius>/<z_radius>");
      } // Fl_Radio_Round_Button* sph_rbtn
      { int_face_rbtn = new Fl_Radio_Round_Button(160, 50, 80, 28, "Interface");
        int_face_rbtn->down_box(FL_ROUND_DOWN_BOX);
        int_face_rbtn->callback((Fl_Callback*)cb_int_face_rbtn);
        int_face_rbtn->tooltip("model parameter:\n<grid-filename>");
      } // Fl_Radio_Round_Button* int_face_rbtn
      mod_type_group->end();
    } // Fl_Group* mod_type_group
    { val_type_group = new Fl_Group(20, 100, 250, 28, "Value Type :");
      val_type_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { app_val_rbtn = new Fl_Radio_Round_Button(20, 100, 80, 28, "Append");
        app_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
        app_val_rbtn->callback((Fl_Callback*)cb_app_val_rbtn);
      } // Fl_Radio_Round_Button* app_val_rbtn
      { rep_val_rbtn = new Fl_Radio_Round_Button(110, 100, 80, 28, "Replace");
        rep_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
        rep_val_rbtn->callback((Fl_Callback*)cb_rep_val_rbtn);
      } // Fl_Radio_Round_Button* rep_val_rbtn
      { era_val_rbtn = new Fl_Radio_Round_Button(200, 100, 60, 28, "Erase");
        era_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
        era_val_rbtn->callback((Fl_Callback*)cb_era_val_rbtn);
      } // Fl_Radio_Round_Button* era_val_rbtn
      val_type_group->end();
    } // Fl_Group* val_type_group
    { agn_part_group = new Fl_Group(20, 150, 160, 28, "Assign Part :");
      agn_part_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { top_val_btn = new Fl_Radio_Round_Button(20, 150, 50, 28, "Top");
        top_val_btn->down_box(FL_ROUND_DOWN_BOX);
        top_val_btn->callback((Fl_Callback*)cb_top_val_rbtn);
      } // Fl_Radio_Round_Button* top_val_btn
      { bot_val_btn = new Fl_Radio_Round_Button(110, 150, 70, 28, "Bottom");
        bot_val_btn->down_box(FL_ROUND_DOWN_BOX);
        bot_val_btn->callback((Fl_Callback*)cb_bot_val_rbtn);
      } // Fl_Radio_Round_Button* bot_val_btn
      agn_part_group->deactivate();
      agn_part_group->end();
    } // Fl_Group* agn_part_group
    { sig_mod_para_input = new Fl_Input(20, 200, 275, 28, "Model Parameter :");
      sig_mod_para_input->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Input* sig_mod_para_input
    { can_add_btn = new Fl_Return_Button(210, 255, 85, 28, "Cancel");
      can_add_btn->callback((Fl_Callback*)cb_can_add_btn);
    } // Fl_Return_Button* can_add_btn
    { sig_add_btn = new Fl_Button(140, 255, 60, 28, "Add");
      sig_add_btn->callback((Fl_Callback*)cb_sig_add_btn);
    } // Fl_Button* sig_add_btn
    { mod_val_input = new Fl_Input(20, 255, 110, 28, "Model Value :");
      mod_val_input->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Input* mod_val_input
    add_mod_win->end();
    add_mod_win->show();
  } // Fl_Double_Window* add_mod_win
  return;
}