#ifndef MAPPING_H
#define MAPPING_H

//#include <iostream>
//using namespace std;
/*
Pin    gpio    use for
7      4       TRIGGER2
11     17      ECHO2
13     27      TRIGGER1
15     22      ECHO1
29     5       ECHO3
31     6       ECHO4
33     13      TRIGGER4
35     19      TRIGGER3
37     26      LIGHT
12     18      ENCODER1
16     23      BRIDGE1_IN1
18     24      BRIDGE1_IN2
22     25      BRIDGE1_ENABLE
32     12      BRIDGE2_IN1
36     16      BRIDGE2_IN2
38     20      BRIDGE2_ENABLE
40     21      ENCODER2

*/


const int TRIGGER1 = 27;
const int ECHO1 = 22;
const int TRIGGER2 = 4;
const int ECHO2 = 17;
const int TRIGGER3 = 19;
const int ECHO3 = 5;
const int TRIGGER4 = 13;
const int ECHO4 = 6;
const int ENCODER1 = 18;
const int ENCODER2 = 21;
const int BRIDGE1_ENABLE = 25;
const int BRIDGE1_IN1 = 23;
const int BRIDGE1_IN2 = 24;
const int BRIDGE2_ENABLE = 20;
const int BRIDGE2_IN1 = 12;
const int BRIDGE2_IN2 = 16;

const double PI = 3.14159265;

const int MIN_PING = 10 * 58 * 1000; // (us)
const int MAX_PING = 20 * 58 * 1000;
#endif // MAPPING_H
