#define left_motor 10
#define right_motor 9
#define BLED 3
#define GLED 2
#define RLED 4
#define lsensor 16
#define rsensor 15
#define rmaxSpeed 255
#define lmaxSpeed 255

int lspeed_wheel = lmaxSpeed;
int rspeed_wheel = rmaxSpeed;

int lspeed, rspeed;
int larr[20];
int rarr[20];
int i = 0;
bool lstop = false;
bool rstop = false;

int lcountdown = 2;
int lstate = 1;
int rcountdown = 2;
int rstate = 1;
int lflashcount = 0;
int rflashcount = 0;

void setup() {
    Serial.begin(9600);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(RLED, OUTPUT);
    pinMode(GLED, OUTPUT);
    pinMode(BLED, OUTPUT);
    pinMode(lsensor, INPUT);
    pinMode(rsensor, INPUT);
}

void kickstart()
{
    lstop = false;
    rstop = false;
    digitalWrite(RLED, LOW);
    digitalWrite(BLED, LOW);
    analogWrite(left_motor, 255);
    analogWrite(right_motor, 255);
}
void slowdown(){
    analogWrite(left_motor, lspeed_wheel);
    analogWrite(right_motor, rspeed_wheel);
    if(!lstop)
        lspeed_wheel-=1;
    if(!rstop)
        rspeed_wheel-=1;
<<<<<<< HEAD
    Serial.print(lspeed_wheel);
    Serial.print(' ');
    Serial.println(rspeed_wheel);
    Serial.print(' ');
=======
>>>>>>> b794a059c2c46e71487a5c64d5b3b549d4d77b3e
}

void check (int* arr, int LorR){
    int first = arr[0];
    int j = 0;
    for(j; j < 20;j++){
        if (abs(arr[j]-first) > 10){
            break;
        }
    }
    if(j == 20){
        if(LorR == 0){
            lstop = true;
        }
        else{
            rstop = true;
        }
    }
}

void recordNewData(){
    lspeed = analogRead(lsensor);
    rspeed = analogRead(rsensor);
    /*Serial.print(lspeed);
    Serial.print(' ');
    Serial.print(rspeed);
    Serial.print(' ');*/
    if (i<20){
        larr[i] = lspeed;
        rarr[i] = rspeed;
        i++;
    }
    else{
        for (int j = 0; j < 19; j++){
            larr[j] = larr[j+1];
            rarr[j] = rarr[j+1];
        }
        larr[19] = lspeed;
        rarr[19] = rspeed;
    }
}


void loop(){
    slowdown();
    if (!lstop || !rstop){
        recordNewData();
    }
    if(!lstop && i == 20){
        check(larr, 0);
    }
    if(!rstop && i == 20){
        check(rarr, 1);
    }
    /*Serial.print(' ');
    Serial.print(lstop);
    Serial.print(' ');
    Serial.print(rstop);
<<<<<<< HEAD
    Serial.println();
    //flashled();
    delay(50);
}
=======
    Serial.println();*/
    if(lstop){
        if (lcountdown == 0){
            lstate = !lstate;
            digitalWrite(BLED, lstate);
            lcountdown = 1;
            lflashcount++;
        }
        else{
            digitalWrite(BLED, lstate);
            lcountdown--;
        }
    }
    if(rstop){
        if (rcountdown == 0){
            rstate = !rstate;
            digitalWrite(RLED, rstate);
            rcountdown = 1;
            rflashcount++;
        }
        else{
            digitalWrite(RLED, rstate);
            rcountdown--;
        }
    }
    if(lflashcount >= 30 && rflashcount >=30){
        kickstart();
    }
    delay(45);
}
>>>>>>> b794a059c2c46e71487a5c64d5b3b549d4d77b3e
