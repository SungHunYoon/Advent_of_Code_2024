#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
#include <string>

class Gate {
private:
    std::string outputWire;
    std::string operand1;
    std::string operand2;
    std::string operatorSymbol;

public:
    Gate(const std::string& gate, const std::string& outputWire)
        : outputWire(outputWire) {
        std::istringstream iss(gate);
        iss >> operand1 >> operatorSymbol >> operand2;
    }

    Gate(const std::string& outputWire, const std::string& operand1, const std::string& operand2, const std::string& operatorSymbol)
        : outputWire(outputWire), operand1(operand1), operand2(operand2), operatorSymbol(operatorSymbol) {}

    std::optional<int> getResult(const std::map<std::string, int>& values) const {
        if (values.count(operand1) && values.count(operand2)) {
            int val1 = values.at(operand1);
            int val2 = values.at(operand2);
            if (operatorSymbol == "AND") {
                return val1 & val2;
            } else if (operatorSymbol == "OR") {
                return val1 | val2;
            } else if (operatorSymbol == "XOR") {
                return val1 ^ val2;
            } else {
                throw std::invalid_argument("Unknown operator: " + operatorSymbol);
            }
        }
        return std::nullopt;
    }

    const std::string& getOutputWire() const {
        return outputWire;
    }

    const std::string& getOperator() const {
        return operatorSymbol;
    }

    const std::string& getOperand1() const {
        return operand1;
    }

    const std::string& getOperand2() const {
        return operand2;
    }

    bool operator<(const Gate& other) const {
        return outputWire < other.outputWire;
    }
};

class Day24 {
private:
    std::vector<Gate> parseGates(const std::vector<std::string>& input) {
        std::vector<Gate> gates;
        bool startParsing = false;
        for (const auto& line : input) {
            if (startParsing) {
                auto delimiterPos = line.find("-> ");
                std::string gate = line.substr(0, delimiterPos - 1);
                std::string wire = line.substr(delimiterPos + 3);
                gates.emplace_back(gate, wire);
            }
            if (line.empty()) {
                startParsing = true;
            }
        }
        return gates;
    }

    std::map<std::string, int> parseValues(const std::vector<std::string>& input) {
        std::map<std::string, int> values;
        for (const auto& line : input) {
            if (line.empty()) {
                break;
            }
            size_t delimiterPos = line.find(": ");
            if (delimiterPos == std::string::npos) {
                std::cerr << "Invalid line format: " << line << std::endl;
                continue;
            }
            std::string wire = line.substr(0, delimiterPos);
            try {
                int value = std::stoi(line.substr(delimiterPos + 2));
                values[wire] = value;
            } catch (const std::exception& e) {
                std::cerr << "Error parsing value for line: " << line << " -> " << e.what() << std::endl;
            }
        }
        return values;
    }

    void calculateFinalValues(std::map<std::string, int>& values, const std::vector<Gate>& gates) {
        std::vector<std::string> wires;
        for (const auto& gate : gates) {
            wires.push_back(gate.getOutputWire());
        }

        while (std::any_of(wires.begin(), wires.end(), [&](const std::string& wire) { return values.find(wire) == values.end(); })) {
            for (const auto& gate : gates) {
                auto result = gate.getResult(values);
                if (result.has_value()) {
                    values[gate.getOutputWire()] = result.value();
                }
            }
        }
    }

    long getNumber(const std::map<std::string, int>& values) {
        std::vector<std::string> zWires;
        for (const auto& [key, value] : values) {
            if (key.size() >= 1 && key[0] == 'z') { // starts_with 대체
                zWires.push_back(key);
            }
        }
        std::sort(zWires.rbegin(), zWires.rend());

        if (zWires.empty()) {
            std::cerr << "No keys starting with 'z' found in values!" << std::endl;
            return 0; // 기본값 반환
        }

        std::string binaryString;
        for (const auto& zWire : zWires) {
            if (values.find(zWire) == values.end()) {
                std::cerr << "Key not found in values: " << zWire << std::endl;
                continue;
            }
            int val = values.at(zWire);
            if (val != 0 && val != 1) {
                std::cerr << "Invalid binary value for key: " << zWire << " -> " << val << std::endl;
                continue;
            }
            binaryString += std::to_string(val);
        }

        if (binaryString.empty()) {
            std::cerr << "Binary string is empty! Defaulting to 0." << std::endl;
            return 0; // 기본값 반환
        }

        try {
            return std::stol(binaryString, nullptr, 2);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Conversion error: " << e.what() << std::endl;
            return 0; // 기본값 반환
        }
    }

    std::vector<Gate> findFaultyGates(const std::vector<Gate>& gates) {
        std::vector<Gate> faultyGates;

        for (const auto& gate : gates) {
            if (gate.getOutputWire().size() > 0 && gate.getOutputWire()[0] == 'z' && gate.getOutputWire() != "z45") {
                if (gate.getOperator() != "XOR") {
                    faultyGates.push_back(gate);
                }
            } else if (!(gate.getOutputWire().size() > 0 && gate.getOutputWire()[0] == 'z') &&
                       !(gate.getOperand1().size() > 0 && (gate.getOperand1()[0] == 'x' || gate.getOperand1()[0] == 'y')) &&
                       !(gate.getOperand2().size() > 0 && (gate.getOperand2()[0] == 'x' || gate.getOperand2()[0] == 'y'))) {
                if (gate.getOperator() == "XOR") {
                    faultyGates.push_back(gate);
                }
            } else if (gate.getOperator() == "XOR" &&
                       (gate.getOperand1().size() > 0 && (gate.getOperand1()[0] == 'x' || gate.getOperand1()[0] == 'y')) &&
                       (gate.getOperand2().size() > 0 && (gate.getOperand2()[0] == 'x' || gate.getOperand2()[0] == 'y'))) {
                if (!(gate.getOperand1().ends_with("00") && gate.getOperand2().ends_with("00"))) {
                    const std::string& output = gate.getOutputWire();
                    bool anotherFound = false;
                    for (const auto& otherGate : gates) {
                        if (otherGate.getOperand1() == output || otherGate.getOperand2() == output) {
                            if (otherGate.getOperator() == "XOR") {
                                anotherFound = true;
                                break;
                            }
                        }
                    }
                    if (!anotherFound) {
                        faultyGates.push_back(gate);
                    }
                }
            } else if (gate.getOperator() == "AND" &&
                       (gate.getOperand1().size() > 0 && (gate.getOperand1()[0] == 'x' || gate.getOperand1()[0] == 'y')) &&
                       (gate.getOperand2().size() > 0 && (gate.getOperand2()[0] == 'x' || gate.getOperand2()[0] == 'y'))) {
                if (!(gate.getOperand1().ends_with("00") && gate.getOperand2().ends_with("00"))) {
                    const std::string& output = gate.getOutputWire();
                    bool anotherFound = false;
                    for (const auto& otherGate : gates) {
                        if (otherGate.getOperand1() == output || otherGate.getOperand2() == output) {
                            if (otherGate.getOperator() == "OR") {
                                anotherFound = true;
                                break;
                            }
                        }
                    }
                    if (!anotherFound) {
                        faultyGates.push_back(gate);
                    }
                }
            }
        }
        return faultyGates;
    }

    std::string getOutput(std::vector<Gate>& faultyGates) {
        std::sort(faultyGates.begin(), faultyGates.end());
        std::ostringstream oss;
        for (size_t i = 0; i < faultyGates.size(); ++i) {
            oss << faultyGates[i].getOutputWire();
            if (i < faultyGates.size() - 1) {
                oss << ",";
            }
        }
        return oss.str();
    }

public:
    std::string runPart1(const std::vector<std::string>& input) {
        auto values = parseValues(input);
        auto gates = parseGates(input);
        calculateFinalValues(values, gates);
        return std::to_string(getNumber(values));
    }

    std::string runPart2(const std::vector<std::string>& input) {
        auto gates = parseGates(input);
        auto faultyGates = findFaultyGates(gates);
        return getOutput(faultyGates);
    }

    static std::vector<std::string> readInput(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
};

int main() {
    std::string filename = "input";
    auto input = Day24::readInput(filename);
    Day24 solver;

    std::cout << "Part 1: " << solver.runPart1(input) << std::endl;
    std::cout << "Part 2: " << solver.runPart2(input) << std::endl;

    return 0;
}
