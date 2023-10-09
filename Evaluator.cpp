#include "Evaluator.h"

#include <iomanip>

std::vector<TransmissionLog> Evaluator::logs;

void Evaluator::Evaluate()
{
     EvaluationTicket correctTicket, incorrectTicket; 

    for (const auto& log : logs)
    {
        EvaluationTicket& ticketToUse = log.GetVerification() == EVerification::Incorrect ? incorrectTicket : correctTicket;
        ticketToUse.TicketLog(log);
    }

    float percentCorrect = correctTicket.TotalCount / (float)logs.size() * 100;
    float percentCorrected = correctTicket.MessagesRetransmittedCount / (float)(correctTicket.MessagesRetransmittedCount + incorrectTicket.MessagesRetransmittedCount) * 100;

    cout << fixed << setprecision(2);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n* Stats:" << endl;
    cout << "* Incorrect: " << incorrectTicket.TotalCount << ", Correct: " << correctTicket.TotalCount << endl;
    cout << "* Average Transmission Count of Incorrect Messages: " << incorrectTicket.GetTransmissionAverage() << ", Average Transmissions Count of Correct Messages: " << correctTicket.GetTransmissionAverage() << endl;
    cout << "* "
         << percentCorrect << "% Correct, "
         << "Correct " << percentCorrected << "% of messages that required retransmission. "
         << "\n* The remaining " << 100 - percentCorrected << "% of initially incorrect messages remained incorrect but were falsely identified as correct." <<
            endl;

    cout << "* On average, incorrect messages required "
         << correctTicket.RetranmissionAverage()
         << " attempts to become correct and were incorrectly marked as correct after " << incorrectTicket.RetranmissionAverage() << " retransmissions." << endl;
    cout << fixed << setprecision(4);
    cout << "* The correct payload was delivered, but marked as incorrect because only the ack bit was flipped " << correctTicket.AckFlippedCount << " times, an occurrence rate of "
         << (float)correctTicket.AckFlippedCount / (correctTicket.TotalCount  + correctTicket.TotalCount) << "%" << endl;
}
