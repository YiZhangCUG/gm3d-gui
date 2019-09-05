#include "gm3d_gui.h"
#include "gm3d.h"

Fl_Double_Window *main_window=(Fl_Double_Window *)0;
Fl_Tabs *main_tabs=(Fl_Tabs *)0;
Fl_Group *model_tab=(Fl_Group *)0;
Fl_Input *mesh_para_input=(Fl_Input *)0;
Fl_Button *mesh_file_btn=(Fl_Button *)0;
Fl_Button *mod_para_file_btn=(Fl_Button *)0;
Fl_Input *mod_ele_input_build=(Fl_Input *)0;
Fl_Button *build_mod_btn=(Fl_Button *)0;
Fl_Output *mesh_para_output=(Fl_Output *)0;
Fl_Button *add_mod_btn=(Fl_Button *)0;
Fl_Button *del_mod_btn=(Fl_Button *)0;
Fl_Check_Button *rm_emp_bok_check=(Fl_Check_Button *)0;
Fl_Browser *mod_para_brw=(Fl_Browser *)0;
Fl_Button *mod_file_out_btn=(Fl_Button *)0;
Fl_Output *mod_out_file_output=(Fl_Output *)0;
Fl_Group *forward_tab=(Fl_Group *)0;
Fl_Group *grav_group=(Fl_Group *)0;
Fl_Check_Button *Vz_check=(Fl_Check_Button *)0;
Fl_Check_Button *Vzx_check=(Fl_Check_Button *)0;
Fl_Check_Button *Vzy_check=(Fl_Check_Button *)0;
Fl_Check_Button *Vzz_check=(Fl_Check_Button *)0;
Fl_Button *mod_file_btn=(Fl_Button *)0;
Fl_Button *obs_file_btn=(Fl_Button *)0;
Fl_Input *mod_file_input=(Fl_Input *)0;
Fl_Output *mod_file_output=(Fl_Output *)0;
Fl_Input *obs_file_input=(Fl_Input *)0;
Fl_Output *obs_file_output=(Fl_Output *)0;
Fl_Input *mod_ele_input=(Fl_Input *)0;
Fl_Group *mag_group=(Fl_Group *)0;
Fl_Check_Button *DeltaT_check=(Fl_Check_Button *)0;
Fl_Check_Button *DeltaTx_check=(Fl_Check_Button *)0;
Fl_Check_Button *DeltaTy_check=(Fl_Check_Button *)0;
Fl_Check_Button *DeltaTz_check=(Fl_Check_Button *)0;
Fl_Check_Button *Hax_check=(Fl_Check_Button *)0;
Fl_Check_Button *Hay_check=(Fl_Check_Button *)0;
Fl_Check_Button *Za_check=(Fl_Check_Button *)0;
Fl_Input *mag_para_input=(Fl_Input *)0;
Fl_Check_Button *mag_data_check=(Fl_Check_Button *)0;
Fl_Button *cal_btn=(Fl_Button *)0;
Fl_Input *noise_para_input=(Fl_Input *)0;
Fl_Check_Button *noise_check=(Fl_Check_Button *)0;
Fl_Input *res_file_input=(Fl_Input *)0;
Fl_Button *res_file_btn=(Fl_Button *)0;
Fl_Output *res_file_output=(Fl_Output *)0;

char mesh_filename[1024];
char out_msh_filename[1024];

void cb_mesh_para_input(Fl_Input*, void*){
	strcpy(mesh_filename,mesh_para_input->value());
	mesh_para_output->value(mesh_para_input->value());
	return;
}

void cb_mesh_file_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  // directory, filter, chooser type, title
  Fl_File_Chooser chooser(".", "*.txt, *.dat, *.xyz", Fl_File_Chooser::SINGLE, "Choose a mesh file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //从文件的绝对路径中分离文件名并从输出框输出
  if (chooser.value() != NULL)
  {
    strcpy(mesh_filename,chooser.value());

    std::string abs_filename = chooser.value();
    int pos = abs_filename.find_last_of("/");

    std::stringstream temp_ss;
    temp_ss << abs_filename.substr(pos+1);
    const char* disp_filename = temp_ss.str().c_str();
    mesh_para_output->value(disp_filename);
  }
  else
  {
    mesh_para_output->value("Unset");
  }
  return;
}

void cb_mod_para_file_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  Fl_File_Chooser chooser(".", "*.txt, *.dat, *.xyz", Fl_File_Chooser::SINGLE, "Choose a model list file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //下面我们读入文件并添加模型参数到列表显示
  std::ifstream modpara_in;
  modpara_in.open(chooser.value());
  if (!modpara_in)
  {
    fl_message("Error! Fail to open file: %s",chooser.value());
    return;
  }
  else{
    std::string temp_str;
    std::stringstream temp_ss;

    while(getline(modpara_in,temp_str)){
      if (*(temp_str.begin()) == '#') continue;
      else{
        temp_ss.clear(); temp_ss.str("");
        temp_ss << temp_str;
        mod_para_brw->add(temp_ss.str().c_str());
      }
    }
    modpara_in.close();
  }
  return;
}

void cb_del_mod_btn(Fl_Widget*, void*){
  int index = mod_para_brw->value();
  mod_para_brw->remove(index);
  del_mod_btn->deactivate();
}

void cb_mod_para_brw(Fl_Browser*, void*){
  for ( int t=1; t<=mod_para_brw->size(); t++ ) {
    if ( mod_para_brw->selected(t) ) {
      //printf("%d) '%s'\n", t, mod_para_brw->text(t));
      del_mod_btn->activate();
    }
  }
  return;
}

bool remove_null = false;
void cb_rm_emp_bok_check(Fl_Check_Button*, void*){
  if (rm_emp_bok_check->value() == 1) remove_null = true;
  else if (rm_emp_bok_check->value() == 0) remove_null = false;
  return;
}

void cb_mod_file_out_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  // directory, filter, chooser type, title
  Fl_File_Chooser chooser(".", "*.msh", Fl_File_Chooser::CREATE, "Create a new model file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //从文件的绝对路径中分离文件名并从输出框输出
  if (chooser.value() != NULL)
  {
    strcpy(out_msh_filename,chooser.value());

    std::string abs_filename = chooser.value();
    int pos = abs_filename.find_last_of("/");

    std::stringstream temp_ss;
    temp_ss << abs_filename.substr(pos+1);
    const char* disp_filename = temp_ss.str().c_str();
    mod_out_file_output->value(disp_filename);
  }
  else
  {
    mod_out_file_output->value("Unset");
  }
  return;
}

void cb_build_mod_btn(Fl_Widget*, void*){
  //首先构建一个GM3D实例
  GM3D gm3d_instance;
  //设置初始化变量
  char dimension[1024] = "10/20/990/10/20/990/10/20/490";
  char out_mshname[1024] = "Untitled.msh";
  char elename[1024] = "Untitled";

  //将mesh_para_output拷贝到dimension
  strcpy(dimension, mesh_filename);
  //std::cout << dimension << std::endl;
  //将mod_para_brw中的模型参数列表拷贝到一个临时参数列表
  std::stringstream temp_ss;
  modelist temp_list;
  modelistArray brw_model_list;

  for ( int t=1; t<=mod_para_brw->size(); t++ ) {
      temp_ss.clear(); temp_ss.str("");
      temp_ss << mod_para_brw->text(t);
      if(temp_ss >> temp_list.mod_type >> temp_list.val_type >> temp_list.mod_value >> temp_list.mod_para){
        brw_model_list.push_back(temp_list);
      }
      else{
        fl_message("Wrong model parameter: %s. Skipped !",mod_para_brw->text(t));
      }
  }

  //将brw_model_list拷贝到GM3D中
  gm3d_instance.get_model_list(brw_model_list);
  //将mod_out_file_input拷贝到out_mshname
  strcpy(out_mshname, out_msh_filename);
  if (!strcmp(out_mshname,"")){
    fl_message("Output file's name can't be empty !");
    return;
  }
  //将mod_ele_input_build拷贝到elename
  strcpy(elename, mod_ele_input_build->value());
  if (!strcmp(elename,"")){
    fl_message("Element data's name can't be empty !");
    return;
  }
  //构建模型网络
  if(gm3d_instance.BuildRegularGrid(dimension)){
    fl_message("Mesh Parameters Load Error !");
    return;
  }
  gm3d_instance.AddModels_GUI();
  gm3d_instance.RegisteredOuput(remove_null);
  if (gm3d_instance.OutMshFile(out_mshname,elename)) return;

  //这里需要一个输出信息窗口
  fl_message("Model Construction Completed !");
  return;
}

/***********************************以下是正演计算GUI函数******************************/
char in_msh_filename[1024];
char in_obs_filename[1024];
char out_res_filename[1024];

void cb_mod_file_input(Fl_Input*, void*){
	strcpy(in_msh_filename,mod_file_input->value());
	mod_file_output->value(mod_file_input->value());
	return;
}

void cb_mod_file_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  // directory, filter, chooser type, title
  Fl_File_Chooser chooser(".", "*.msh", Fl_File_Chooser::SINGLE, "Create a model file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //从文件的绝对路径中分离文件名并从输出框输出
  if (chooser.value() != NULL)
  {
    strcpy(in_msh_filename,chooser.value());

    std::string abs_filename = chooser.value();
    int pos = abs_filename.find_last_of("/");

    std::stringstream temp_ss;
    temp_ss << abs_filename.substr(pos+1);
    const char* disp_filename = temp_ss.str().c_str();
    mod_file_output->value(disp_filename);
  }
  else
  {
    mod_file_output->value("Unset");
  }
  return;
}

void cb_obs_file_input(Fl_Input*, void*){
	strcpy(in_obs_filename,obs_file_input->value());
	obs_file_output->value(obs_file_input->value());
	return;
}

void cb_obs_file_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  // directory, filter, chooser type, title
  Fl_File_Chooser chooser(".", "*.txt, *.dat, *.xyz", Fl_File_Chooser::SINGLE, "Create observe file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //从文件的绝对路径中分离文件名并从输出框输出
  if (chooser.value() != NULL)
  {
    strcpy(in_obs_filename,chooser.value());

    std::string abs_filename = chooser.value();
    int pos = abs_filename.find_last_of("/");

    std::stringstream temp_ss;
    temp_ss << abs_filename.substr(pos+1);
    const char* disp_filename = temp_ss.str().c_str();
    obs_file_output->value(disp_filename);
  }
  else
  {
    obs_file_output->value("Unset");
  }
  return;
}

void cb_res_file_input(Fl_Input*, void*){
	strcpy(out_res_filename,res_file_input->value());
	res_file_output->value(res_file_input->value());
	return;
}

void cb_res_file_btn(Fl_Widget*, void*){
  // Create the file chooser, and show it
  // directory, filter, chooser type, title
  Fl_File_Chooser chooser(".", "*.txt, *.dat", Fl_File_Chooser::CREATE, "Create a new observe file.");
  chooser.show();

  // Block until user picks something.
  while(chooser.shown()) { Fl::wait(); }

  //从文件的绝对路径中分离文件名并从输出框输出
  if (chooser.value() != NULL)
  {
    strcpy(out_res_filename,chooser.value());

    std::string abs_filename = chooser.value();
    int pos = abs_filename.find_last_of("/");

    std::stringstream temp_ss;
    temp_ss << abs_filename.substr(pos+1);
    const char* disp_filename = temp_ss.str().c_str();
    res_file_output->value(disp_filename);
  }
  else
  {
    res_file_output->value("Unset");
  }
  return;
}

void cb_noise_check(Fl_Check_Button*, void*){
  if (noise_check->value() == 1){
    noise_para_input->activate();
  }
  else if (noise_check->value() == 0){
    noise_para_input->deactivate();
  }
  return;
}

void cb_mag_data_check(Fl_Check_Button*, void*){
  if (mag_data_check->value() == 1){
    mag_para_input->activate();
    DeltaT_check->activate();
    DeltaTx_check->activate();
    DeltaTy_check->activate();
    DeltaTz_check->activate();
    Hax_check->activate();
    Hay_check->activate();
    Za_check->activate();
  }
  else if (mag_data_check->value() == 0){
    mag_para_input->deactivate();
    DeltaT_check->deactivate();
    DeltaTx_check->deactivate();
    DeltaTy_check->deactivate();
    DeltaTz_check->deactivate();
    Hax_check->deactivate();
    Hay_check->deactivate();
    Za_check->deactivate();
  }
  return;
}

void cb_cal_btn(Fl_Button*, void*){
  //首先构建一个GM3D实例
  GM3D gm3d_instance;
  //设置初始化变量
  char in_mshname[1024] = "Untitled.msh";
  char in_obspara[1024] = "Untitled.txt";
  char res_outfile[1024] = "Untitled";
  char res_outfile_full[1024];
  char ele_name[1024] = "Untitled";
  char noise_para[1024] = "0.0/0.0";
  char mag_para[1024] = "90.0/0.0/90.0/0.0";

  strcpy(in_mshname,in_msh_filename);
  strcpy(in_obspara,in_obs_filename);
  strcpy(res_outfile,out_res_filename);
  strcpy(ele_name,mod_ele_input->value());
  strcpy(noise_para,noise_para_input->value());
  strcpy(mag_para,mag_para_input->value());

  if (gm3d_instance.ReadModel(in_mshname,ele_name))
  {
    fl_message("Model Load Error !");
    return;
  }

  if (gm3d_instance.InitObs(in_obspara))
  {
    fl_message("Observe File Load Error !");
    return;
  }

  if (Vz_check->value() == 1)
  {
    gm3d_instance.ForwardVz(noise_para);
    strcpy(res_outfile_full,res_outfile);
    strcat(res_outfile_full,"_Vz.txt");
    if (gm3d_instance.OutObs(res_outfile_full))
    {
      fl_message("Observe File Output Error !");
      return;
    }
  }

  if (Vzx_check->value() == 1)
  {
    gm3d_instance.ForwardVzx(noise_para);
    strcpy(res_outfile_full,res_outfile);
    strcat(res_outfile_full,"_Vzx.txt");
    if (gm3d_instance.OutObs(res_outfile_full))
    {
      fl_message("Observe File Output Error !");
      return;
    }
  }

  if (Vzy_check->value() == 1)
  {
    gm3d_instance.ForwardVzy(noise_para);
    strcpy(res_outfile_full,res_outfile);
    strcat(res_outfile_full,"_Vzy.txt");
    if (gm3d_instance.OutObs(res_outfile_full))
    {
      fl_message("Observe File Output Error !");
      return;
    }
  }

  if (Vzz_check->value() == 1)
  {
    gm3d_instance.ForwardVzz(noise_para);
    strcpy(res_outfile_full,res_outfile);
    strcat(res_outfile_full,"_Vzz.txt");
    if (gm3d_instance.OutObs(res_outfile_full))
    {
      fl_message("Observe File Output Error !");
      return;
    }
  }

  if (mag_data_check->value() == 1)
  {
    if (DeltaT_check->value() == 1)
    {
      gm3d_instance.ForwardDeltaT(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_DeltaT.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (DeltaTx_check->value() == 1)
    {
      gm3d_instance.ForwardDeltaTx(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_DeltaTx.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (DeltaTy_check->value() == 1)
    {
      gm3d_instance.ForwardDeltaTy(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_DeltaTy.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (DeltaTz_check->value() == 1)
    {
      gm3d_instance.ForwardDeltaTz(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_DeltaTz.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (Hax_check->value() == 1)
    {
      gm3d_instance.ForwardHax(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_Hax.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (Hay_check->value() == 1)
    {
      gm3d_instance.ForwardHay(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_Hay.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }

    if (Za_check->value() == 1)
    {
      gm3d_instance.ForwardZa(noise_para,mag_para);
      strcpy(res_outfile_full,res_outfile);
      strcat(res_outfile_full,"_Za.txt");
      if (gm3d_instance.OutObs(res_outfile_full))
      {
        fl_message("Observe File Output Error !");
        return;
      }
    }
  }

  fl_message("Forward calculation completed !");
  return;
}