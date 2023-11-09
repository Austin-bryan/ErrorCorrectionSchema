#pragma once
#include <vector>

#include "../Headers/TransmissionLog.h"

class Evaluator
{
public:
    static void AddLog(const TransmissionLog& log) { logs.push_back(log); }
    static void Evaluate();

    static double Percentage;
    static string ByteMethod;
    static int IterationCount;
private:
    // This totals all values across all logs. Two of these are used, one for correct messages and one for incorrect messages
    struct EvaluationTicket
    {
        int TotalCount                 = 0;
        int AckFlippedCount            = 0;
        int TransmissionCount          = 0;
        int RetransmittedCount         = 0;
        int SingleTransmitCount        = 0;
        int MessagesRetransmittedCount = 0;

        float RetranmissionAverage()   const { return MessagesRetransmittedCount == 0 ? 0 : RetransmittedCount / (float)MessagesRetransmittedCount; }
        float GetTransmissionAverage() const { return (float)TransmissionCount / TotalCount; }

        // Takes a log and adds its values to the totals
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

            if (log.GetWasAckFlipped())
                AckFlippedCount++;
        }
    };
    static std::vector<TransmissionLog> logs;
};
