int float_switch_one = 2;
int *p = &float_switch_one;
void setup(){Serial.begin(9600);
pinMode(*p,OUTPUT);}
void loop(){Serial.println(digitalRead(*p));}
