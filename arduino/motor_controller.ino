

const int motor1_dir1_pin = A0;
const int motor1_dir2_pin = A1;

const int motor2_dir1_pin = A2;
const int motor2_dir2_pin = A3;

enum eDirection{
    forward,
    reverse,
    stopped
};

class MController
{
private:
    /* data */
    eDirection ldirection;
    eDirection rdirection;
    int lcurrSpeed;
    int rcurrSpeed;

public:
    MController(/* args */);
    ~MController();
    void both_stop();
    void set_ldirection(eDirection direction);
    void set_rdirection(eDirection direction);
    void set_direction(eDirection direction);
    void incr_left(int numIncr);
    //void incr_right();
    //void incr_both();
    int get_lSpeed();
    void decr_left(int numDecr);
    //void decr_right(int numDecr);
    //void decr_both(int numDecr);
};

MController::MController(/* args */)
{
    pinMode(motor1_dir1_pin, OUTPUT);
    pinMode(motor1_dir2_pin, OUTPUT);
    pinMode(motor2_dir1_pin, OUTPUT);
    pinMode(motor2_dir2_pin, OUTPUT);

    ldirection = stopped;
    rdirection = stopped;
    
}

MController::~MController()
{
}

void MController::both_stop(){
    analogWrite(motor1_dir1_pin, 0);
    analogWrite(motor1_dir2_pin, 0);
    analogWrite(motor2_dir1_pin, 0);
    analogWrite(motor2_dir2_pin, 0);

    ldirection = stopped;
    rdirection = stopped;
}

void MController::set_ldirection(eDirection direction){
    ldirection = direction;
}

void MController::set_rdirection(eDirection direction){
    rdirection = direction;
}

void MController::set_direction(eDirection direction){
    set_ldirection(direction);
    set_rdirection(direction);
}

void MController::incr_left(int numIncr){
    if(ldirection == forward){
        //forward
        lcurrSpeed += numIncr;
        if(lcurrSpeed > 255){
            lcurrSpeed = 255;
        }
        analogWrite(motor1_dir1_pin, lcurrSpeed);
        analogWrite(motor1_dir2_pin, 0);
    }
    else if(ldirection == reverse){
        //reverse
        lcurrSpeed += numIncr;
        if(lcurrSpeed > 255){
            lcurrSpeed = 255;
        }
        analogWrite(motor1_dir1_pin, 0);
        analogWrite(motor1_dir2_pin, lcurrSpeed);
    }
    else{
        //stopped
        analogWrite(motor1_dir1_pin, 0);
        analogWrite(motor1_dir2_pin, 0);
    }
}

int MController::get_lSpeed(){
    return lcurrSpeed;
}

void MController::decr_left(int numDecr){
    if(ldirection == forward){
        //forward
        lcurrSpeed -= numDecr;
        if(lcurrSpeed < 0){
            lcurrSpeed = 0;
        }
        analogWrite(motor1_dir1_pin, lcurrSpeed);
        analogWrite(motor1_dir2_pin, 0);
    }
    else if(ldirection == reverse){
        //reverse
        lcurrSpeed -= numDecr;
        if(lcurrSpeed < 0){
            lcurrSpeed = 0;
        }
        analogWrite(motor1_dir1_pin, 0);
        analogWrite(motor1_dir2_pin, lcurrSpeed);
    }
    else{
        //stopped
        analogWrite(motor1_dir1_pin, 0);
        analogWrite(motor1_dir2_pin, 0);
    }
}

MController mcontroller;

void setup(){

    Serial.begin(115200);
    
    mcontroller.both_stop();
    mcontroller.set_direction(forward);

    while(!Serial){
        ;//wait for serial
    }

}


void loop(){
    mcontroller.incr_left(10);
    delay(1000);
    for(int i = 0; i < 25; i ++ ){
        mcontroller.incr_left(10);
        delay(1000);
        Serial.println(mcontroller.get_lSpeed());
    }
    
    delay(5000);
    for(int i = 0; i < 25; i ++){
        mcontroller.decr_left(10);
        delay(1000);
        Serial.println(mcontroller.get_lSpeed());
    }
    delay(10000);

}