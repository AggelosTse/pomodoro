using namespace std;

class timer
{
    public:
    timer(int x,int y,int z,int s);  //im using these functions as public, because main has access to them.
    void menouepilogis();

    private:                    //these functions are private because they are used only within the class.
    void startsession();
    void endsession(); 
    void clearscreen();
    void getStatistics();
    void getworkdur();
    void getbreakdur();                                                         
    void workcounting();
    void breakcounting();
    int workdur,breakdur,sessionsCompleted,totalWorkTime;  //class variables are also private for better encapsulation.
};