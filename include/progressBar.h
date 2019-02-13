#include "scenes/scene.h"
#include <renderTask.h>
#include <thread>
#include <vector>

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
class ProgressBar {
  private:
    std::vector<int>* taskCounters;
    bool isRunning = true;
    int progress = 0;
    int stepSize;
    int totalTasks;
    int steps = 20;
    void update();
    std::thread* progressThread;

  public:
    void start();
    void stop();
    ProgressBar(std::vector<int>*, int);
};
#endif
