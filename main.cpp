#include <iostream>
#include <vector>
#include <algorithm>

class Ion {
private:
    char charge;
    int valence;

public:
    Ion(char ch, int val) : charge(ch), valence(val) {
        std::cout << "Ion created with charge: " << charge << " and valence: " << valence << std::endl;
    }

    Ion(const Ion& other) : charge(other.charge), valence(other.valence) {
        std::cout << "Ion copied with charge: " << charge << " and valence: " << valence << std::endl;
    }

    Ion(Ion&& other) noexcept : charge(other.charge), valence(other.valence) {
        other.charge = '\0';
        other.valence = 0;
        std::cout << "Ion moved with charge: " << charge << " and valence: " << valence << std::endl;
    }

    ~Ion() {
        std::cout << "Ion destroyed with charge: " << charge << " and valence: " << valence << std::endl;
    }

    Ion& operator=(const Ion& other) {
        if (this != &other) {
            charge = other.charge;
            valence = other.valence;
        }
        std::cout << "Ion assigned with charge: " << charge << " and valence: " << valence << std::endl;
        return *this;
    }

    char getCharge() const {
        return charge;
    }

    int getValence() const {
        return valence;
    }
};

int main() {
    std::vector<Ion> ions;

    ions.emplace_back('+', 2);
    ions.emplace_back('-', 4);
    ions.emplace_back('-', 2);
    ions.emplace_back('+', 3);

    std::vector<Ion> reactingIons;
    std::vector<Ion> nonReactingIons;


    for (auto& ion : ions) {
        auto it = std::find_if(ions.begin(), ions.end(), [&](const Ion& other) {
            return ion.getCharge() != other.getCharge() && ion.getValence() == other.getValence();
        });

        if (it != ions.end()) {
            reactingIons.emplace_back(std::move(ion));
        } else {
            nonReactingIons.emplace_back(ion);
        }
    }

    std::cout << "Ions in reaction:\n";
    for (const auto& ion : reactingIons) {
        std::cout << "Charge: " << ion.getCharge() << ", Valence: " << ion.getValence() << std::endl;
    }

    std::cout << "\nIons not in reaction:\n";
    for (const auto& ion : nonReactingIons) {
        std::cout << "Charge: " << ion.getCharge() << ", Valence: " << ion.getValence() << std::endl;
    }

    return 0;
}

