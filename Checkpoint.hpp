#pragma once

class Checkpoint
{
    public:
        float distance;
        int checkpointNo;
        void updateCheckpoint();
        bool checkpointReached();
};