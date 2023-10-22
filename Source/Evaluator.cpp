#include "../Headers/Evaluator.h"
#include <iostream>

#include <iomanip>
#include <map>

std::vector<TransmissionLog> Evaluator::logs;

void Evaluator::Evaluate()
{
    EvaluationTicket correctTicket, incorrectTicket;
    map<int, int> noiseCounts;

    for (const auto& log : logs)
    {
        EvaluationTicket& ticketToUse = log.GetVerification() == EVerification::Incorrect ? incorrectTicket : correctTicket;
        ticketToUse.TicketLog(log);

        noiseCounts[log.GetNoiseCount()]++;
    }
    double totalCount = correctTicket.TotalCount + incorrectTicket.TotalCount;

    double percentCorrect = correctTicket.TotalCount / (float)logs.size() * 100;
    double retransmissionPercentage = correctTicket.MessagesRetransmittedCount / totalCount * 100.0;
    double percentCorrected =  (float)correctTicket.MessagesRetransmittedCount / correctTicket.TotalCount * 100;
    double retransmissionCount = correctTicket.MessagesRetransmittedCount + incorrectTicket.MessagesRetransmittedCount;

    cout << fixed << setprecision(2);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Stats:" << endl;
    cout << "* Incorrect: " << incorrectTicket.TotalCount << ", Correct: " << correctTicket.TotalCount << endl;
    cout << "* Average Transmission Count of Incorrect Messages: " << incorrectTicket.GetTransmissionAverage()
         << ", Average Transmission Count of Correct Messages: " << correctTicket.GetTransmissionAverage() << endl;
    cout << "* "
         << percentCorrect << "% of messages were received correctly, "
         << retransmissionPercentage << "% of messages required retransmission, ie, the checksum failed on first transmission. " << endl;
    cout << "* " << incorrectTicket.TotalCount / retransmissionCount * 100 << "% of initially incorrect messages remained incorrect but were falsely identified as correct." <<
            endl;
    cout << "* On average, incorrect messages required "
         << correctTicket.RetranmissionAverage()
         << " attempts to become correct. Messages were incorrectly marked as correct after " << incorrectTicket.RetranmissionAverage() << " retransmissions." << endl;
    cout << fixed << setprecision(4);
    cout << "* The correct payload was delivered, but marked as incorrect because only the ack bit was flipped " << correctTicket.AckFlippedCount << " times, an occurrence rate of "
         << (float)correctTicket.AckFlippedCount / (correctTicket.TotalCount  + correctTicket.TotalCount) << "%" << endl;

    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Noise Occurrence Spread:" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < noiseCounts.size() - 1; i++)
    {
        cout << "* ";
        cout << noiseCounts[i] << " messages (" << noiseCounts[i] / totalCount * 100 << "%) were flipped " << i << " times. " << endl;
    }
}
