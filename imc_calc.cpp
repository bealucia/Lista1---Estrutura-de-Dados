#include <iostream>

using namespace std;

float calcularIMC(float massa, float altura) {
    return massa / (altura * altura);
}

string classificarIMC(float imc) {
    if (imc < 17)
        return "Muito abaixo do peso";
    else if (imc < 18.5)
        return "Abaixo do peso";
    else if (imc < 25)
        return "Peso normal";
    else if (imc < 30)
        return "Acima do peso";
    else if (imc < 35)
        return "Obesidade";
    else if (imc < 40)
        return "Obesidade severa";
    else
        return "Obesidade mórbida";
}

int main() {
    float massa, altura;
    cout << "Digite a massa (em kg): ";
    cin >> massa;
    cout << "Digite a altura (em metros): ";
    cin >> altura;

    float imc = calcularIMC(massa, altura);
    string classificacao = classificarIMC(imc);

    // Exibir resultado
    cout << "O IMC é: " << imc << endl;
    cout << "Classificado como: " << classificacao << endl;

    return 0;
}
