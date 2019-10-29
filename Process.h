#ifndef PROCESS_H
#define PROCESS_H

class Process
{
  private:
    int id;
    int arrival;
    int burst;
    int priority;

    void set_id(int id);
    void set_arrival(int arrival);
    void set_priority(int priority);


  public:
    Process();
    Process(int id, int arrival, int burst, int priority): 
	    id(id), arrival(arrival), burst(burst), priority(priority){}
    int get_id() const;
    int get_arrival() const;
    int get_burst() const;
    int get_priority() const;

    void set_burst(int burst);
    void exchange(Process &process);
    ~Process(){};


};
#endif
