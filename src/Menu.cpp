/**
* @file Menu.cpp
 * @brief Implementation of the terminal menu for the program.
 */

#include <iostream>
#include <limits>
#include "Menu.h"
#include "MaxFlow.h"
#include "RiskAnalysis.h"

/**
 * @brief Displays the menu in the terminal.
 * @note **Time complexity:** O(1).
 */
void printMenu() {
    std::cout << "\n==========================" << endl;
    std::cout << "  Conference Review Tool  "   << endl;
    std::cout << "==========================" << endl;
    std::cout << "1. Carregar ficheiro CSV"      << endl;
    std::cout << "2. Listar submissoes"          << endl;
    std::cout << "3. Listar revisores"           << endl;
    std::cout << "4. Ver parametros"             << endl;
    std::cout << "5. Gerar atribuicoes"          << endl;
    std::cout << "0. Sair"                       << endl;
    std::cout << "==========================" << endl;
    std::cout << "Opcao: ";
}

/**
 * @brief Displays the submissions.
 * @param data Input object containing the data.
 * @note **Time complexity:** O(S), where S = number of submissions.
 */

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

/**
 * @brief Displays the reviewers.
 * @param data Input object containing the data.
 * @note **Time complexity:** O(R), where R = number of reviewers.
 */

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

/**
 * @brief  Display the parameters
 * @param data Input object containing the data.
 * @note **Time complexity** O(1)
 */

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

/**
 * @brief Displays the main menu, handles user input, and executes actions accordingly.
 *
 * This function provides a terminal-based interface for the user to:
 *
 * The function repeatedly prompts the user until the exit option (0) is selected.
 * Certain actions require that a file has been loaded first; otherwise, a warning is displayed.
 *
 * @param data Reference to the Input object containing submissions, reviewers, and parameters.
 * @param graph Reference to the Graph<Node> object representing the flow network.
 * @param loaded Boolean flag indicating whether input data has been successfully loaded.
 *
 * @note **Time Complexity:** Depends on the selected action:
 * - Listing submissions or reviewers: O(S) or O(R), where S = submissions, R = reviewers.
 * - Running Edmonds-Karp: O(V * E^2), where V = vertices, E = edges in the graph.
 * - Risk analysis: O(R * (V * E^2)), since Edmonds-Karp is repeated for each reviewer.
 *
 * The menu interface itself is O(1) per user input loop iteration.
 */
void runMenu(Input& data, Graph<Node>& graph, bool loaded);
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
                printResults(graph,data,data.getOutputFileName());
                if (data.getRiskAnalysis()!=0) {
                    riskAnalysis(&graph, source, sink,data.getOutputFileName());
                }
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