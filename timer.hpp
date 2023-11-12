using namespace std;
class timer
{
    public:
    timer(int x,int y,int z,int s);
    void set_work(int wd);
    void set_break(int bd);
    void startsession();
    void endsession(); 
    void clearscreen();
    string menouepilogis();
    void getStatistics();
    
    private:
    int workdur,breakdur,sessionsCompleted,totalWorkTime;
};