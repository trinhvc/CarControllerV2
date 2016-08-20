#ifndef LED_H
#define LED_H


class Led
{
    private:
        int _status[10];
    public:
        Led()
        {
            for(int i = 0; i < 10; i++)
            {
                _status[i] = 0;
            }
        }

        static Led& getInstance()
        {
            static Led instance;
            return instance;
        }

        void setReady(int val) {}
        void setData(int val) {}
        void setEncoder1(int val) {}
        void setEncoder2(int val) {}
        void setMotor1(int val) {}
        void setMotor2(int val) {}
        void setSonar1(int val) {}
        void setSonar2(int val) {}
        void setSonar3(int val) {}
        void setSonar4(int val) {}

};

#endif // LED_H
