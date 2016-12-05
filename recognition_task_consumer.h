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

#include <opencv2/core.hpp>

#include "FaceRecognitionQueue.h"
#include "tasksMutex.h"

struct RecognitionTaskConsumer {
    
    FaceRecognitionQueue &recognitionQueue;
    
    RecognitionTaskConsumer(FaceRecognitionQueue &recognitionQueue)
        : recognitionQueue(recognitionQueue) {
    }

    void operator()(){
        mutex mtx;
        unique_lock<mutex> lock(mtx);
        std::printf("Consumer running\n");
        while ( recognitionQueue.isRunning() ) {
            
            recognitionQueue.lockQueue();
            if ( recognitionQueue.keepRunning() ){
                
                cv::Mat face = recognitionQueue.pop();
                recognitionQueue.unlockQueue();
                
                recognitionQueue.getRecognizer().recognize(face);
                
            } else {
                recognitionQueue.unlockQueue();
                TasksMutex::condition.wait( lock );
            }
        }
    }
    
};


#endif /* RECOGNITION_TASK_ */

