#include <mutex>
#include <utility>

class Semafor {
    int clock;        
    int count;        
    std::mutex mutex; 

public:
    Semafor(int x) {
        clock = 0;   
    	count = x;  
    };

    std::pair<int, int> Enter() {  
        while (true) {            

           
           std::lock_guard<std::mutex> lock(mutex);

            if (count != 0) { 
               
               
                return std::make_pair(clock++, --count);
            }
        }
    }

    std::pair<int, int> Leave() {  

       
        std::lock_guard<std::mutex> lock(mutex);

        return std::make_pair(clock++, ++count);
    }
};
