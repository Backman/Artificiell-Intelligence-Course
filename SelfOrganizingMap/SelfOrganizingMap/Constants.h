#pragma once
#include "Utility.h"

const int CELL_SIZE = 5;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

const int NUM_EPOCHS = 1000;

const int MAX_TRAINING_SETS = 10;
const int MIN_TRAINING_SETS = 4;

const float START_LEARNING_RATE = 0.1;
const float START_RADIUS = Utility::max(WINDOW_WIDTH, WINDOW_HEIGHT) / 2;