#ifndef globals_h
#define globals_h

int debugging_enabled=0;

bool debug_sense=true;
bool debug_drive=false;
bool debug_listening=false;
bool debug_behaviors=false;

#define s_bot 0
#define m_green_bot 1
#define m_grey_bot 2

#define WDT_TIMEOUT 2
int flag[]={0,0};

bool sensors_ON=false;
bool drive_ON=false;

static int currentBot=m_green_bot;

struct myRobot{
    bool flip_IR;
    bool flip_sense;
    bool flip_motor;
    bool flip_rotation;
    bool disable_front_sensors;
    int roam;
};

myRobot theRobot[3]={
{false,true,true,false,false,180},//small
{true,true,false,false,true,200},//m_green
{false,true,false,true,true,180}//m_grey
};

float agility=0.05;
int decelerate_rate=20;
int accelerate_rate=50;
int max_speed=255;
int roam_speed=theRobot[currentBot].roam;
float dead_band=0.5;
bool flip_IR_follow_response=theRobot[currentBot].flip_IR;//false;//true for m_green
bool flip_sensor_response=theRobot[currentBot].flip_sense;//false for small, true for m_green
bool flip_motor_direction=theRobot[currentBot].flip_motor;//true for small
bool flip_rotation_response=theRobot[currentBot].flip_rotation;//true for mgrey
bool disable_front=theRobot[currentBot].disable_front_sensors;

#define F_GRD_LO 127
#define F_GRD_HI 256
#define F_TRI_LOL 64
#define F_TRI_HI 127
#define F_TRI_LOR 190
#define F_REV_GRD_LO 1
#define F_REV_GRD_HI 127



#endif