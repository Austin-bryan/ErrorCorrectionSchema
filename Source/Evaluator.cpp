#include "../Headers/Evaluator.h"

#include <iostream>
#include <iomanip>
#include <map>

std::vector<TransmissionLog> Evaluator::logs;
double Evaluator::Percentage;
string Evaluator::ByteMethod;
int Evaluator::IterationCount;

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

    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "* Configuration: " << endl;
    cout << "* " << endl;
    cout << "* Error Percentage: " << Percentage << "%" << endl;
    cout << "* Iteration count: " << IterationCount << endl;
    cout << "* Byte method: " << ByteMethod << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;

    cout << fixed << setprecision(4);
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Stats:" << endl;
    cout << "* " << endl;
    cout << "* Incorrect: " << incorrectTicket.TotalCount << ", Correct: " << correctTicket.TotalCount << endl;
    cout << "* Average Transmission Count of Incorrect Messages: " << incorrectTicket.GetTransmissionAverage() << endl;
    cout << "* Average Transmission Count of Correct Messages: " << correctTicket.GetTransmissionAverage() << endl;
    cout << "* " << endl;
    cout << "* " << percentCorrect << "% of messages were received correctly " << endl;
    cout << "* " << retransmissionPercentage << "% of messages required retransmission. " << endl;
    cout << "* " << endl;
    cout << "* " << (retransmissionCount < 0.001 ? 1 : incorrectTicket.TotalCount / retransmissionCount) * 100 << "% of incorrect messages were falsely identified as correct." << endl;
    cout << "* There were " << transmissionCount << " transmissions; a 1 to " << transmissionCount / totalCount  << " message-transmission ratio." << endl;
    cout << "* Incorrect messages averaged " << correctTicket.RetranmissionAverage() << " attempts to be corrected." << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Noise Occurrence Spread:" << endl;
    cout << "* " << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < noiseCounts.size() - 1; i++)
    {
        cout << "* ";
        cout << noiseCounts[i] << " messages (" << noiseCounts[i] / totalCount * 100 << "%) were flipped " << i << " times. " << endl;
    }
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
}
