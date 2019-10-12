#include "progressBar.h"
#include <chrono>
#include <iostream>
#include "logger.h"

ProgressBar::ProgressBar(std::vector<int>* taskCounters, int totalTasks)
    : taskCounters(taskCounters) {
  this->stepSize = std::max(totalTasks / progressIntervals, 1);
}

void ProgressBar::update() {
  Logger().log("Progress: ");
  while (isRunning) {
    int completedTaskCount = 0;
    for (auto& n : (*taskCounters)) {
      completedTaskCount += n;
    }

    int tmpProgress = (completedTaskCount / stepSize) + 1;
    int diff = tmpProgress - progress;
    Logger().log("");

    for (int k = 0; k < diff; k++) {
      Logger().log("* ");
    }
    std::cout << std::flush;
    progress = tmpProgress;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void ProgressBar::start() { this->progressThread = new std::thread(&ProgressBar::update, this); }

void ProgressBar::stop() {
  isRunning = false;
  progressThread->join();
  Logger().log("\n");
}
