﻿#pragma once
#include <vector>

#include "../Headers/TransmissionLog.h"

class Evaluator
{
public:
    static void AddLog(const TransmissionLog& log) { logs.push_back(log); }
    static void Evaluate();

private:
    struct EvaluationTicket
    {
        int TotalCount                 = 0;
        int AckFlippedCount            = 0;
        int TransmissionCount          = 0;
        int RetransmittedCount         = 0;
        int SingleTransmitCount        = 0;
        int MessagesRetransmittedCount = 0;

        float RetranmissionAverage()   const { return RetransmittedCount / (float)MessagesRetransmittedCount; }
        float GetTransmissionAverage() const
        {
            cout << endl << TransmissionCount << " / " << TotalCount << " = " << (float)TransmissionCount / TotalCount << endl;
            return (float)TransmissionCount / TotalCount;
        }
        void TicketLog(const TransmissionLog& log)
        {
            TotalCount++;
            // if (log.WasRetransmitted())
                // cout << "ID: " << log.ID << ", tCount: " << log.GetTransmissionCount() << ", " << log.GetVerification() << endl;
            TransmissionCount += log.GetTransmissionCount();

            if (log.WasRetransmitted())
            {
                MessagesRetransmittedCount++;
                RetransmittedCount += log.GetTransmissionCount(); 
            }
            else SingleTransmitCount++;

            if (log.GetWasAckFlipped())
                AckFlippedCount++;
            
            // if (log.WasRetransmitted())
            // {
            //     MessagesRetransmittedCount += log.
            // }
        }
    };
    static std::vector<TransmissionLog> logs;
};
