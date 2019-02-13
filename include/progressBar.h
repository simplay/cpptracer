#include "scenes/scene.h"
#include <renderTask.h>
#include <thread>
#include <vector>

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
class ProgressBar {
  private:
    std::vector<int>* taskCounters;
    int totalTasks;

    bool isRunning = true;
    int progress = 0;
    int progressIntervals = 20;
    int stepSize;
    std::thread* progressThread;

    void update();

  public:
    void start();
    void stop();
    ProgressBar(std::vector<int>*, int);
};
#endif
