#include <gtest/gtest.h>
#include "progressBar.h"

#include <vector>

TEST(ProgressBar, can_be_run) {
  std::vector<int>* taskCounters = new std::vector<int>(1);

  ProgressBar progressbar(taskCounters, 1);
  progressbar.start();
  progressbar.stop();
}
