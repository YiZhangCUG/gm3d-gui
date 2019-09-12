#include "gm3d.h"

int GM3D::ForwardDeltaTy(char* noise_level,char* mag_para){
	int i,j;
	double I0,A0,I,A;
	double k1,k2,k3,k4,k5,k6;
	double x1,x2,y1,y2,z1,z2;
	double w111,w112,w121,w122,w211,w212,w221,w222;
	double v111,v112,v121,v122,v211,v212,v221,v222;
	double R222,R122,R212,R112,R221,R121,R211,R111;
	double G222,G122,G212,G112,G221,G121,G211,G111;

	//��ʼ������ֵ�Ͳ�ȷ����
	for (int i = 0; i < obs_num_; i++){
		obs_p_[i].val = obs_p_[i].dev = 0.0;
	}

	//ȷ������ˮƽ
	double noise_mean, noise_dev, temp_noise;
	if (2 != sscanf(noise_level,"%lf/%lf",&noise_mean,&noise_dev)){
		noise_mean = noise_dev = 0.0;
	}

	//ȷ���Ż�����
	if (4 != sscanf(mag_para,"%lf/%lf/%lf/%lf",&I0,&A0,&I,&A)){
		I0 = I = 90; A0 = A = 0;
	}
	else{
		I0=I0*Pi/180;
		A0=A0*Pi/180;
		I=I*Pi/180;
		A=A*Pi/180;

		k1=cos(I0)*sin(A0)*sin(I)+sin(I0)*cos(I)*sin(A);
		k2=cos(I0)*cos(A0)*sin(I)+sin(I0)*cos(I)*cos(A);
		k3=cos(I0)*cos(A0)*cos(I)*sin(A)+cos(I0)*sin(A0)*cos(I)*cos(A);
		k4=cos(I0)*cos(A0)*cos(I)*cos(A);
		k5=cos(I0)*sin(A0)*cos(I)*sin(A);
		k6=-sin(I0)*sin(I);
	}

	//��Ӹ�˹����ֵ
	default_random_engine generator;
	normal_distribution<double> dist(noise_mean, noise_dev);

	_1dArray temp_obs(model_num_);

	//ProgressBar *bar = new ProgressBar(obs_num_,"Forward modeling");
	for (i = 0; i < obs_num_; i++){
		//bar->Progressed(i);
#pragma omp parallel for private(j,R222,R122,R212,R112,R221,R121,R211,R111,\
		G222,G122,G212,G112,G221,G121,G211,G111,\
		w111,w112,w121,w122,w211,w212,w221,w222,\
		v111,v112,v121,v122,v211,v212,v221,v222,\
		x1,x2,y1,y2,z1,z2) shared(i) schedule(guided)
		for (j = 0; j < model_num_; j++){
			if (fabs(forward_model_[j]) > ZERO){
				x1 = model_cube_[j].cen.x - 0.5*model_cube_[j].dx; x2 = model_cube_[j].cen.x + 0.5*model_cube_[j].dx;
				y1 = model_cube_[j].cen.y - 0.5*model_cube_[j].dy; y2 = model_cube_[j].cen.y + 0.5*model_cube_[j].dy;
				z1 = model_cube_[j].cen.z - 0.5*model_cube_[j].dz; z2 = model_cube_[j].cen.z + 0.5*model_cube_[j].dz;

				R222=sqrt((x2-obs_p_[i].x)*(x2-obs_p_[i].x)+(y2-obs_p_[i].y)*(y2-obs_p_[i].y)+(z2-obs_p_[i].z)*(z2-obs_p_[i].z));
				R122=sqrt((x1-obs_p_[i].x)*(x1-obs_p_[i].x)+(y2-obs_p_[i].y)*(y2-obs_p_[i].y)+(z2-obs_p_[i].z)*(z2-obs_p_[i].z));
				R212=sqrt((x2-obs_p_[i].x)*(x2-obs_p_[i].x)+(y1-obs_p_[i].y)*(y1-obs_p_[i].y)+(z2-obs_p_[i].z)*(z2-obs_p_[i].z));
				R112=sqrt((x1-obs_p_[i].x)*(x1-obs_p_[i].x)+(y1-obs_p_[i].y)*(y1-obs_p_[i].y)+(z2-obs_p_[i].z)*(z2-obs_p_[i].z));
				R221=sqrt((x2-obs_p_[i].x)*(x2-obs_p_[i].x)+(y2-obs_p_[i].y)*(y2-obs_p_[i].y)+(z1-obs_p_[i].z)*(z1-obs_p_[i].z));
				R121=sqrt((x1-obs_p_[i].x)*(x1-obs_p_[i].x)+(y2-obs_p_[i].y)*(y2-obs_p_[i].y)+(z1-obs_p_[i].z)*(z1-obs_p_[i].z));
				R211=sqrt((x2-obs_p_[i].x)*(x2-obs_p_[i].x)+(y1-obs_p_[i].y)*(y1-obs_p_[i].y)+(z1-obs_p_[i].z)*(z1-obs_p_[i].z));
				R111=sqrt((x1-obs_p_[i].x)*(x1-obs_p_[i].x)+(y1-obs_p_[i].y)*(y1-obs_p_[i].y)+(z1-obs_p_[i].z)*(z1-obs_p_[i].z));

				w222=((x2-obs_p_[i].x)*(pow(y2-obs_p_[i].y,2)-R222*(z2-obs_p_[i].z)))/(R222*(pow(y2-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2))*(R222+z2-obs_p_[i].z));
				w122=((x1-obs_p_[i].x)*(pow(y2-obs_p_[i].y,2)-R122*(z2-obs_p_[i].z)))/(R122*(pow(y2-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2))*(R122+z2-obs_p_[i].z));
				w212=((x2-obs_p_[i].x)*(pow(y1-obs_p_[i].y,2)-R212*(z2-obs_p_[i].z)))/(R212*(pow(y1-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2))*(R212+z2-obs_p_[i].z));
				w112=((x1-obs_p_[i].x)*(pow(y1-obs_p_[i].y,2)-R112*(z2-obs_p_[i].z)))/(R112*(pow(y1-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2))*(R112+z2-obs_p_[i].z));
				w221=((x2-obs_p_[i].x)*(pow(y2-obs_p_[i].y,2)-R221*(z1-obs_p_[i].z)))/(R221*(pow(y2-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2))*(R221+z1-obs_p_[i].z));
				w121=((x1-obs_p_[i].x)*(pow(y2-obs_p_[i].y,2)-R121*(z1-obs_p_[i].z)))/(R121*(pow(y2-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2))*(R121+z1-obs_p_[i].z));
				w211=((x2-obs_p_[i].x)*(pow(y1-obs_p_[i].y,2)-R211*(z1-obs_p_[i].z)))/(R211*(pow(y1-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2))*(R211+z1-obs_p_[i].z));
				w111=((x1-obs_p_[i].x)*(pow(y1-obs_p_[i].y,2)-R111*(z1-obs_p_[i].z)))/(R111*(pow(y1-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2))*(R111+z1-obs_p_[i].z));

				v222=((x2-obs_p_[i].x)*(z2-obs_p_[i].z))/(R222*(pow(y2-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2)));
				v122=((x1-obs_p_[i].x)*(z2-obs_p_[i].z))/(R122*(pow(y2-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2)));
				v212=((x2-obs_p_[i].x)*(z2-obs_p_[i].z))/(R212*(pow(y1-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2)));
				v112=((x1-obs_p_[i].x)*(z2-obs_p_[i].z))/(R112*(pow(y1-obs_p_[i].y,2)+pow(z2-obs_p_[i].z,2)));
				v221=((x2-obs_p_[i].x)*(z1-obs_p_[i].z))/(R221*(pow(y2-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2)));
				v121=((x1-obs_p_[i].x)*(z1-obs_p_[i].z))/(R121*(pow(y2-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2)));
				v211=((x2-obs_p_[i].x)*(z1-obs_p_[i].z))/(R211*(pow(y1-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2)));
				v111=((x1-obs_p_[i].x)*(z1-obs_p_[i].z))/(R111*(pow(y1-obs_p_[i].y,2)+pow(z1-obs_p_[i].z,2)));
				
				G222=-k1*(y2-obs_p_[i].y)/(R222*(R222+x2-obs_p_[i].x))-k2*pow(R222,-1)-k3*(y2-obs_p_[i].y)/(R222*(R222+z2-obs_p_[i].z))-k4*(x2-obs_p_[i].x)/(R222*(R222+z2-obs_p_[i].z))+k5*w222-k6*v222;
				G122=-k1*(y2-obs_p_[i].y)/(R122*(R122+x1-obs_p_[i].x))-k2*pow(R122,-1)-k3*(y2-obs_p_[i].y)/(R122*(R122+z2-obs_p_[i].z))-k4*(x1-obs_p_[i].x)/(R122*(R122+z2-obs_p_[i].z))+k5*w122-k6*v122;
				G212=-k1*(y1-obs_p_[i].y)/(R212*(R212+x2-obs_p_[i].x))-k2*pow(R212,-1)-k3*(y1-obs_p_[i].y)/(R212*(R212+z2-obs_p_[i].z))-k4*(x2-obs_p_[i].x)/(R212*(R212+z2-obs_p_[i].z))+k5*w212-k6*v212;
				G112=-k1*(y1-obs_p_[i].y)/(R112*(R112+x1-obs_p_[i].x))-k2*pow(R112,-1)-k3*(y1-obs_p_[i].y)/(R112*(R112+z2-obs_p_[i].z))-k4*(x1-obs_p_[i].x)/(R112*(R112+z2-obs_p_[i].z))+k5*w112-k6*v112;
				G221=-k1*(y2-obs_p_[i].y)/(R221*(R221+x2-obs_p_[i].x))-k2*pow(R221,-1)-k3*(y2-obs_p_[i].y)/(R221*(R221+z1-obs_p_[i].z))-k4*(x2-obs_p_[i].x)/(R221*(R221+z1-obs_p_[i].z))+k5*w221-k6*v221;
				G121=-k1*(y2-obs_p_[i].y)/(R121*(R121+x1-obs_p_[i].x))-k2*pow(R121,-1)-k3*(y2-obs_p_[i].y)/(R121*(R121+z1-obs_p_[i].z))-k4*(x1-obs_p_[i].x)/(R121*(R121+z1-obs_p_[i].z))+k5*w121-k6*v121;
				G211=-k1*(y1-obs_p_[i].y)/(R211*(R211+x2-obs_p_[i].x))-k2*pow(R211,-1)-k3*(y1-obs_p_[i].y)/(R211*(R211+z1-obs_p_[i].z))-k4*(x2-obs_p_[i].x)/(R211*(R211+z1-obs_p_[i].z))+k5*w211-k6*v211;
				G111=-k1*(y1-obs_p_[i].y)/(R111*(R111+x1-obs_p_[i].x))-k2*pow(R111,-1)-k3*(y1-obs_p_[i].y)/(R111*(R111+z1-obs_p_[i].z))-k4*(x1-obs_p_[i].x)/(R111*(R111+z1-obs_p_[i].z))+k5*w111-k6*v111;

				temp_obs[j] = T0/(4*Pi)*(G222-G122-G212+G112-G221+G121+G211-G111)*forward_model_[j];
			}
		}

		for (int n = 0; n < model_num_; n++){
			obs_p_[i].val += temp_obs[n];
		}
	}

	for (int i = 0; i < obs_num_; i++){
		temp_noise = dist(generator);
		obs_p_[i].val += temp_noise;
		obs_p_[i].dev = noise_dev;
	}
	return 0;
}