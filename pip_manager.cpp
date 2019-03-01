#include <iostream>
#include <fstream>

//defines constant values for the min/max pid
#define MIN_PID 300
#define MAX_PID 5000

using namespace std;

// Constant decleration for TRUE and FALSE (1/0)
// const is used to initialize the variables so that its state wont be ultered
const int TRUE=1, FALSE =0;


// difference of the max and min pids being stored in a variable.
 int value_of_Pids = MAX_PID-MIN_PID;

//  Data Structure with two int member types
//  Pointer structure
struct pid_table{
    int PID;
    int empty_pid;
}*pid_table;

//calling of functions /*function prototypes*/
int allocate_map();
void release_pid(int pid);
int allocate_pid();

//function prototype for pid calculation and output statement to console.
void ID_mapper();

int main(){
    
    // calling of the function
    allocate_map();
    
    //function call for ID_mapper, makes process IDs and then prints them to console
    ID_mapper();
}


int allocate_map(){
    
    // We take the size of the data structure we just created
    int size = sizeof(struct pid_table);
    
    
    //calloc functions take 2 parameters, the value of pid and the table size.
    pid_table=(struct pid_table *)calloc((value_of_Pids+1), size);
    
    //returns -1 if unsuccessful
    if(pid_table==0)
        return -1;
    
    // the first element will be the miniumum value of the PID possible
    pid_table[0].PID=MIN_PID;
    // Is pId[i] empty? If true, then TRUE.
    pid_table[0].empty_pid=TRUE;
    
    // let's fill the whole range (value_of_Pids) with TRUE
    //make room for all the available pids by setting them to TRUE
    for(int i=0; i<value_of_Pids+1; i++){
        pid_table[i].PID=pid_table[i-1].PID+1;
        pid_table[i].empty_pid=TRUE;
    }
    
    // return 1 if successful
    return 1;
}

//release_pid function takes pid of type int as a parameter and checks if the pid exist or not and if its in the declared range
void release_pid(int pid){
    
    // If the range is 0 (difference between MAX and MIN), then exit
    if(pid_table==0){
        cout<<"PID Range is 0. Exiting"<<endl;
        return;
    }
    
    
    //check for the pid that is passed as a parameter to the function.
    //if is less than the min or bigger than the max, it gives an error message
    if(pid<MIN_PID || pid >MAX_PID){
        cout<<"ERROR! PID is out of Range"<<endl;
        return;
    }
    
    
    // check for a situation where by the pid is empty
    if(pid_table[pid-MIN_PID].empty_pid==TRUE){
        cout<< "PID " << pid << " is already released "<<endl;
        return;
    }
    
    // If there aren't any unexpected occurance, then this else statement executes
    else{
    cout<<"Pid "<<pid<<" is being released "<<endl;
        pid_table[pid-MIN_PID].empty_pid=TRUE;}
    
}

//in this function, pids get allocated.
int allocate_pid(){
    
    // In an instance where we make used all the possible pids, (min=max)
    // Exit and return -1
    if(value_of_Pids==0){
        cout<<"PID range is 0. Program Exiting"<<endl;
        return -1;
    }
    
    // number_of_pid will be our return int, when all else fails
    int number_of_pid =-1;
    
    // 0 and 1 ranges were covered, all else are run through this loop
    if(value_of_Pids>1){
        
        // for i=0, size of our data structure
        for(int i=0;i<sizeof(struct pid_table);i++){
            
            //this if statement checks for taken pid (pid_table[i].empty_pid==TRUE(1)) and the clears them by setting pid_table[i].empty_pid==FALSE(1) then it sets a new value to the Pid but adding the index location to the min pid
            if(pid_table[i].empty_pid==TRUE){
                pid_table[i].empty_pid=FALSE;
                number_of_pid = i + MIN_PID;
                break;
            }
        }
    }
    
    // If all PID are already filled, return -1
    if(number_of_pid==-1){
        cout<<"Unable to allocate PID. ALL PID ARE FULL"<<endl;
    }
    
    // if everything fails, return number_of_pid (should be -1 if everything failed)
    return number_of_pid;
}

//this function maps the IDs to each processes
void ID_mapper(){
    
    //function call for allocate_map
    allocate_map();
    
    int pid;
    
    // starts making ID for processes
    if((pid=allocate_pid())!=-1){   // 0 gets added to pid, min pid is 300, 300+0=300
        cout<<"New Process ID: "<<pid<<endl; //pid=300
    }
    
    if((pid=allocate_pid())!=-1){   // 1 gets added to pid, min pid is 300, 300+1=301
        cout<<"New Process ID: "<<pid<<endl;//pid=301
    }
    
    if((pid=allocate_pid())!=-1){   // 2 gets added to pid, min pid is 300, 300+2=302
        cout<<"New Process ID: "<<pid<<endl;//pid=302
    }
    
    if((pid=allocate_pid())!=-1){   // 3 gets added to pid, min pid is 300, 300+3=303
        cout<<"New Process ID: "<<pid<<endl;//pid=303
    }
    
    if((pid=allocate_pid())!=-1){   // 4 gets added to pid, min pid is 300, 300+4=304
        cout<<"New Process ID: "<<pid<<endl;//pid=304
    }
    
    if((pid=allocate_pid())!=-1){   // 5 gets added to pid, min pid is 300, 300+5=305
        cout<<"New Process ID: "<<pid<<endl;}//pid =305
    
    // release the previous PID
    // will not work if the previous PID went over the MAX and returned -1
    release_pid(pid);

   // Make ID for the next process
   // Should be the same PID that we just released
    if((pid=allocate_pid())!=-1){ // 0 gets added to pid, min pid is 305, 305+0=305
        cout<<"New Process ID: "<<pid<<endl; //pid=305
    }
    
}





