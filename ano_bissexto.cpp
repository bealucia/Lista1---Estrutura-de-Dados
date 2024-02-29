#include <iostream>

bool verificarDivisoes(int iano) {
    return (iano % 4 == 0 && iano % 100 != 0) || (iano % 400 == 0);
}

int main() {
    int iano;
    std::cout << "Digite a ano para verificar se é bissexto: ";
    std::cin >> iano;

    if (verificarDivisoes(iano)) {
        std::cout << iano << " é um ano bissexto." << std::endl;
    } else {
        std::cout << iano << " não é um ano bissexto." << std::endl;
    }

    return 0;
}
