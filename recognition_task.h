/* 
 * File:   recognition_task.
 * Author: viniciusas
 *
 * Created on 28 de Novembro de 2016, 00:04
 */

#ifndef RECOGNITION_TASK_
#define RECOGNITION_TASK_

#include <mutex>
using namespace std;

#include "FaceRecognition.h"
#include "tasksMutex.h"

struct RecognitionTask {
    
    FaceRecognition &recognition;
    
    RecognitionTask(FaceRecognition &recognition)
        : recognition(recognition) {
    }

    void operator()(){
        mutex mtx;
        unique_lock<mutex> lock(mtx);
        while ( recognition.isRunning() ) {
            
            recognition.lockQueue();
            if ( recognition.keepRunning() ){
                
                Mat face = recognition.pop();
                recognition.unlockQueue();
                
                recognition.recognize(face);
                
            } else {
                recognition.unlockQueue();
                TasksMutex::condition.wait( lock );
            }
        }
    }
    
};


#endif /* RECOGNITION_TASK_ */

