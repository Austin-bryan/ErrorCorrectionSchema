#pragma once
#include <vector>

#include "TransmissionLog.h"

class Evaluator
{
public:
    static void AddLog(const TransmissionLog& log) { logs.push_back(log); }
    static void Evaluate();

private:
    struct EvaluationTicket
    {
        int TotalCount = 0;
        int TransmissionCount = 0;
        int RetransmittedCount = 0;
        int SingleTransmitCount = 0;
        int MessagesRetransmittedCount = 0;

        float GetTransmissionAverage() const { return static_cast<float>(TransmissionCount) / TotalCount; }
        float RetranmissionAverage() const { return RetransmittedCount / (float)MessagesRetransmittedCount; }
        void TicketLog(const TransmissionLog& log)
        {
            TotalCount++;
            TransmissionCount += log.GetTransmissionCount();

            if (log.WasRetransmitted())
            {
                MessagesRetransmittedCount++;
                RetransmittedCount += log.GetTransmissionCount(); 
            }
            else SingleTransmitCount++;
            // if (log.WasRetransmitted())
            // {
            //     MessagesRetransmittedCount += log.
            // }
        }
    };
    static std::vector<TransmissionLog> logs;
};
