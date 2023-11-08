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
    double totalCount               = correctTicket.TotalCount + incorrectTicket.TotalCount;
    double percentCorrect           = correctTicket.TotalCount / (float)logs.size() * 100;
    double retransmissionPercentage = correctTicket.MessagesRetransmittedCount / totalCount * 100.0;
    double percentCorrected         =  (float)correctTicket.MessagesRetransmittedCount / correctTicket.TotalCount * 100;
    double retransmissionCount      = correctTicket.MessagesRetransmittedCount + incorrectTicket.MessagesRetransmittedCount;
    int transmissionCount           = correctTicket.TransmissionCount + incorrectTicket.TransmissionCount;

    cout << fixed << setprecision(4);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Stats:" << endl;
    cout << "* Incorrect: " << incorrectTicket.TotalCount << ", Correct: " << correctTicket.TotalCount << endl;
    cout << "* Average Transmission Count of Incorrect Messages: " << incorrectTicket.GetTransmissionAverage()
         << ". Average Transmission Count of Correct Messages: " << correctTicket.GetTransmissionAverage() << endl;
    cout << "* " << percentCorrect << "% of messages were received correctly, " << retransmissionPercentage << "% of messages required retransmission. " << endl;
    cout << "* " << (retransmissionCount < 0.001 ? 1 : incorrectTicket.TotalCount / retransmissionCount) * 100 << "% of initially incorrect messages remained incorrect but were falsely identified as correct." << endl;
    cout << "* There was a total of " << transmissionCount << " transmissions, which is a 1 to " << transmissionCount / totalCount  << " message-transmission ratio." << endl;
    cout << "* On average, incorrect messages required " << correctTicket.RetranmissionAverage() << " attempts to become correct." << endl;

    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Noise Occurrence Spread:" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < noiseCounts.size() - 1; i++)
    {
        cout << "* ";
        cout << noiseCounts[i] << " messages (" << noiseCounts[i] / totalCount * 100 << "%) were flipped " << i << " times. " << endl;
    }
}
