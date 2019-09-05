// generated by Fast Light User Interface Designer (fluid) version 1.0305

#include "add_model.h"

Fl_Double_Window *add_mod_win=(Fl_Double_Window *)0;

Fl_Group *mod_type_group=(Fl_Group *)0;

Fl_Round_Button *reg_bok_rbtn=(Fl_Round_Button *)0;

Fl_Round_Button *til_bok_rbtn=(Fl_Round_Button *)0;

Fl_Round_Button *sph_rbtn=(Fl_Round_Button *)0;

Fl_Round_Button *int_face_rbtn=(Fl_Round_Button *)0;

Fl_Group *val_type_group=(Fl_Group *)0;

Fl_Round_Button *app_val_rbtn=(Fl_Round_Button *)0;

Fl_Round_Button *rep_val_rbtn=(Fl_Round_Button *)0;

Fl_Round_Button *era_val_rbtn=(Fl_Round_Button *)0;

Fl_Group *agn_part_group=(Fl_Group *)0;

Fl_Round_Button *top_val_btn=(Fl_Round_Button *)0;

Fl_Round_Button *bot_val_btn=(Fl_Round_Button *)0;

Fl_Input *sig_mod_para_input=(Fl_Input *)0;

Fl_Return_Button *can_add_btn=(Fl_Return_Button *)0;

Fl_Button *sig_add_btn=(Fl_Button *)0;

Fl_Input *mod_val_input=(Fl_Input *)0;

void cb_add_mod_btn(Fl_Button*, void*) {
  { add_mod_win = new Fl_Double_Window(315, 300, "Add model (gm3d)");
    { mod_type_group = new Fl_Group(20, 25, 250, 53, "Model Type :");
      mod_type_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { reg_bok_rbtn = new Fl_Round_Button(20, 25, 110, 28, "Regular Block");
        reg_bok_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* reg_bok_rbtn
      { til_bok_rbtn = new Fl_Round_Button(160, 25, 100, 28, "Tilted Block");
        til_bok_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* til_bok_rbtn
      { sph_rbtn = new Fl_Round_Button(20, 50, 70, 28, "Sphere");
        sph_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* sph_rbtn
      { int_face_rbtn = new Fl_Round_Button(160, 50, 80, 28, "Interface");
        int_face_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* int_face_rbtn
      mod_type_group->end();
    } // Fl_Group* mod_type_group
    { val_type_group = new Fl_Group(20, 100, 250, 30, "Value Type :");
      val_type_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { app_val_rbtn = new Fl_Round_Button(20, 100, 80, 28, "Append");
        app_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* app_val_rbtn
      { rep_val_rbtn = new Fl_Round_Button(110, 100, 80, 28, "Replace");
        rep_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* rep_val_rbtn
      { era_val_rbtn = new Fl_Round_Button(200, 100, 60, 28, "Erase");
        era_val_rbtn->down_box(FL_ROUND_DOWN_BOX);
      } // Fl_Round_Button* era_val_rbtn
      val_type_group->end();
    } // Fl_Group* val_type_group
    { agn_part_group = new Fl_Group(20, 150, 160, 28, "Assgin Part :");
      agn_part_group->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { top_val_btn = new Fl_Round_Button(20, 150, 50, 28, "Top");
        top_val_btn->down_box(FL_ROUND_DOWN_BOX);
        top_val_btn->deactivate();
      } // Fl_Round_Button* top_val_btn
      { bot_val_btn = new Fl_Round_Button(110, 150, 70, 28, "Bottom");
        bot_val_btn->down_box(FL_ROUND_DOWN_BOX);
        bot_val_btn->deactivate();
      } // Fl_Round_Button* bot_val_btn
      agn_part_group->end();
    } // Fl_Group* agn_part_group
    { sig_mod_para_input = new Fl_Input(20, 200, 275, 28, "Model Parameter :");
      sig_mod_para_input->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Input* sig_mod_para_input
    { can_add_btn = new Fl_Return_Button(210, 255, 85, 28, "Cancel");
    } // Fl_Return_Button* can_add_btn
    { sig_add_btn = new Fl_Button(140, 255, 60, 28, "Add");
    } // Fl_Button* sig_add_btn
    { mod_val_input = new Fl_Input(20, 255, 110, 28, "Model Value :");
      mod_val_input->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Input* mod_val_input
    add_mod_win->end();
  } // Fl_Double_Window* add_mod_win
}
