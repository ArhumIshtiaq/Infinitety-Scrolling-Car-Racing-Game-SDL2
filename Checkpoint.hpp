#pragma once

class Checkpoint
{
    float distance;
    int checkpointNo;
    void updateCheckpoint();
    bool checkpointReached();
};