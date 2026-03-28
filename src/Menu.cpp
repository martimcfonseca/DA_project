#include <iostream>
#include <limits>
#include "Menu.h"
#include "MaxFlow.h"
#include "RiskAnalysis.h"

void printMenu() {
    std::cout << "\n==========================" << endl;
    std::cout << "  Conference Review Tool  "   << endl;
    std::cout << "==========================" << endl;
    std::cout << "1. Carregar ficheiro CSV"      << endl;
    std::cout << "2. Listar submissoes"          << endl;
    std::cout << "3. Listar revisores"           << endl;
    std::cout << "4. Ver parametros"             << endl;
    std::cout << "5. Gerar atribuicoes"          << endl;
    std::cout << "6. Risk Analysis"              << endl;
    std::cout << "0. Sair"                       << endl;
    std::cout << "==========================" << endl;
    std::cout << "Opcao: ";
}

void listSubmissions(const Input& data) {
    for (const auto& sub : data.getSubmissions()) {
        cout << "ID: "      << sub.id
                  << " | Titulo: " << sub.title
                  << " | Autores: " << sub.authors
                  << " | Email: "  << sub.email
                  << " | Topico Primario: "   << sub.primary
                  << " | Topico Secundario: " << (sub.secondary == -1 ? "N/A" : to_string(sub.secondary))
                  << endl;
    }
}

void listReviewers(const Input& data) {
    for (const auto& rev : data.getReviewers()) {
        cout << "ID: "     << rev.id
                  << " | Nome: "  << rev.name
                  << " | Email: " << rev.email
                  << " | Topico Primario: "   << rev.primary
                  << " | Topico Secundario: " << (rev.secondary == -1 ? "N/A" : to_string(rev.secondary))
                  << endl;
    }
}

void listParameters(const Input& data) {
    cout << "MinReviewsPerSubmission:    " << data.getMinReviewsPerSubmission()    << endl;
    cout << "MaxReviewsPerReviewer:      " << data.getMaxReviewsPerReviewer()      << endl;
    cout << "PrimaryReviewerExpertise:   " << data.getPrimaryReviewerExpertise()   << endl;
    cout << "SecondaryReviewerExpertise: " << data.getSecondaryReviewerExpertise() << endl;
    cout << "PrimarySubmissionDomain:    " << data.getPrimarySubmissionDomain()    << endl;
    cout << "SecondarySubmissionDomain:  " << data.getSecondarySubmissionDomain()  << endl;
    cout << "GenerateAssignments:        " << data.getGenerateAssignments()        << endl;
    cout << "RiskAnalysis:               " << data.getRiskAnalysis()               << endl;
    cout << "OutputFileName:             " << data.getOutputFileName()             << endl;
}

void runMenu(Input& data, Graph<Node>& graph, bool loaded) {
    int choice;

    do {
        printMenu();
        cin >> choice;


        switch (choice) {
            case 1: {
                string filename;
                cout << "Caminho do ficheiro: ";
                cin >> filename;
                try {
                    data   = parseFile(filename);
                    graph  = makeGraph(data);
                    loaded = true;
                    cout << "Ficheiro carregado com sucesso!" << endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << std::endl;
                }
                break;
            }
            case 2:
                if (!loaded) { cout << "Carrega um ficheiro primeiro!" << endl; break; }
                listSubmissions(data);
                break;
            case 3:
                if (!loaded) { cout << "Carrega um ficheiro primeiro!" << endl; break; }
                listReviewers(data);
                break;
            case 4:
                if (!loaded) { cout << "Carrega um ficheiro primeiro!" << endl; break; }
                listParameters(data);
                break;
            case 5: {
                if (!loaded) { cout << "Carrega um ficheiro primeiro!" << endl; break; }
                Node source{0, Node::Type::SOURCE};
                Node sink{0, Node::Type::SINK};
                edmondsKarp(&graph, source, sink);
                printResults(graph,data);
                break;
            }
            case 6: {
                if (!loaded) { cout << "Carrega um ficheiro primeiro!" << endl; break; }
                Node source{0, Node::Type::SOURCE};
                Node sink{0, Node::Type::SINK};
                edmondsKarp(&graph,source,sink);
                printResults(graph,data);
                riskAnalysis(&graph, source, sink);
                break;
            }
            case 0:
                cout << "A sair..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while (choice != 0);
}