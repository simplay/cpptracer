#include <chrono>
#include <iostream>
#include "progressBar.h"

ProgressBar::ProgressBar(std::vector<int>* taskCounters, int totalTasks)
  : taskCounters(taskCounters), totalTasks(totalTasks) {
    this->stepSize = totalTasks / steps;
  }

void ProgressBar::update() {
  while (isRunning) {
    int completedTaskCount = 0;
    for (auto& n : (*taskCounters)) {
      completedTaskCount += n;
    }

    int tmpProgress = (completedTaskCount / stepSize) + 1;
    int diff = tmpProgress - progress;
    std::cout << "";
    for (int k = 0; k < diff; k++) {
      std::cout << "* ";
    }
    std::cout << std::flush;
    progress = tmpProgress;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void ProgressBar::start() {
  this->progressThread = new std::thread(&ProgressBar::update, this);
}

void ProgressBar::stop() {
  isRunning = false;
  progressThread->join();
  std::cout << std::endl;
}
