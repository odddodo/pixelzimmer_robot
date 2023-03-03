#ifndef globals_h
#define globals_h

int debugging_enabled=1;

bool debug_sense=true;
bool debug_drive=false;
bool debug_listening=false;
bool debug_behaviors=false;

bool sensors_ON=false;
bool drive_ON=false;

float agility=0.05;
int decelerate_rate=20;
float dead_band=0.5;

#define F_GRD_LO 127
#define F_GRD_HI 256
#define F_TRI_LOL 64
#define F_TRI_HI 127
#define F_TRI_LOR 190
#define F_REV_GRD_LO 1
#define F_REV_GRD_HI 127



#endif