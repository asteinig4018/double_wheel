

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
public:
    MController(/* args */);
    ~MController();
    void both_stop();
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


void setup(){

    Serial.begin(115200);

    MController mcontroller;
    
    mcontroller.both_stop();

}


void loop(){



}