// generated by Fast Light User Interface Designer (fluid) version 1.0305

#ifndef _GM3D_GUI_H
#define _GM3D_GUI_H
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Browser.H>

extern void cb_mesh_para_input(Fl_Input*, void*);
extern void cb_mesh_file_btn(Fl_Widget*, void*);
extern void cb_add_mod_btn(Fl_Widget*, void*);
extern void cb_mod_para_file_btn(Fl_Widget*, void*);
extern void cb_del_mod_btn(Fl_Widget*, void*);
extern void cb_mod_para_brw(Fl_Browser*, void*);
extern void cb_mod_ele_input(Fl_Input*, void*);
extern void cb_rm_emp_bok_check(Fl_Check_Button*, void*);
extern void cb_mod_file_out_btn(Fl_Widget*, void*);
extern void cb_build_mod_btn(Fl_Widget*, void*);
extern void cb_mod_file_input(Fl_Input*, void*);
extern void cb_mod_file_btn(Fl_Widget*, void*);
extern void cb_obs_file_input(Fl_Input*, void*);
extern void cb_obs_file_btn(Fl_Widget*, void*);
extern void cb_res_file_input(Fl_Input*, void*);
extern void cb_res_file_btn(Fl_Widget*, void*);
extern void cb_nosie_check(Fl_Check_Button*, void*);
extern void cb_noise_para_input(Fl_Input*, void*);
extern void cb_mag_data_check(Fl_Check_Button*, void*);
extern void cb_mag_para_input(Fl_Input*, void*);
extern void cb_cal_btn(Fl_Button*, void*);
extern void cb_noise_check(Fl_Check_Button*, void*);

extern Fl_Double_Window *main_window;
extern Fl_Tabs *main_tabs;
extern Fl_Group *model_tab;
extern Fl_Input *mesh_para_input;
extern Fl_Button *mesh_file_btn;
extern Fl_Button *mod_para_file_btn;
extern Fl_Input *mod_ele_input_build;
extern Fl_Button *build_mod_btn;
extern Fl_Output *mesh_para_output;
extern Fl_Button *add_mod_btn;
extern Fl_Button *del_mod_btn;
extern Fl_Check_Button *rm_emp_bok_check;
extern Fl_Browser *mod_para_brw;
extern Fl_Button *mod_file_out_btn;
extern Fl_Output *mod_out_file_output;
extern Fl_Group *forward_tab;
extern Fl_Group *grav_group;
extern Fl_Check_Button *Vz_check;
extern Fl_Check_Button *Vzx_check;
extern Fl_Check_Button *Vzy_check;
extern Fl_Check_Button *Vzz_check;
extern Fl_Button *mod_file_btn;
extern Fl_Button *obs_file_btn;
extern Fl_Input *mod_file_input;
extern Fl_Output *mod_file_output;
extern Fl_Input *obs_file_input;
extern Fl_Output *obs_file_output;
extern Fl_Input *mod_ele_input;
extern Fl_Group *mag_group;
extern Fl_Check_Button *DeltaT_check;
extern Fl_Check_Button *DeltaTx_check;
extern Fl_Check_Button *DeltaTy_check;
extern Fl_Check_Button *DeltaTz_check;
extern Fl_Check_Button *Hax_check;
extern Fl_Check_Button *Hay_check;
extern Fl_Check_Button *Za_check;
extern Fl_Input *mag_para_input;
extern Fl_Check_Button *mag_data_check;
extern Fl_Button *cal_btn;
extern Fl_Input *noise_para_input;
extern Fl_Check_Button *noise_check;
extern Fl_Input *res_file_input;
extern Fl_Button *res_file_btn;
extern Fl_Output *res_out_file_output;
#endif
