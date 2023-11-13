#include <string>

using namespace std;

class timer
{
    public:
    timer(int x,int y,int z,int s);
    void menouepilogis();

    private:
    void startsession();
    void endsession(); 
    void clearscreen();
    void getStatistics();
    void getworkdur();
    void getbreakdur();
    void workcounting();
    void breakcounting();
    bool checkifnumber(string n);

    private:
    int workdur,breakdur,sessionsCompleted,totalWorkTime;
};